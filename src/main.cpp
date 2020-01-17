#include <log.h>
#include <hybris/hook.h>
#include <hybris/dlfcn.h>
#ifdef _WIN32
#include <windows/msvc.h>
#include <windows/dirent.h>
#include <windows/dlfcn.h>
#include <fcntl.h>
#else
#include <dlfcn.h>
#include <dirent.h>
#include <unistd.h>
#endif
#include <game_window_manager.h>
#include <argparser.h>
#include <mcpelauncher/minecraft_utils.h>
#include <mcpelauncher/minecraft_version.h>
#include <mcpelauncher/crash_handler.h>
#include <mcpelauncher/path_helper.h>
#include <minecraft/Common.h>
#include <minecraft/MinecraftGame.h>
#include <minecraft/ClientInstance.h>
#include <mcpelauncher/mod_loader.h>
#include "window_callbacks.h"
// #include "xbox_live_helper.h"
#ifdef USE_ARMHF_SUPPORT
#include "armhf_support.h"
#endif
#ifdef __i386__
#include "cpuid.h"
#endif
#include <build_info.h>
#include "native_activity.h"
#include <jnivm.h>
#include <fstream>
#include <sys/types.h>
#include <hybris/hook.h>
#include <signal.h>
#include "JNIBinding.h"

#include <GLFW/glfw3.h>

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

JNIEnv * jnienv = 0;

void printVersionInfo();

// void test() {
//   __asm {
//     MOV EAX, DWORD PTR SS:[EBP + 4]
//   }
//   auto proc_ = ((char*(*)(int))glfwGetProcAddress("glGetString"));
//   char* ret2 = proc_(0x1F03);
//   Log::trace("test", "[%ld] %s", (unsigned long&) proc_, ret2);
//   __asm {
//     MOV EAX, DWORD PTR SS:[EBP + 4]
//   }
// }

int main(int argc, char *argv[]) {
    auto windowManager = GameWindowManager::getManager();
    // CrashHandler::registerCrashHandler();
    // MinecraftUtils::workaroundLocaleBug();

    argparser::arg_parser p;
    argparser::arg<bool> printVersion (p, "--version", "-v", "Prints version info");
    argparser::arg<std::string> gameDir (p, "--game-dir", "-dg", "Directory with the game and assets");
    argparser::arg<std::string> dataDir (p, "--data-dir", "-dd", "Directory to use for the data");
    argparser::arg<std::string> cacheDir (p, "--cache-dir", "-dc", "Directory to use for cache");
    argparser::arg<int> windowWidth (p, "--width", "-ww", "Window width", 720);
    argparser::arg<int> windowHeight (p, "--height", "-wh", "Window height", 480);
    argparser::arg<float> pixelScale (p, "--scale", "-s", "Pixel Scale", 2.f);
    argparser::arg<bool> mallocZero (p, "--malloc-zero", "-mz", "Patch malloc to always zero initialize memory, this may help workaround MCPE bugs");
    argparser::arg<bool> disableFmod (p, "--disable-fmod", "-df", "Disables usage of the FMod audio library");
    if (!p.parse(argc, (const char**) argv))
        return 1;
    if (printVersion) {
        printVersionInfo();
        return 0;
    }
    PathHelper::setGameDir("C:\\Users\\Christopher\\AppData\\Local\\mcpelauncher2\\versions\\1.14.2.50");
    if (!gameDir.get().empty())
        PathHelper::setGameDir(gameDir);
    if (!dataDir.get().empty())
        PathHelper::setDataDir(dataDir);
    if (!cacheDir.get().empty())
        PathHelper::setCacheDir(cacheDir);
    if (mallocZero)
        MinecraftUtils::setMallocZero();

    Log::info("Launcher", "Version: client %s / manifest %s", CLIENT_GIT_COMMIT_HASH, MANIFEST_GIT_COMMIT_HASH);
#ifdef __i386__
    {
        CpuId cpuid;
        Log::info("Launcher", "CPU: %s %s", cpuid.getManufacturer(), cpuid.getBrandString());
        Log::info("Launcher", "CPU supports SSSE3: %s",
                cpuid.queryFeatureFlag(CpuId::FeatureFlag::SSSE3) ? "YES" : "NO");
    }
#endif

    GraphicsApi graphicsApi = GraphicsApi::OPENGL_ES2;

    Log::trace("Launcher", "Loading hybris libraries");
    /*if (!disableFmod)
        MinecraftUtils::loadFMod();
    else*/
        MinecraftUtils::stubFMod();
    MinecraftUtils::setupHybris();

    Log::info("Launcher", "Creating window");
    WindowCallbacks::loadGamepadMappings();
    static auto window = windowManager->createWindow("Minecraft", windowWidth, windowHeight, graphicsApi);
    window->setIcon(PathHelper::getIconPath());
    window->show();
    hybris_hook("ANativeActivity_finish", (void *)+[](ANativeActivity *activity) {
      Log::warn("Launcher", "Android stub %s called", "ANativeActivity_finish");
      std::thread([=]() {
        // Saves nothing (returns every time null)
        // size_t outSize;
        // void * data = activity->callbacks->onSaveInstanceState(activity, &outSize);
        ((void(*)(JNIEnv * env, void*))hybris_dlsym(jnienv->functions->reserved3, "Java_com_mojang_minecraftpe_MainActivity_nativeUnregisterThis"))(jnienv, nullptr);
        ((void(*)(JNIEnv * env, void*))hybris_dlsym(jnienv->functions->reserved3, "Java_com_mojang_minecraftpe_MainActivity_nativeSuspend"))(jnienv, nullptr);
        ((void(*)(JNIEnv * env, void*))hybris_dlsym(jnienv->functions->reserved3, "Java_com_mojang_minecraftpe_MainActivity_nativeShutdown"))(jnienv, nullptr);
        activity->callbacks->onStop(activity);
      }).detach();
      // With Xboxlive it usually don't close the Game with the main function correctly
      // Force exit with code 0 (Maybe Android related)
      _Exit(0);
    });
    hybris_hook("eglChooseConfig", (void *)+[](EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config) {
      *num_config = 1;
      return EGL_TRUE;
    });
    hybris_hook("eglGetError", (void *)(void (*)())[]() {
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
        // Force Opengl ES 2
        if(attrib_list && attrib_list[0] == 0x3098 && attrib_list[1] > 2) {
            return 0;
        }
      return 1;
    });
    hybris_hook("eglDestroySurface", (void *)(void (*)())[]() {
    });
    hybris_hook("eglSwapBuffers", (void *)+[](EGLDisplay *display,
      EGLSurface surface) {
        if(surface) {
            ((GameWindow*)surface)->swapBuffers();
        }
    });
    hybris_hook("eglMakeCurrent", (void *)+[](EGLDisplay display,
      EGLSurface draw,
      EGLSurface read,
      EGLContext context) {
      Log::warn("Launcher", "EGL stub %s called", "eglMakeCurrent");
      return EGL_TRUE;
    });
    hybris_hook("eglDestroyContext", (void *)(void (*)())[]() {
    });
    hybris_hook("eglTerminate", (void *)(void (*)())[]() {
    });
    hybris_hook("eglGetDisplay", (void *)+[](NativeDisplayType native_display) {
      return 1; 
    });
    hybris_hook("eglInitialize", (void *)+[](void* display,
    uint32_t * major,
    uint32_t * minor) {
      return EGL_TRUE;
    });
    hybris_hook("eglQuerySurface", (void *) + [](void* dpy, EGLSurface surface, EGLint attribute, EGLint *value) {
      int dummy;
      switch (attribute)
      {
      case EGL_WIDTH:
          ((GameWindow*) surface)->getWindowSize(*value, dummy);
          break;
      case EGL_HEIGHT:
          ((GameWindow*) surface)->getWindowSize(dummy, *value);
          break;
      default:
          return EGL_FALSE;
      }
      return EGL_TRUE;
    });
    hybris_hook("eglSwapInterval", (void *)+[](EGLDisplay display,
      EGLint interval) {
        window->swapInterval(interval);
      return EGL_TRUE;
    });
    hybris_hook("eglQueryString", (void *)+[](void* display, int32_t name) {
        return 0;
    });
    // auto eglGetProcAddress =  (void* (*)(const char*))[](const char* name) -> void* {
    //   return !strcmp(name, "glGetString") ? /* (void*)glfwGetProcAddress("glGetString") */(void*)+[](int i) -> char* {
    //     // auto res = div(2, 4);
        
    //     // char * ret8 = proc_(i);
    //     // char * ret2 = glGetString(0x1F02);
    //     //char * ret3 = glGetString(0x1F02);
    //     //auto val = glGetString(i);
    //       auto proc_ = ((char* (*)(int))glfwGetProcAddress("glGetString"));
    //       char* ret2 = proc_(i);

    //     // const char * d;
    //     // int ret = glfwGetError(&d);
    //     // i = 0xabef;
    //     // test();
    //     // double ret = fmod(32.34, 12.56);
    //     return ret2;
    //     // return ret2;
    //   } : (void*)+[](int i) -> char* { 
    //     return 0;
    //   };//glfwGetProcAddress(name);
    //   };
    hybris_hook("eglGetProcAddress", (void*)/* eglGetProcAddress */windowManager->getProcAddrFunc());
    // static auto glGetString = (char*(*)(int))glfwGetProcAddress("glGetString");
    // static auto glHint = (char*(*)(int))glfwGetProcAddress("glHint");
    // static auto glEnable = (char*(*)(int))glfwGetProcAddress("glEnable");
    // static auto glDisable = (char*(*)(int))glfwGetProcAddress("glDisable");
    MinecraftUtils::setupGLES2Symbols( /* eglGetProcAddress */(void* (*)(const char*))windowManager->getProcAddrFunc());
    // MinecraftUtils::setupGLES2Symbols( (void* (*)(const char*))windowManager->getProcAddrFunc());
#ifdef USE_ARMHF_SUPPORT
    ArmhfSupport::install();
#endif

    struct Looper {
      int fdin;
      int fdout;
      int indent;
      void * data;
      int indent2;
      void * data2;
      char buf[10];
      OVERLAPPED alooperov;
    };
    static Looper looper;
    hybris_hook("ALooper_pollAll", (void *)+[](  int timeoutMillis,
    int *outFd,
    int *outEvents,
    void **outData) {
      fd_set rfds;
      struct timeval tv;
      DWORD retval;

      /* Watch stdin (fd 0) to see when it has input. */

      // FD_ZERO(&rfds);
      // FD_SET(looper.fd, &rfds);

      // tv.tv_sec = 0;
      // tv.tv_usec = 0;
      // ReadFileEx()

      // retval = select(looper.fd + 1, &rfds, NULL, NULL, &tv);
      // reval = WaitForSingleObject(_get_osfhandle(looper.fd), timeoutMillis);
      /* Don't rely on the value of tv now! */
      ResetEvent(looper.alooperov.hEvent);
      DWORD length;
      // DWORD readin;
    //   BOOL suc = ReadFileEx((HANDLE)_get_osfhandle(looper.fdin), &looper.buf, 10, &looper.alooperov, (LPOVERLAPPED_COMPLETION_ROUTINE)(void*)+[](
    // _In_    DWORD dwErrorCode,
    // _In_    DWORD dwNumberOfBytesTransfered,
    // _Inout_ LPOVERLAPPED lpOverlapped
    // ) {
    //     BOOL rt = SetEvent(looper.alooperov.hEvent);
    //   });
      BOOL suc = ReadFile((HANDLE)_get_osfhandle(looper.fdin), &looper.buf, 10, &length, &looper.alooperov);
      DWORD err = GetLastError();
      // auto _looper = &looper;
      if(err) {
          // BOOL ret = GetOverlappedResultEx((HANDLE)_get_osfhandle(looper.fdin), &looper.alooperov, &length, timeoutMillis, TRUE);
          // Windows 7 / Vista support, do it like linux version
          BOOL ret = GetOverlappedResult((HANDLE)_get_osfhandle(looper.fdin), &looper.alooperov, &length, FALSE);
        // retval = WaitForSingleObject( looper.alooperov.hEvent, timeoutMillis);
        err = GetLastError();
      }
      if (!err) {
          // printf("Data is available now.\n");
          *outData = looper.data;
          // GetOverlappedResult((HANDLE)_get_osfhandle(looper.fdin), &looper.alooperov, &length, FALSE);
          // int read2 = read(looper.fdin, looper.buf, length);
          _write(looper.fdout, looper.buf, length);
          return looper.indent;
          /* FD_ISSET(0, &rfds) will be true. */
      }

      return -3;
    });
    hybris_hook("ALooper_addFd", (void *)+[](  void *loopere ,
      int fd,
      int ident,
      int events,
      int(* callback)(int fd, int events, void *data),
      void *data) {
      int fdin = _dup(fd);
      int fd_[2];
      _pipe(fd_, 128, O_BINARY | _O_NOINHERIT);
      _dup2(fd_[0], fd);
      looper.fdin = fdin;
      looper.fdout = fd_[1];
      looper.indent = ident;
      looper.data = data;
      looper.alooperov.hEvent = CreateEventW(NULL, TRUE, TRUE, NULL);
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

    // Hook AppPlatform function directly (functions are too small for a jump instruction)
    // static vtable replace isn't working
    auto hide = (void*) + [](void* t) {
        window->setCursorDisabled(true);
    };
    auto show = (void*) + [](void* t) {
        window->setCursorDisabled(false);
    };

    hybris_hook("_ZN11AppPlatform16hideMousePointerEv", hide);
    hybris_hook("_ZN11AppPlatform16showMousePointerEv", show);

    hybris_hook("_ZN3web4http6client7details35verify_cert_chain_platform_specificERN5boost4asio3ssl14verify_contextERKSs", (void*) + []() {
        // Log::trace("web::http::client", "verify_cert_chain_platform_specific stub called");
        return true;
    });

    // Hack pthread to run mainthread on the main function #macoscacoa support
    static std::atomic_bool uithread_started;
    uithread_started = false;
    static void *(*main_routine)(void*) = nullptr;
    static void *main_arg = nullptr;
    static pthread_t mainthread = pthread_self();
    static int (*my_pthread_create)(pthread_t *thread, const pthread_attr_t *__attr,
                             void *(*start_routine)(void*), void *arg) = 0;
    my_pthread_create = (int (*)(pthread_t *thread, const pthread_attr_t *__attr,
                             void *(*start_routine)(void*), void *arg))get_hooked_symbol("pthread_create");
    hybris_hook("pthread_create", (void*) + [](pthread_t *thread, const pthread_attr_t *__attr,
        void *(*start_routine)(void*), void *arg) {
        if(uithread_started.load()) {
          return my_pthread_create(thread, __attr, start_routine, arg);
        } else {
          uithread_started = true;
          *thread = mainthread;
          main_routine = start_routine;
          main_arg = arg;
          return 0;
        }
      }
    );

    static auto my_fopen = (void*(*)(const char *filename, const char *mode))get_hooked_symbol("fopen");
    hybris_hook("fopen", (void*) + [](const char *filename, const char *mode) {
      if(!strcmp(filename, "/data/data/com.mojang.minecraftpe/games/com.mojang/minecraftpe/external_servers.txt")) {
          return my_fopen((PathHelper::getPrimaryDataDirectory() + (filename + 34)).data(), mode);
      } else {
        return my_fopen(filename, mode);
      }
    });

    #if defined( __i386__ ) && ! defined(_WIN32)
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_RESTART;
    act.sa_sigaction = [](int, siginfo_t *si, void *ptr) {
      *(char*)si->si_addr = 0x90;
      *((char*)si->si_addr + 1) = 0x90;
      Log::warn("Minecraft BUG", "SIGFPE Experimental patch applied, the Game will continue now");
    };
    sigaction(SIGFPE, &act, NULL);
    #endif

    Log::trace("Launcher", "Loading Minecraft library");
    void * handle = MinecraftUtils::loadMinecraftLib();
    Log::info("Launcher", "Loaded Minecraft library");
    Log::debug("Launcher", "Minecraft is at offset 0x%x", MinecraftUtils::getLibraryBase(handle));

    MinecraftUtils::initSymbolBindings(handle);

    auto ANativeActivity_onCreate = (ANativeActivity_createFunc*)hybris_dlsym(handle, "ANativeActivity_onCreate");
    ANativeActivity activity;
    memset(&activity, 0, sizeof(ANativeActivity));
    activity.internalDataPath = "./idata/";
    activity.externalDataPath = "./edata/";
    activity.obbPath = "./oob/";
    activity.sdkVersion = 28;
    jnivm::VM vm;
    activity.vm = vm.GetJavaVM();
    // activity.assetManager = (struct AAssetManager*)23;
    ANativeActivityCallbacks callbacks;
    memset(&callbacks, 0, sizeof(ANativeActivityCallbacks));
    activity.callbacks = &callbacks;
    activity.vm->GetEnv(&(void*&)activity.env, 0);
    jnienv = activity.env;
    vm.SetReserved3(handle);
    // Avoid using cd by hand
    chdir((PathHelper::getGameDir() + "/assets").data());
    void * onload = hybris_dlsym(handle, "JNI_OnLoad");
    jint ver = onload ? ((jint (*)(JavaVM* vm, void* reserved))onload)(activity.vm, 0) : 0;
    auto mainactivity = new com::mojang::minecraftpe::MainActivity();
    mainactivity->clazz = (java::lang::Class*)activity.env->FindClass("com/mojang/minecraftpe/MainActivity");//new jnivm::Object<void> { .cl = activity.env->FindClass("com/mojang/minecraftpe/MainActivity"), .value = new int() };
    mainactivity->window = window;
    activity.clazz = mainactivity;
    WindowCallbacks windowCallbacks (*window, activity);
    windowCallbacks.handle = handle;
    windowCallbacks.registerCallbacks();
    std::thread([&]() {
      void * nativeRegisterThis = hybris_dlsym(jnienv->functions->reserved3, "Java_com_mojang_minecraftpe_MainActivity_nativeRegisterThis");
      if(nativeRegisterThis)
        ((void(*)(JNIEnv * env, void*))nativeRegisterThis)(jnienv, activity.clazz);
      ANativeActivity_onCreate(&activity, 0, 0);
      // activity.callbacks->onInputQueueCreated(&activity, (AInputQueue*)2);
      activity.callbacks->onNativeWindowCreated(&activity, (ANativeWindow*)window.get());
      activity.callbacks->onStart(&activity);
    }).detach();
    while (!uithread_started.load()) std::this_thread::sleep_for(std::chrono::milliseconds(100));
    window->prepareRunLoop();
    // char * ret = glGetString(0x1F01);
    auto res = main_routine(main_arg);
    _Exit(0);
}

void printVersionInfo() {
    printf("mcpelauncher-client %s / manifest %s\n", CLIENT_GIT_COMMIT_HASH, MANIFEST_GIT_COMMIT_HASH);
#ifdef __i386__
    CpuId cpuid;
    printf("CPU: %s %s\n", cpuid.getManufacturer(), cpuid.getBrandString());
    printf("SSSE3 support: %s\n", cpuid.queryFeatureFlag(CpuId::FeatureFlag::SSSE3) ? "YES" : "NO");
#endif
    auto windowManager = GameWindowManager::getManager();
    GraphicsApi graphicsApi = GraphicsApi::OPENGL_ES2;
    auto window = windowManager->createWindow("mcpelauncher", 32, 32, graphicsApi);
    auto glGetString = (const char* (*)(int)) windowManager->getProcAddrFunc()("glGetString");
    printf("GL Vendor: %s\n", glGetString(0x1F00 /* GL_VENDOR */));
    printf("GL Renderer: %s\n", glGetString(0x1F01 /* GL_RENDERER */));
    printf("GL Version: %s\n", glGetString(0x1F02 /* GL_VERSION */));
    // printf("MSA daemon path: %s\n", XboxLiveHelper::findMsa().c_str());
}
