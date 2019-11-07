#include <log.h>
#include <hybris/hook.h>
#include <hybris/dlfcn.h>
#include <dlfcn.h>
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
#include "client_app_platform.h"
#include "xbox_live_patches.h"
#include "store.h"
#include "window_callbacks.h"
#include "http_request_stub.h"
#include "splitscreen_patch.h"
#include "gl_core_patch.h"
#include "xbox_live_helper.h"
#include "xbox_shutdown_patch.h"
#include "tts_patch.h"
#include "shader_error_patch.h"
#include "hbui_patch.h"
#ifdef USE_ARMHF_SUPPORT
#include "armhf_support.h"
#endif
#ifdef __i386__
#include "cpuid.h"
#include "legacy/legacy_patches.h"
#include "minecraft_game_wrapper.h"
#include "texel_aa_patch.h"
#endif
#include <build_info.h>
#include "native_activity.h"
// #include <EGL/egl.h>
#include <jnivm.h>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include "InputQueue.h"
#include <hybris/hook.h>

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

void log_attrib_list(const int * attrib_list) {
    if(attrib_list) {
        while(*attrib_list != EGL_NONE) {
            Log::debug("EGL", "Attribute %x value: %d", *attrib_list, attrib_list[1]);
            attrib_list += 2;
        }
    } else {
        Log::debug("EGL", "Attributes Empty");
    }
}

void dump(JNIEnv * env) {
    std::ofstream os("binding.cpp");
    os << jnivm::GeneratePreDeclaration(env);
    os << jnivm::GenerateHeader(env);
    os << jnivm::GenerateStubs(env);
    os << jnivm::GenerateJNIBinding(env);
}

int main(int argc, char *argv[]) {
    auto windowManager = GameWindowManager::getManager();
    CrashHandler::registerCrashHandler();
    MinecraftUtils::workaroundLocaleBug();

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

    GraphicsApi graphicsApi = GLCorePatch::mustUseDesktopGL() ? GraphicsApi::OPENGL : GraphicsApi::OPENGL_ES2;

    Log::trace("Launcher", "Loading hybris libraries");
    if (!disableFmod)
        MinecraftUtils::loadFMod();
    else
        MinecraftUtils::stubFMod();
    MinecraftUtils::setupHybris();

    Log::info("Launcher", "Creating window");
    WindowCallbacks::loadGamepadMappings();
    static auto window = windowManager->createWindow("Minecraft", windowWidth, windowHeight, graphicsApi);
    window->setIcon(PathHelper::getIconPath());
    window->show();
    hybris_hook("ANativeActivity_finish", (void *)+[](void *activity) {
      Log::warn("Launcher", "Android stub %s called", "ANativeActivity_finish");
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
            log_attrib_list(attrib_list);
      return native_window;
    });
    hybris_hook("eglGetConfigAttrib", (void *)+[](EGLDisplay display,
      EGLConfig config,
      EGLint attribute,
      EGLint * value) {
      *value = 8;
      return EGL_TRUE;
    });
    hybris_hook("eglCreateContext", (void *)+[](EGLDisplay display,
      EGLConfig config,
      EGLContext share_context,
      EGLint const * attrib_list) {
        log_attrib_list(attrib_list);
        // Force Opengl ES 2
        if(attrib_list[0] == 0x3098 && attrib_list[1] > 2) {
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
      if(draw) {
        ((GameWindow*)draw)->makeContextCurrent(true);
        GLCorePatch::onGLContextCreated();
        ShaderErrorPatch::onGLContextCreated();
      }
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
          *value = 1;
          break;
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
    hybris_hook("eglGetProcAddress", (void*) windowManager->getProcAddrFunc());
    MinecraftUtils::setupGLES2Symbols((void* (*)(const char*)) windowManager->getProcAddrFunc());
#ifdef USE_ARMHF_SUPPORT
    ArmhfSupport::install();
#endif

    hybris_hook("ANativeWindow_setBuffersGeometry", (void *)+[](void *window, int32_t width, int32_t height, int32_t format) {
    });
    hybris_hook("AAssetManager_open", (void *)+[](AAssetManager *mgr,
  const char *filename,
  int mode) {
      auto fullpath = PathHelper::getGameDir() + "assets/" + filename;
      return fopen(fullpath.data(), "r");
    });
    hybris_hook("AAsset_getLength", (void *)+[](FILE* file) {
      auto old = ftell(file);
      fseek(file, 0L, SEEK_END);
      auto size = ftell(file);
      fseek(file, old, SEEK_SET);
      return size;
    });
    hybris_hook("AAsset_getBuffer", (void *)+[](FILE* file) {
      auto old = ftell(file);
      fseek(file, 0L, SEEK_END);
      auto size = ftell(file);
      fseek(file, 0L, SEEK_SET);
      auto buffer = new uint8_t[size];
      auto read = fread(buffer, size, size, file);
      if(read != size) {
        Log::error("AAsset", "Failed to read whole file");
      }
      return buffer;
    });
    hybris_hook("AAsset_close", (void *)(void (*)())[]() {
    });
    hybris_hook("AAsset_read", (void *)(void (*)())[]() {
    });
    hybris_hook("AAsset_seek64", (void *)(void (*)())[]() {
    });
    hybris_hook("AAsset_getLength64", (void *)(void (*)())[]() {
    });
    hybris_hook("AAsset_getRemainingLength64", (void *)(void (*)())[]() {
    });
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

      InputQueue::instance->guard.lock();
      if(InputQueue::instance->queue.empty()) {
        InputQueue::instance->guard.unlock();
        return -3;
      }
      InputQueue::instance->guard.unlock();
      *outData = looper.data2;
      return looper.indent2;
    });
    hybris_hook("AInputQueue_getEvent", (void *)+[](void *queue,
    void **outEvent) -> int32_t {
      Log::warn("Launcher", "Android stub %s called", "AInputQueue_getEvent");
      InputQueue::instance->guard.lock();
      if(InputQueue::instance->queue.empty()) {
        InputQueue::instance->guard.unlock();
        return -1;
      }
      *outEvent = new InputQueue::KeyEvent (InputQueue::instance->queue.front());
      InputQueue::instance->queue.pop();
      InputQueue::instance->guard.unlock();
      return 0;
    });
    hybris_hook("AKeyEvent_getKeyCode", (void *)+[](const void *key_event) {
      return ((InputQueue::KeyEvent*)key_event)->key;
    });
    hybris_hook("AInputQueue_preDispatchEvent", (void *)+[](void *queue, void *event) ->int32_t {
      return 0;
    });
    hybris_hook("AInputQueue_finishEvent", (void *)+[](void *queue, void *event, int handled) {
      delete ((InputQueue::KeyEvent*)event);
    });
    hybris_hook("AKeyEvent_getAction", (void *)+[](const void *key_event) {
      switch (((InputQueue::KeyEvent*)key_event)->action)
      {
      case KeyAction::PRESS :
          return 0;
      case KeyAction::REPEAT :
           return 2;
      case KeyAction::RELEASE :
          return 1;
      }
      return 0;
    });
    hybris_hook("AMotionEvent_getAxisValue", (void *)(void (*)())[]() {
    });
    hybris_hook("AKeyEvent_getRepeatCount", (void *)+[](const void *key_event) {
      return ((InputQueue::KeyEvent*)key_event)->repeat;
    });
    hybris_hook("AKeyEvent_getMetaState", (void *)+[](const void *key_event) {
      return ((InputQueue::KeyEvent*)key_event)->metastate;
    });
    hybris_hook("AInputEvent_getDeviceId", (void *)(void (*)())[]() {
    });
    hybris_hook("AInputEvent_getType", (void *)+[]() {
      return 1;
    });
    hybris_hook("AInputEvent_getSource", (void *)+[]() {
      return 1;
    });
    hybris_hook("AMotionEvent_getAction", (void *)(void (*)())[]() {
    });
    hybris_hook("AMotionEvent_getPointerId", (void *)(void (*)())[]() {
    });
    hybris_hook("AMotionEvent_getX", (void *)(void (*)())[]() {
    });
    hybris_hook("AMotionEvent_getRawX", (void *)(void (*)())[]() {
    });
    hybris_hook("AMotionEvent_getY", (void *)(void (*)())[]() {
    });
    hybris_hook("AMotionEvent_getRawY", (void *)(void (*)())[]() {
    });
    hybris_hook("AMotionEvent_getPointerCount", (void *)(void (*)())[]() {
    });
    hybris_hook("AConfiguration_new", (void *)(void (*)())[]() {
    });
    hybris_hook("AConfiguration_fromAssetManager", (void *)(void (*)())[]() {
    });
    hybris_hook("AConfiguration_getLanguage", (void *)+[](class AConfiguration *config, char *outLanguage) {
      outLanguage[0] = 'e';
      outLanguage[1] = 'n';
    });
    hybris_hook("AConfiguration_getCountry", (void *)+[](class AConfiguration *config,
    char *outCountry) {
      outCountry[0] = 'e';
      outCountry[1] = 'n';
    });
    hybris_hook("ALooper_prepare", (void *)(void (*)())[]() {
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
    hybris_hook("AInputQueue_detachLooper", (void *)(void (*)())[]() {
    });
    hybris_hook("AConfiguration_delete", (void *)(void (*)())[]() {
    });
    hybris_hook("AInputQueue_attachLooper", (void *)+[](  void *queue,
    void *looper2,
    int ident,
    void* callback,
    void *data) {
      looper.indent2 = ident;
      looper.data2 = data;
    });
    hybris_hook("AAssetManager_openDir", (void *)+[]( AAssetManager *mgr, const char *dirName) {
      Log::warn("Launcher", "Android stub %s called", "AAssetManager_openDir");
      if(*dirName == '/') {
        return (DIR *)nullptr;
      }
      auto fullpath =  PathHelper::getGameDir() + "assets/" + dirName;
      return opendir(fullpath.data());
    });
    hybris_hook("AAssetDir_getNextFileName", (void *)+[](DIR *assetDir) {
      Log::warn("Launcher", "Android stub %s called",
                "AAssetDir_getNextFileName");
      if(assetDir) {
        auto dp = readdir(assetDir);
        if(dp) {
          return dp->d_name;
        }
      }
      return (char*)0;
    });
    hybris_hook("AAssetDir_close", (void *)+[](DIR *assetDir) {
      Log::warn("Launcher", "Android stub %s called", "AAssetDir_close");
      closedir(assetDir);
    });
    hybris_hook("AAssetManager_fromJava", (void *)(void (*)())[]() {
      Log::warn("Launcher", "Android stub %s called", "AAssetManager_fromJava");
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

    Log::trace("Launcher", "Loading Minecraft library");
    void * handle = MinecraftUtils::loadMinecraftLib();
    Log::info("Launcher", "Loaded Minecraft library");
    Log::debug("Launcher", "Minecraft is at offset 0x%x", MinecraftUtils::getLibraryBase(handle));

    ModLoader modLoader;
    modLoader.loadModsFromDirectory(PathHelper::getPrimaryDataDirectory() + "mods/");
    MinecraftUtils::initSymbolBindings(handle);
    SharedConstants::MajorVersion = new int[1] { 1 };
    SharedConstants::MinorVersion = new int[1] { 14 };
    SharedConstants::PatchVersion = new int[1] { 0 };
    SharedConstants::RevisionVersion = new int[1] { 2 };
    Log::info("Launcher", "Applying patches");
    // XboxLivePatches::install(handle);
    void* ptr = hybris_dlsym(handle, "_ZN3web4http6client7details35verify_cert_chain_platform_specificERN5boost4asio3ssl14verify_contextERKSs");
    PatchUtils::patchCallInstruction(ptr, (void*) + []() {
        Log::trace("web::http::client", "verify_cert_chain_platform_specific stub called");
        return true;
    }, true);

    Log::trace("Launcher", "Initializing AppPlatform (create instance)");
    PatchUtils::patchCallInstruction(hybris_dlsym(handle, "_ZN11AppPlatform16hideMousePointerEv"), (void*) + [](void*) {
        window->setCursorDisabled(true);
    }, true);

    PatchUtils::patchCallInstruction(hybris_dlsym(handle, "_ZN11AppPlatform16showMousePointerEv"), (void*) + [](void*) {
        window->setCursorDisabled(false);
    }, true);

    auto ANativeActivity_onCreate = (ANativeActivity_createFunc*)hybris_dlsym(handle, "ANativeActivity_onCreate");
    ANativeActivity activity;
    memset(&activity, 0, sizeof(ANativeActivity));
    activity.internalDataPath = "./idata";
    activity.externalDataPath = "./edata";
    activity.obbPath = "./obb";
    activity.sdkVersion = 28;
    activity.vm = jnivm::createJNIVM();
    // activity.assetManager = (struct AAssetManager*)23;
    ANativeActivityCallbacks callbacks;
    memset(&callbacks, 0, sizeof(ANativeActivityCallbacks));
    activity.callbacks = &callbacks;
    activity.vm->GetEnv(&(void*&)activity.env, 0);
    jnienv = activity.env;
    (void*&)activity.env->functions->reserved3 = hybris_dlsym(handle, "Java_com_mojang_minecraftpe_store_NativeStoreListener_onStoreInitialized");
    (void*&)activity.env->functions->reserved2 = hybris_dlsym(handle, "Java_com_mojang_minecraftpe_store_NativeStoreListener_onStoreInitialized");
    // Avoid using cd by hand
    chdir((PathHelper::getGameDir() + "/assets").data());
    // replace dead start with nops
    memset((char*)hybris_dlsym(handle, "android_main") + 394, 0x90, 18);
    jint ver = ((jint (*)(JavaVM* vm, void* reserved))hybris_dlsym(handle, "JNI_OnLoad"))(activity.vm, 0);
    activity.clazz = new jnivm::Object<void> { .cl = activity.env->FindClass("com/mojang/minecraftpe/MainActivity"), .value = new int() };
    WindowCallbacks windowCallbacks (*window, activity);
    windowCallbacks.handle = handle;
    windowCallbacks.registerCallbacks();
    std::thread androidctrl([&]() {
      ANativeActivity_onCreate(&activity, 0, 0);
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      activity.callbacks->onInputQueueCreated(&activity, (AInputQueue*)2);
      activity.callbacks->onNativeWindowCreated(&activity, (ANativeWindow*)window.get());
      activity.callbacks->onStart(&activity);
      activity.callbacks->onResume(&activity);
    });
    while (!uithread_started.load()) std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto res = main_routine(main_arg);
    return 0;
}

void printVersionInfo() {
    printf("mcpelauncher-client %s / manifest %s\n", CLIENT_GIT_COMMIT_HASH, MANIFEST_GIT_COMMIT_HASH);
#ifdef __i386__
    CpuId cpuid;
    printf("CPU: %s %s\n", cpuid.getManufacturer(), cpuid.getBrandString());
    printf("SSSE3 support: %s\n", cpuid.queryFeatureFlag(CpuId::FeatureFlag::SSSE3) ? "YES" : "NO");
#endif
    auto windowManager = GameWindowManager::getManager();
    GraphicsApi graphicsApi = GLCorePatch::mustUseDesktopGL() ? GraphicsApi::OPENGL : GraphicsApi::OPENGL_ES2;
    auto window = windowManager->createWindow("mcpelauncher", 32, 32, graphicsApi);
    auto glGetString = (const char* (*)(int)) windowManager->getProcAddrFunc()("glGetString");
    printf("GL Vendor: %s\n", glGetString(0x1F00 /* GL_VENDOR */));
    printf("GL Renderer: %s\n", glGetString(0x1F01 /* GL_RENDERER */));
    printf("GL Version: %s\n", glGetString(0x1F02 /* GL_VERSION */));
    printf("MSA daemon path: %s\n", XboxLiveHelper::findMsa().c_str());
}
