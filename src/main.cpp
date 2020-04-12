#include <dlfcn.h>
#include <wctype.h>
#include <string.h>
#include <signal.h>
// #include <sys/eventfd.h>
#include <sys/epoll.h>
#include <jnivm.h>
#include <log.h>
#include "native_activity.h"
#include "../mcpelauncher-linker/bionic/linker/linker_soinfo.h"
#include <game_window.h>
#include <game_window_manager.h>
#include <iostream>
#include <thread>
#include <future>
#include <atomic>

extern "C" int my_pthread_create(pthread_t *thread, const pthread_attr_t *__attr,
                             void *(*start_routine)(void*), void *arg);

enum class AndroidLogPriority {
    ANDROID_LOG_UNKNOWN = 0,
    ANDROID_LOG_DEFAULT,
    ANDROID_LOG_VERBOSE,
    ANDROID_LOG_DEBUG,
    ANDROID_LOG_INFO,
    ANDROID_LOG_WARN,
    ANDROID_LOG_ERROR,
    ANDROID_LOG_FATAL,
    ANDROID_LOG_SILENT
};

static LogLevel convertAndroidLogLevel(int level) {
    if (level <= (int) AndroidLogPriority::ANDROID_LOG_VERBOSE)
        return LogLevel::LOG_TRACE;
    if (level == (int) AndroidLogPriority::ANDROID_LOG_DEBUG)
        return LogLevel::LOG_DEBUG;
    if (level == (int) AndroidLogPriority::ANDROID_LOG_INFO)
        return LogLevel::LOG_INFO;
    if (level == (int) AndroidLogPriority::ANDROID_LOG_WARN)
        return LogLevel::LOG_WARN;
    if (level >= (int) AndroidLogPriority::ANDROID_LOG_ERROR)
        return LogLevel::LOG_ERROR;
    return LogLevel::LOG_ERROR;
}

extern "C" void* __loader_dlopen(const char* filename, int flags, const void* caller_addr);
extern "C" void* __loader_dlsym(void* handle, const char* symbol, const void* caller_addr);
extern "C" int __loader_dl_iterate_phdr(int (*cb)(struct dl_phdr_info* info, size_t size, void* data),
                             void* data);
extern "C" int __loader_dlclose(void* handle);
extern "C" char* __loader_dlerror();


void solist_init();

extern "C" {
struct _hook {
    const char *name;
    void *func;
};
extern struct _hook main_hooks[];
extern struct _hook dirent_hooks[];
extern struct _hook io_hooks[];
extern struct _hook net_hooks[];
extern struct _hook pthread_hooks[];
#ifdef __APPLE__
extern struct _hook net_darwin_hooks[];
#endif
}

const char* libm_symbols[] = {
        "__sF",
        "acos",
        "acosf",
        "acosh",
        "acoshf",
        "acoshl",
        "acosl",
        "asin",
        "asinf",
        "asinh",
        "asinhf",
        "asinhl",
        "asinl",
        "atan",
        "atan2",
        "atan2f",
        "atan2l",
        "atanf",
        "atanh",
        "atanhf",
        "atanhl",
        "atanl",
        "cabsl",
        "cbrt",
        "cbrtf",
        "cbrtl",
        "ceil",
        "ceilf",
        "ceill",
        "copysign",
        "copysignf",
        "copysignl",
        "cos",
        "cosf",
        "cosh",
        "coshf",
        "coshl",
        "cosl",
        "cprojl",
        "csqrtl",
        "drem",
        "dremf",
        "erf",
        "erfc",
        "erfcf",
        "erfcl",
        "erff",
        "erfl",
        "exp",
        "exp2",
        "exp2f",
        "exp2l",
        "expf",
        "expl",
        "expm1",
        "expm1f",
        "expm1l",
        "fabs",
        "fabsf",
        "fabsl",
        "fdim",
        "fdimf",
        "fdiml",
        "feclearexcept",
        "fedisableexcept",
        "feenableexcept",
        "fegetenv",
        "fegetexcept",
        "fegetexceptflag",
        "fegetround",
        "feholdexcept",
        "feraiseexcept",
        "fesetenv",
        "fesetexceptflag",
        "fesetround",
        "fetestexcept",
        "feupdateenv",
        "finite",
        "finitef",
        "floor",
        "floorf",
        "floorl",
        "fma",
        "fmaf",
        "fmal",
        "fmax",
        "fmaxf",
        "fmaxl",
        "fmin",
        "fminf",
        "fminl",
        "fmod",
        "fmodf",
        "fmodl",
        "frexp",
        "frexpf",
        "frexpl",
        "gamma",
        "gammaf",
        "gammaf_r",
        "gamma_r",
        "hypot",
        "hypotf",
        "hypotl",
        "ilogb",
        "ilogbf",
        "ilogbl",
        "j0",
        "j0f",
        "j1",
        "j1f",
        "jn",
        "jnf",
        "ldexpf",
        "ldexpl",
        "lgamma",
        "lgammaf",
        "lgammaf_r",
        "lgammal",
        "lgammal_r",
        "lgamma_r",
        "llrint",
        "llrintf",
        "llrintl",
        "llround",
        "llroundf",
        "llroundl",
        "log",
        "log10",
        "log10f",
        "log10l",
        "log1p",
        "log1pf",
        "log1pl",
        "log2",
        "log2f",
        "log2l",
        "logb",
        "logbf",
        "logbl",
        "logf",
        "logl",
        "lrint",
        "lrintf",
        "lrintl",
        "lround",
        "lroundf",
        "lroundl",
        "modf",
        "modff",
        "modfl",
        "nan",
        "nanf",
        "nanl",
        "nearbyint",
        "nearbyintf",
        "nearbyintl",
        "nextafter",
        "nextafterf",
        "nextafterl",
        "nexttoward",
        "nexttowardf",
        "nexttowardl",
        "pow",
        "powf",
        "powl",
        "remainder",
        "remainderf",
        "remainderl",
        "remquo",
        "remquof",
        "remquol",
        "rint",
        "rintf",
        "rintl",
        "round",
        "roundf",
        "roundl",
        "scalb",
        "scalbf",
        "scalbln",
        "scalblnf",
        "scalblnl",
        "scalbn",
        "scalbnf",
        "scalbnl",
        "__signbit",
        "__signbitf",
        "__signbitl",
        "signgam",
        "significand",
        "significandf",
        "significandl",
        "sin",
        "sincos",
        "sincosf",
        "sincosl",
        "sinf",
        "sinh",
        "sinhf",
        "sinhl",
        "sinl",
        "sqrt",
        "sqrtf",
        "sqrtl",
        "tan",
        "tanf",
        "tanh",
        "tanhf",
        "tanhl",
        "tanl",
        "tgamma",
        "tgammaf",
        "tgammal",
        "trunc",
        "truncf",
        "truncl",
        "y0",
        "y0f",
        "y1",
        "y1f",
        "yn",
        "ynf",
        "isnan",
        nullptr
};

const char* egl_symbols[] = {
        "eglGetCurrentDisplay",
        "eglChooseConfig",
        "eglGetError",
        "eglCreateWindowSurface",
        "eglGetConfigAttrib",
        "eglCreateContext",
        "eglDestroySurface",
        "eglSwapBuffers",
        "eglMakeCurrent",
        "eglDestroyContext",
        "eglTerminate",
        "eglGetDisplay",
        "eglInitialize",
        "eglQuerySurface",
        "eglSwapInterval",
        "eglQueryString",
        "eglGetCurrentContext",
        nullptr
};

const char* android_symbols[] = {
        "ANativeWindow_setBuffersGeometry",
        "AAssetManager_open",
        "AAsset_getLength",
        "AAsset_getBuffer",
        "AAsset_close",
        "AAsset_read",
        "AAsset_seek64",
        "AAsset_getLength64",
        "AAsset_getRemainingLength64",
        "ALooper_pollAll",
        "ANativeActivity_finish",
        "AInputQueue_getEvent",
        "AKeyEvent_getKeyCode",
        "AInputQueue_preDispatchEvent",
        "AInputQueue_finishEvent",
        "AKeyEvent_getAction",
        "AMotionEvent_getAxisValue",
        "AKeyEvent_getRepeatCount",
        "AKeyEvent_getMetaState",
        "AInputEvent_getDeviceId",
        "AInputEvent_getType",
        "AInputEvent_getSource",
        "AMotionEvent_getAction",
        "AMotionEvent_getPointerId",
        "AMotionEvent_getX",
        "AMotionEvent_getRawX",
        "AMotionEvent_getY",
        "AMotionEvent_getRawY",
        "AMotionEvent_getPointerCount",
        "AConfiguration_new",
        "AConfiguration_fromAssetManager",
        "AConfiguration_getLanguage",
        "AConfiguration_getCountry",
        "ALooper_prepare",
        "ALooper_addFd",
        "AInputQueue_detachLooper",
        "AConfiguration_delete",
        "AInputQueue_attachLooper",
        "AAssetManager_openDir",
        "AAssetDir_getNextFileName",
        "AAssetDir_close",
        "AAssetManager_fromJava",
        nullptr
};

const char* fmod_symbols[] = {
    "_ZN4FMOD6System12mixerSuspendEv",
    "_ZN4FMOD6System11mixerResumeEv",
    "_ZN4FMOD14ChannelControl7setMuteEb",
    "_ZN4FMOD14ChannelControl9setVolumeEf",
    "_ZN4FMOD14ChannelControl9isPlayingEPb",
    "_ZN4FMOD14ChannelControl4stopEv",
    "_ZN4FMOD6System9playSoundEPNS_5SoundEPNS_12ChannelGroupEbPPNS_7ChannelE",
    "_ZN4FMOD5Sound15getNumSubSoundsEPi",
    "_ZN4FMOD5Sound11getSubSoundEiPPS0_",
    "_ZN4FMOD14ChannelControl15set3DAttributesEPK11FMOD_VECTORS3_S3_",
    "_ZN4FMOD14ChannelControl15set3DAttributesEPK11FMOD_VECTORS3_",/*New x64*/
    "_ZN4FMOD14ChannelControl8setPitchEf",
    "_ZN4FMOD14ChannelControl9setPausedEb",
    "_ZN4FMOD5Sound7releaseEv",
    "_ZN4FMOD6System5closeEv",
    "_ZN4FMOD6System7releaseEv",
    "FMOD_System_Create",
    "_ZN4FMOD6System10getVersionEPj",
    "_ZN4FMOD6System9setOutputE15FMOD_OUTPUTTYPE",
    "_ZN4FMOD6System4initEijPv",
    "_ZN4FMOD6System13set3DSettingsEfff",
    "_ZN4FMOD6System18createChannelGroupEPKcPPNS_12ChannelGroupE",
    "_ZN4FMOD6System21getMasterChannelGroupEPPNS_12ChannelGroupE",
    "_ZN4FMOD12ChannelGroup8addGroupEPS0_bPPNS_13DSPConnectionE",
    "_ZN4FMOD6System23set3DListenerAttributesEiPK11FMOD_VECTORS3_S3_S3_",
    "_ZN4FMOD6System6updateEv",
    "_ZN4FMOD6System12createStreamEPKcjP22FMOD_CREATESOUNDEXINFOPPNS_5SoundE",
    "_ZN4FMOD6System11createSoundEPKcjP22FMOD_CREATESOUNDEXINFOPPNS_5SoundE",
    "_ZN4FMOD5Sound19set3DMinMaxDistanceEff",
    "_ZN4FMOD6System13getNumDriversEPi",
    "_ZN4FMOD6System13getDriverInfoEiPciP9FMOD_GUIDPiP16FMOD_SPEAKERMODES4_",
    "_ZN4FMOD6System9setDriverEi",
    "_ZN4FMOD5Sound7setModeEj",
    "_ZN4FMOD5Sound9getFormatEP15FMOD_SOUND_TYPEP17FMOD_SOUND_FORMATPiS5_",
    "_ZN4FMOD6System17getSoftwareFormatEPiP16FMOD_SPEAKERMODES1_",
    "_ZN4FMOD14ChannelControl11getDSPClockEPyS1_",
    "_ZN4FMOD14ChannelControl12addFadePointEyf",
    "_ZN4FMOD14ChannelControl8setDelayEyyb",
    "_ZN4FMOD6System17set3DNumListenersEi",
    "_ZN4FMOD6System13setFileSystemEPF11FMOD_RESULTPKcPjPPvS5_EPFS1_S5_S5_EPFS1_S5_S5_jS4_S5_EPFS1_S5_jS5_EPFS1_P18FMOD_ASYNCREADINFOS5_ESI_i",
    "FMOD_Memory_GetStats",
    "_ZN4FMOD6System11getCPUUsageEPfS1_S1_S1_S1_",
    "_ZN4FMOD6System18getChannelsPlayingEPiS1_",
    "_ZN4FMOD6System12getFileUsageEPxS1_S1_",
    nullptr
};

static void __android_log_vprint(int prio, const char *tag, const char *fmt, va_list args) {
    Log::vlog(convertAndroidLogLevel(prio), tag, fmt, args);
}
static void __android_log_print(int prio, const char *tag, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    Log::vlog(convertAndroidLogLevel(prio), tag, fmt, args);
    va_end(args);
}
static void __android_log_write(int prio, const char *tag, const char *text) {
    Log::log(convertAndroidLogLevel(prio), tag, "%s", text);
}

#define hybris_hook(a, b) symbols[a] = b;

static std::shared_ptr<GameWindow> window;

void InstallALooper(std::unordered_map<std::string, void *>& symbols) {
    struct Looper {
      int fd;
      int indent;
      void * data;
      int indent2;
      void * data2;
    };
    static Looper looper;
    hybris_hook("ALooper_pollAll", (void *)+[](  int timeoutMillis,
    int *outFd,
    int *outEvents,
    void **outData) {
      fd_set rfds;
      struct timeval tv;
      int retval;

      /* Watch stdin (fd 0) to see when it has input. */

      FD_ZERO(&rfds);
      FD_SET(looper.fd, &rfds);

      tv.tv_sec = 0;
      tv.tv_usec = 0;

      retval = select(looper.fd + 1, &rfds, NULL, NULL, &tv);
      /* Don't rely on the value of tv now! */

      if (retval == -1)
          perror("select()");
      else if (retval) {
          // printf("Data is available now.\n");
          *outData = looper.data;
          return looper.indent;
          /* FD_ISSET(0, &rfds) will be true. */
      }
      if(window) {
        window->pollEvents();
      }

      return -3;
    });
    hybris_hook("ALooper_addFd", (void *)+[](  void *loopere ,
      int fd,
      int ident,
      int events,
      int(* callback)(int fd, int events, void *data),
      void *data) {
      looper.fd = fd;
      looper.indent = ident;
      looper.data = data;
      return 1;
    });
    hybris_hook("AInputQueue_attachLooper", (void *)+[](  void *queue,
    void *looper2,
    int ident,
    void* callback,
    void *data) {
      looper.indent2 = ident;
      looper.data2 = data;
    });
}

#define EGL_NONE 0x3038
#define EGL_TRUE 1
#define EGL_FALSE 0
#define EGL_WIDTH 0x3057
#define EGL_HEIGHT 0x3056
using EGLint = int;
using EGLDisplay = void*;
using EGLSurface = void*;
using EGLContext = void*;
using EGLConfig = void*;
using NativeWindowType = void*;
using NativeDisplayType = void*;

void CreateIfNeededWindow() {
    if(!window) {
        window = GameWindowManager::getManager()->createWindow("mcpelauncher 64bit alpha", 1280, 720, GraphicsApi::OPENGL_ES2);
        window->show();
    }
}

void InstallEGL(std::unordered_map<std::string, void *>& symbols) {
    hybris_hook("eglChooseConfig", (void *)+[](EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config) {
      *num_config = 1;
      return EGL_TRUE;
    });
    hybris_hook("eglGetError", (void *)(void (*)())[]() {
    });
    hybris_hook("eglGetCurrentDisplay", (void *)+[]() -> EGLDisplay {
      return (EGLDisplay)1;
    });
    hybris_hook("eglCreateWindowSurface", (void *)+[](EGLDisplay display,
      EGLConfig config,
      NativeWindowType native_window,
      EGLint const * attrib_list) {
      return native_window;
    });
    hybris_hook("eglGetConfigAttrib", (void *)+[](EGLDisplay display,
      EGLConfig config,
      EGLint attribute,
      EGLint * value) {
      return EGL_TRUE;
    });
    hybris_hook("eglCreateContext", (void *)+[](EGLDisplay display,
      EGLConfig config,
      EGLContext share_context,
      EGLint const * attrib_list) {
      CreateIfNeededWindow();
      return 1;
    });
    hybris_hook("eglDestroySurface", (void *)(void (*)())[]() {
    });
    hybris_hook("eglSwapBuffers", (void *)+[](EGLDisplay *display,
      EGLSurface surface) {
        window->swapBuffers();
    });
    hybris_hook("eglMakeCurrent", (void *)+[](EGLDisplay display,
      EGLSurface draw,
      EGLSurface read,
      EGLContext context) {
      Log::warn("Launcher", "EGL stub %s called", "eglMakeCurrent");
      CreateIfNeededWindow();
      return EGL_TRUE;
    });
    hybris_hook("eglDestroyContext", (void *)(void (*)())[]() {
    });
    hybris_hook("eglTerminate", (void *)(void (*)())[]() {
    });
    hybris_hook("eglGetDisplay", (void *)+[](NativeDisplayType native_display) {
      return 1; 
    });
    hybris_hook("eglInitialize", (void *)+[](void* display, uint32_t * major, uint32_t * minor) {

      return EGL_TRUE;
    });
    hybris_hook("eglQuerySurface", (void *) + [](void* dpy, EGLSurface surface, EGLint attribute, EGLint *value) {
      int dummy;
      CreateIfNeededWindow();
      switch (attribute)
      {
      case EGL_WIDTH:
          window->getWindowSize(*value, dummy);
          break;
      case EGL_HEIGHT:
          window->getWindowSize(dummy, *value);
          break;
      default:
          return EGL_FALSE;
      }
      return EGL_TRUE;
    });
    hybris_hook("eglSwapInterval", (void *)+[](EGLDisplay display, EGLint interval) {
        window->swapInterval(interval);
      return EGL_TRUE;
    });
    hybris_hook("eglQueryString", (void *)+[](void* display, int32_t name) {
        return 0;
    });
    hybris_hook("eglGetProcAddress", ((void*)+[](char* ch)->void*{
      static std::unordered_map<std::string, void*> eglfuncs = {{ "glInvalidateFramebuffer", (void*)+[]() {}}};
      auto hook = eglfuncs[ch];
      if(!hook) {
          hook = ((void* (*)(const char*))GameWindowManager::getManager()->getProcAddrFunc())(ch);
      }
      return hook;
    }));
    hybris_hook("eglGetCurrentContext", (void*) + []() -> int {
      return 0;
    });
}

#include "../mcpelauncher-linker/bionic/libc/platform/bionic/tls.h"
#ifdef __x86_64__
// Signal handler for when code tries to use %fs.
static void handle_sigsegv(int sig, siginfo_t *si, void *ucp) {
  ucontext_t *uc = (ucontext_t*)ucp;
  unsigned char *p = (unsigned char *)uc->uc_mcontext->__ss.__rip;
  if (p && *p == 0x64) {
    // Instruction starts with 0x64, meaning it tries to access %fs. By
    // changing the first byte to 0x65, it uses %gs instead.
    //std::cout << "Try to patch it\n";
    *p = 0x65;
    //std::cout << "Tried to patch it\n";
  } else if (p && *p == 0x65) {
    // Instruction has already been patched up, but it may well be the
    // case that this was done by another CPU core. There is nothing
    // else we can do than return and try again. This may cause us to
    // get stuck indefinitely.
  } else {
    // Segmentation violation on an instruction that does not try to
    // access %fs. Reset the handler to its default action, so that the
    // segmentation violation is rethrown.
    struct sigaction sa = {
        .sa_handler = SIG_DFL,
    };
    sigemptyset(&sa.sa_mask);
    sigaction(SIGSEGV, &sa, NULL);
  }
}

static void *tls_get(void) {
  void *tcb;
  asm volatile("mov %%gs:0, %0" : "=r"(tcb));
  return tcb;
}

static void tls_set(const void *tcb) {
  asm volatile("mov %0, %%gs:0x28" : : "r"(tcb));
}
#endif

int main(int argc, char** argv) {
#ifdef __x86_64__
    // On OS X there doesn't seem to be any way to modify the %fs base.
    // Let's use %gs instead. Install a signal handler for SIGSEGV to
    // dynamically patch up instructions that access %fs.
    static bool handler_set_up = false;
    if (!handler_set_up) {
        struct sigaction sa = {
            .sa_sigaction = handle_sigsegv,
            .sa_flags = SA_SIGINFO,
        };
        sigemptyset(&sa.sa_mask);
        sigaction(SIGSEGV, &sa, NULL);
        handler_set_up = true;
    }
    void * val2 = tls_get();
    static uintptr_t guard = 0;
    tls_set(&guard);
    auto val = __get_tls();
#endif
    solist_init();
    std::unordered_map<std::string, void *> symbols;
    for (size_t i = 0; main_hooks[i].name; i++) {
        symbols[main_hooks[i].name] = main_hooks[i].func;
    }
    for (size_t i = 0; dirent_hooks[i].name; i++) {
        symbols[dirent_hooks[i].name] = dirent_hooks[i].func;
    }
    for (size_t i = 0; io_hooks[i].name; i++) {
        symbols[io_hooks[i].name] = io_hooks[i].func;
    }
    for (size_t i = 0; net_hooks[i].name; i++) {
        symbols[net_hooks[i].name] = net_hooks[i].func;
    }
    for (size_t i = 0; net_darwin_hooks[i].name; i++) {
        symbols[net_darwin_hooks[i].name] = net_darwin_hooks[i].func;
    }
    
    for (size_t i = 0; pthread_hooks[i].name; i++) {
        symbols[pthread_hooks[i].name] = pthread_hooks[i].func;
    }
    auto h = dlopen("libm.dylib", RTLD_LAZY);
    for (size_t i = 0; libm_symbols[i]; i++) {
        symbols[libm_symbols[i]] = dlsym(h, libm_symbols[i]);
    }
    symbols["newlocale"] = (void*)newlocale;
    symbols["uselocale"] = (void*)uselocale;
    symbols["mbsrtowcs"] = (void*)mbsrtowcs;
    symbols["freelocale"] = (void*)freelocale;
    symbols["iswlower"] = (void*)iswlower;
    symbols["iswprint"] = (void*)iswprint;
    symbols["iswblank"] = (void*)iswblank;
    symbols["iswcntrl"] = (void*)iswcntrl;
    symbols["iswupper"] = (void*)iswupper;
    symbols["iswalpha"] = (void*)iswalpha;
    symbols["iswdigit"] = (void*)iswdigit;
    symbols["iswpunct"] = (void*)iswpunct;
    symbols["iswxdigit"] = (void*)iswxdigit;
    symbols["wcsnrtombs"] = (void*)wcsnrtombs;
    symbols["mbsnrtowcs"] = (void*)mbsnrtowcs;
    symbols["__ctype_get_mb_cur_max"] = (void*) + []() -> size_t {
        return 4;
    };
    symbols["mbrlen"] = (void*)mbrlen;
    symbols["vasprintf"] = (void*)+ []() {

    };
    symbols["wcstol"] = (void*)wcstol;
    symbols["wcstoul"] = (void*)wcstoul;
    symbols["wcstoll"] = (void*)wcstoll;
    symbols["wcstoull"] = (void*)wcstoull;
    symbols["wcstof"] = (void*)wcstof;
    symbols["wcstod"] = (void*)wcstod;
    symbols["wcstold"] = (void*)wcstold;
    symbols["swprintf"] = (void*)swprintf;
    symbols["android_set_abort_message"] = (void*)+[](const char msg) {
        
    };
    symbols["sigemptyset"] = (void*)sigemptyset;
    symbols["sigaddset"] = (void*)sigaddset;
    symbols["arc4random"] = (void*)+[]() -> uint32_t{
        return 0;
    };
    symbols["strptime"] = (void*)+[]() {

    };
    symbols["strptime_l"] = (void*)+[]() {
        
    };
    symbols["__FD_SET_chk"] = (void*)+[]() {
        
    };
    symbols["__FD_ISSET_chk"] = (void*)+[]() {
        
    };
    
    symbols["epoll_create1"] = (void*)+[]() {
        
    };
    
    symbols["eventfd"] = (void*)  + []() -> int {
        return -1;
    };

    symbols["__memcpy_chk"] = (void*) + [](void* dst, const void* src, size_t count, size_t dst_len) -> void*{
        return memcpy(dst, src, count);
    };
    symbols["__vsnprintf_chk"] = (void*) + [](char* dst, size_t supplied_size, int /*flags*/,
                               size_t dst_len_from_compiler, const char* format, va_list va) -> int {
        return vsnprintf(dst, supplied_size, format, va);
    };

    symbols["__fgets_chk"] = (void*) + [](char* dst, int supplied_size, FILE* stream, size_t dst_len_from_compiler) {
        return fgets(dst, supplied_size, stream);
    };
    
    
    // soinfo::load_library("libhybris.so", symbols);
    soinfo::load_library("libdl.so", { { std::string("dl_iterate_phdr"), (void*)&__loader_dl_iterate_phdr },
                                       { std::string("dlopen"), (void*)+ [](const char * filename, int flags)-> void* {
                                           return __loader_dlopen(filename, flags, nullptr);
                                       }},
                                       { std::string("dlsym"), (void*)+ [](void* dl, const char * name)-> void* {
                                           return __loader_dlsym(dl, name, nullptr);
                                       }},
                                       { std::string("dlclose"), (void*)&__loader_dlclose },
                                       { std::string("dlerror"), (void*)&__loader_dlerror},
                                       
                                        });
    symbols["_ZN6cohtml17VerifiyLicenseKeyEPKc"] = (void*) + []() {
        return true;
    };
    symbols["_ZN3web4http6client7details35verify_cert_chain_platform_specificERN5boost4asio3ssl14verify_contextERKSs"] = (void*) + []() {
        return true;
    };

    static std::promise<std::pair<void *(*)(void*), void *>> pthread_main;
    static std::atomic_bool run_pthread_main = true;
    static pthread_t pthread_main_v = pthread_self();
    symbols["pthread_create"] = (void*) + [](pthread_t *thread, const pthread_attr_t *__attr, void *(*start_routine)(void*), void *arg) -> int {
        if(run_pthread_main.exchange(false)) {
            *thread = pthread_main_v;
            pthread_main.set_value({start_routine, arg});
            return 0;
        }
        return my_pthread_create(thread, __attr, start_routine, arg);
    };
    
    soinfo::load_library("libc.so", symbols);
    // symbols.clear();
    // auto h = dlopen("libm.so.6", RTLD_LAZY);
    // for (size_t i = 0; libm_symbols[i]; i++) {
    //     symbols[libm_symbols[i]] = dlsym(h, libm_symbols[i]);
    // }
    soinfo::load_library("libm.so", /* symbols */ {});
    symbols.clear();
    for (size_t i = 0; egl_symbols[i]; i++) {
        symbols[egl_symbols[i]] = (void*)+[]() {
            
        };
    }
    symbols["eglGetProcAddress"] = (void*) + [](const char* name) -> void* {
        return nullptr;
    };
    InstallEGL(symbols);
    soinfo::load_library("libEGL.so", symbols);
    symbols.clear();
    symbols["__android_log_print"] = (void*) __android_log_print;
    symbols["__android_log_vprint"] = (void*) __android_log_vprint;
    symbols["__android_log_write"] = (void*) __android_log_write;

    soinfo::load_library("liblog.so", symbols);
    symbols.clear();
    for (size_t i = 0; android_symbols[i]; i++) {
        symbols[android_symbols[i]] = (void*)+[]() {
            
        };
    }
    InstallALooper(symbols);
    soinfo::load_library("libandroid.so", symbols);
    soinfo::load_library("libOpenSLES.so", { });
    auto libcpp = __loader_dlopen("../libs/libc++_shared.so", 0, 0) || __loader_dlopen("../libs/libgnustl_shared.so", 0, 0);
    symbols.clear();
    for (size_t i = 0; fmod_symbols[i]; i++) {
        symbols[fmod_symbols[i]] = (void*)+[]() {
            
        };
    }
    soinfo::load_library("libfmod.so", symbols);
    void * libmcpe = __loader_dlopen("../libs/libminecraftpe.so", 0, 0);
    if(!libmcpe) {
        std::cout << "Please change the current working directory to the assets folder.\nOn linux e.g \"cd ~/.local/share/mcpelauncher/versions/1.16.0.55/assets\"\n";
        return -1;
    }
    auto vm = std::make_shared<jnivm::VM>();
    ///Fake act
    auto mainActivity = std::make_shared<jnivm::Object>();
    auto MainActivity_ = vm->GetEnv()->GetClass("com/mojang/minecraftpe/MainActivity");
    mainActivity->clazz = MainActivity_;
    MainActivity_->HookInstanceFunction(vm->GetEnv().get(), "createUUID", [](jnivm::ENV*env, jnivm::Object*obj) -> std::shared_ptr<jnivm::String> {
        return std::make_shared<jnivm::String>("daa78df1-373a-444d-9b1d-4c71a14bb559");
    });
    struct ClassLoader : jnivm::Object { };
    auto ClassLoader_ = vm->GetEnv()->GetClass<ClassLoader>("java/lang/ClassLoader");
    MainActivity_->HookInstanceFunction(vm->GetEnv().get(), "getClassLoader", [](jnivm::ENV*env, jnivm::Object*obj) -> std::shared_ptr<ClassLoader> {
        return std::make_shared<ClassLoader>();
    });
// OLD BEGIN
    auto env = vm->GetEnv();
    MainActivity_->HookInstanceFunction(env.get(), "launchUri", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<jnivm::String> uri) {
      Log::trace("Launch URI", "%s", uri->data());
    });
    struct StoreListener : jnivm::Object {
        jlong nstorelisterner;
    };
    struct NativeStoreListener : StoreListener {
    };
    auto NativeStoreListener_ = env->GetClass<NativeStoreListener>("com/mojang/minecraftpe/store/NativeStoreListener");
    NativeStoreListener_->Hook(env.get(), "<init>", [](jnivm::ENV*env, jnivm::Class*cl, jlong arg0) -> std::shared_ptr<NativeStoreListener> {
      auto storel = std::make_shared<NativeStoreListener>();
      storel->nstorelisterner = arg0;
      return storel;
    });
    // Show Gamepad Options
	  auto Build = env->GetClass("android/os/Build$VERSION");
    Build->HookGetterFunction(env.get(), "SDK_INT", [](jnivm::ENV*env, jnivm::Class*cl) -> jint {
      return 28;
    });
    // Make pictures loading, advance apilevel
    MainActivity_->HookInstanceFunction(env.get(), "getAndroidVersion", [](jnivm::ENV*env, jnivm::Object*obj) -> jint {
      return 28;
    });
    auto StoreListener_ = env->GetClass<StoreListener>("com/mojang/minecraftpe/store/StoreListener");
    struct Store : jnivm::Object {
    };
    auto Store_ = env->GetClass<Store>("com/mojang/minecraftpe/store/Store");
    Store_->HookInstanceFunction(env.get(), "receivedLicenseResponse", [](jnivm::ENV* env, jnivm::Object* store) -> jboolean {
      return true;
    });
    Store_->HookInstanceFunction(env.get(), "hasVerifiedLicense", [](jnivm::ENV* env, jnivm::Object* store) -> jboolean {
      return true;
    });
    struct StoreFactory : jnivm::Object {
    };
    auto StoreFactory_ = env->GetClass<StoreFactory>("com/mojang/minecraftpe/store/StoreFactory");
    StoreFactory_->Hook(env.get(), "createGooglePlayStore", [callback = (void(*)(JNIEnv*,StoreListener*, jlong, jboolean)) __loader_dlsym(libmcpe, "Java_com_mojang_minecraftpe_store_NativeStoreListener_onStoreInitialized", 0)](jnivm::ENV* env, jnivm::Class* clazz, std::shared_ptr<jnivm::String> arg0, std::shared_ptr<StoreListener> arg1) -> std::shared_ptr<Store> {
      auto store = std::make_shared<Store>();
      callback(&env->env, arg1.get(), arg1->nstorelisterner, true);
      return store;
    });
// OLD END
    ClassLoader_->HookInstanceFunction(vm->GetEnv().get(), "loadClass", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<jnivm::String> str) {
        return env->GetClass(str->data());
    });
    struct Context : jnivm::Object { };
    auto Context_ = vm->GetEnv()->GetClass<Context>("android/content/Context");
    struct Intent : jnivm::Object { };
    auto Intent_ = vm->GetEnv()->GetClass<Intent>("android/content/Intent");
    // Context_->HookInstanceFunction(vm->GetEnv().get(), "startActivity", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<Intent> in) {

    // });
    struct NativeActivity : jnivm::Object { };
    auto NativeActivity_ = vm->GetEnv()->GetClass<NativeActivity>("android/app/NativeActivity");
    NativeActivity_->HookInstanceFunction(vm->GetEnv().get(), "getApplicationContext", [](jnivm::ENV*env, jnivm::Object*obj) {
        return std::make_shared<Context>();
    });

    struct Interop : jnivm::Object {};
    auto Interop_ = vm->GetEnv()->GetClass<Interop>("com/microsoft/xbox/idp/interop/Interop");
    Interop_->HookInstanceFunction(vm->GetEnv().get(), "GetLocalStoragePath", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<Context> ctx) {
        return std::make_shared<jnivm::String>("/");
    });
    Interop_->HookInstanceFunction(vm->GetEnv().get(), "ReadConfigFile", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<Context> ctx) {
        return std::make_shared<jnivm::String>("{}");
    });

    struct ByteArrayInputStream : jnivm::Object {
        std::shared_ptr<jnivm::Array<jbyte>> s;
    };
    auto ByteArrayInputStream_ = vm->GetEnv()->GetClass<ByteArrayInputStream>("java/io/ByteArrayInputStream");
    ByteArrayInputStream_->Hook(vm->GetEnv().get(), "<init>", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<jnivm::Array<jbyte>> s) {
        auto factory = std::make_shared<ByteArrayInputStream>();
        factory->s = s;
        return factory;
    });

    struct CertificateFactory : jnivm::Object {
        std::shared_ptr<jnivm::String> s;
    };
    auto CertificateFactory_ = vm->GetEnv()->GetClass<CertificateFactory>("java/security/cert/CertificateFactory");
    CertificateFactory_->Hook(vm->GetEnv().get(), "getInstance", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<jnivm::String> s) {
        auto factory = std::make_shared<CertificateFactory>();
        factory->s = s;
        return factory;
    });
    struct InputStream : jnivm::Object {
    };
    auto InputStream_ = vm->GetEnv()->GetClass<InputStream>("java/io/InputStream");
    struct Certificate : jnivm::Object {
    };
    struct X509Certificate : Certificate {};
    auto Certificate_ = vm->GetEnv()->GetClass<Certificate>("java/security/cert/Certificate");
    CertificateFactory_->HookInstanceFunction(vm->GetEnv().get(), "generateCertificate", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<InputStream> s) -> std::shared_ptr<Certificate> {
        auto factory = std::make_shared<X509Certificate>();
        return factory;
    });

    struct TrustManagerFactory : jnivm::Object {
        std::shared_ptr<jnivm::String> s;
    };
    auto TrustManagerFactory_ = vm->GetEnv()->GetClass<TrustManagerFactory>("javax/net/ssl/TrustManagerFactory");
    TrustManagerFactory_->Hook(vm->GetEnv().get(), "getInstance", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<jnivm::String> s) {
        auto factory = std::make_shared<TrustManagerFactory>();
        factory->s = s;
        return factory;
    });
    struct TrustManager : jnivm::Object {};
    auto TrustManager_ = vm->GetEnv()->GetClass<TrustManager>("javax/net/ssl/TrustManager");
    TrustManagerFactory_->HookInstanceFunction(vm->GetEnv().get(), "getTrustManagers", [](jnivm::ENV*env, jnivm::Object*obj) {
        auto factory = std::make_shared<jnivm::Array<std::shared_ptr<TrustManager>>>(new std::shared_ptr<TrustManager>[1] { std::make_shared<TrustManager>() }, 1);
        return factory;
    });

    struct StrictHostnameVerifier : jnivm::Object {};
    auto StrictHostnameVerifier_ = vm->GetEnv()->GetClass<StrictHostnameVerifier>("org/apache/http/conn/ssl/StrictHostnameVerifier");
    StrictHostnameVerifier_->Hook(vm->GetEnv().get(), "<init>", [](jnivm::ENV*env, jnivm::Object*obj) {
        auto factory = std::make_shared<StrictHostnameVerifier>();
        return factory;
    });
    auto X509Certificate_ = vm->GetEnv()->GetClass<X509Certificate>("org/apache/http/conn/ssl/java/security/cert/X509Certificate");
    StrictHostnameVerifier_->HookInstanceFunction(vm->GetEnv().get(), "verify", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<jnivm::String> s, std::shared_ptr<X509Certificate> cert) {

    });

    auto JNI_OnLoad = (jint (*)(JavaVM* vm, void* reserved))__loader_dlsym(libmcpe, "JNI_OnLoad", nullptr);

    auto ver = JNI_OnLoad(vm->GetJavaVM(), nullptr);
    ANativeActivity activity;
    ANativeActivityCallbacks callbacks;
    std::thread starter([&]() {
        memset(&activity, 0, sizeof(ANativeActivity));
        activity.internalDataPath = "./idata/";
        activity.externalDataPath = "./edata/";
        activity.obbPath = "./oob/";
        activity.sdkVersion = 28;
        activity.vm = vm->GetJavaVM();
        activity.clazz = mainActivity.get();
        // activity.assetManager = (struct AAssetManager*)23;
        memset(&callbacks, 0, sizeof(ANativeActivityCallbacks));
        activity.callbacks = &callbacks;
        activity.vm->GetEnv(&(void*&)activity.env, 0);
        auto ANativeActivity_onCreate = (ANativeActivity_createFunc*)__loader_dlsym(libmcpe, "ANativeActivity_onCreate", 0);
        ANativeActivity_onCreate(&activity, nullptr, 0);
        auto nativeRegisterThis = (void(*)(JNIEnv * env, void*))__loader_dlsym(libmcpe, "Java_com_mojang_minecraftpe_MainActivity_nativeRegisterThis", 0);
        nativeRegisterThis(activity.env, mainActivity.get());
        activity.callbacks->onInputQueueCreated(&activity, (AInputQueue *)1);
        activity.callbacks->onNativeWindowCreated(&activity, (ANativeWindow *)1);
        activity.callbacks->onStart(&activity);
        activity.callbacks->onResume(&activity);
    });
    auto run_main = pthread_main.get_future().get();
    run_main.first(run_main.second);
    return 0;
}