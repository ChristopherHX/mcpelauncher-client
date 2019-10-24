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
#include <EGL/egl.h>
#include <jnivm.h>

static std::unique_ptr<ClientAppPlatform> appPlatform;

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
//     if (graphicsApi == GraphicsApi::OPENGL)
//         GLCorePatch::install(handle);
//     LegacyPatches::install(handle);

    Log::info("Launcher", "Creating window");
    WindowCallbacks::loadGamepadMappings();
    static auto window = windowManager->createWindow("Minecraft", windowWidth, windowHeight, graphicsApi);
    window->setIcon(PathHelper::getIconPath());
    window->show();
    // HybrisUtils::stubSymbols(egl_symbols, (void*) +[]() {
    //     Log::warn("Launcher", "EGL stub called");
    //     // return 0;
    // });//eglChooseConfig
    hybris_hook("eglChooseConfig", (void *)+[](EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config) {
log_attrib_list(attrib_list);
   Log::warn("Launcher", "EGL stub %s called", "eglChooseConfig");
   *num_config = 1;
   return EGL_TRUE;
});
        hybris_hook("eglGetError", (void *)(void (*)())[]() {
   Log::warn("Launcher", "EGL stub %s called", "eglGetError");
});
        hybris_hook("eglCreateWindowSurface", (void *)+[](EGLDisplay display,
 	EGLConfig config,
 	NativeWindowType native_window,
 	EGLint const * attrib_list) {
         log_attrib_list(attrib_list);
   Log::warn("Launcher", "EGL stub %s called", "eglCreateWindowSurface");
   return native_window;
});
        hybris_hook("eglGetConfigAttrib", (void *)+[](EGLDisplay display,
 	EGLConfig config,
 	EGLint attribute,
 	EGLint * value) {
   Log::warn("Launcher", "EGL stub %s called %x", "eglGetConfigAttrib", (int)attribute);
   *value = 8;
   return EGL_TRUE;
});
        hybris_hook("eglCreateContext", (void *)+[](EGLDisplay display,
 	EGLConfig config,
 	EGLContext share_context,
 	EGLint const * attrib_list) {
   Log::warn("Launcher", "EGL stub %s called", "eglCreateContext");
    log_attrib_list(attrib_list);
  //  glfwGetEGLContext(display)
  return 1;
});
        hybris_hook("eglDestroySurface", (void *)(void (*)())[]() {
   Log::warn("Launcher", "EGL stub %s called", "eglDestroySurface");
});
//         hybris_hook("eglSwapBuffers", (void *)+[](GLFWwindow *window,
//  	EGLSurface surface) {
//    Log::warn("Launcher", "EGL stub %s called", "eglSwapBuffers");
//    return glfwSwapBuffers(window);
// });
hybris_hook("eglSwapBuffers", (void *)+[](EGLDisplay *display,
 	EGLSurface surface) {
   Log::warn("Launcher", "EGL stub %s called", "eglSwapBuffers");
    if(surface) {
        ((GameWindow*)surface)->swapBuffers();
    }
  //  return glfwSwapBuffers(window);
});
        hybris_hook("eglMakeCurrent", (void *)+[](EGLDisplay display,
 	EGLSurface draw,
 	EGLSurface read,
 	EGLContext context) {
   Log::warn("Launcher", "EGL stub %s called", "eglMakeCurrent");
  //  glfwMakeContextCurrent();
  if(draw) {
    ((GameWindow*)draw)->makeContextCurrent();
    GLCorePatch::onGLContextCreated();
    ShaderErrorPatch::onGLContextCreated();
  }
   return EGL_TRUE;
});
        hybris_hook("eglDestroyContext", (void *)(void (*)())[]() {
   Log::warn("Launcher", "EGL stub %s called", "eglDestroyContext");
  //  glfwDestroyWindow()
});
        hybris_hook("eglTerminate", (void *)(void (*)())[]() {
   Log::warn("Launcher", "EGL stub %s called", "eglTerminate");
  //  glfwTerminate();
});
        hybris_hook("eglGetDisplay", (void *)+[](NativeDisplayType native_display) {
   Log::warn("Launcher", "EGL stub %s called", "eglGetDisplay");
   return 1; 
});
        hybris_hook("eglInitialize", (void *)+[](void* display,
 	uint32_t * major,
 	uint32_t * minor) {
    //  glfwInit();
  //  Log::warn("Launcher", "EGL stub %s called", "eglInitialize");
  //  if(major) {
  //    *major = 1;
  //  }
  // if(minor) {
  //    *minor = 4;
  //  }
    // auto egl = dlopen("/usr/lib/i386-linux-gnu/libEGL.so", RTLD_LAZY);
    // auto qustr = (const char (*)(void* display, uint32_t * major, uint32_t * minor))dlsym(egl, "eglInitialize");
    // auto ret = qustr(display, major, minor);
    // dlclose(egl);
//    return ret;
    return EGL_TRUE;
});
        hybris_hook("eglQuerySurface", (void *) + [](void* dpy, EGLSurface surface, EGLint attribute, EGLint *value) {
   Log::warn("Launcher", "EGL stub %s called %x", "eglQuerySurface", (int)attribute);
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
   return EGL_TRUE;//eglQuerySurface(glfwGetEGLDisplay(), glfwGetEGLSurface(dpy), attribute, value);
});
        hybris_hook("eglSwapInterval", (void *)+[](EGLDisplay display,
 	EGLint interval) {
   Log::warn("Launcher", "EGL stub %s called", "eglSwapInterval");
  //  glfwSwapInterval(interval);
    window->swapInterval(interval);
   return EGL_TRUE;
});
hybris_hook("eglQueryString", (void *)+[](void* display, int32_t name) {
    // Log::warn("Launcher", "EGL stub %s called", "eglQueryString");
    // auto egl = dlopen("/usr/lib/i386-linux-gnu/libEGL.so", RTLD_LAZY);
    // auto qustr = (const char (*)(EGLDisplay dpy, EGLint name))dlsym(egl, "eglQueryString");
    // auto ret = qustr(display, (EGLint) name);
    // dlclose(egl);
    // return ret;
    return 0;
//    switch (name) {
//     case 12373:
//       return "EGL_KHR_image EGL_KHR_image_base EGL_KHR_image_pixmap EGL_KHR_vg_parent_image EGL_KHR_gl_texture_2D_image EGL_KHR_gl_texture_cubemap_image EGL_KHR_lock_surface";
//     case 12372:
//       return "1.4";
//     case 12371:
//       return "Generic";
//     default:
//       return "Unknown";
//    }
});
    // static std::unordered_map<std::string, void*> eglproc({
    //     { "glGetString", (void*)+[](uint32_t name) {
    //         Log::warn("Launcher", "EGL glGetString stub called");
    //         return "3.0 Mesa 10.1.3";
    //     } }
    // });
    // hybris_hook("eglGetProcAddress", (void*) +[](	char const * procname) {
    //     Log::warn("Launcher", "EGL stub called %s", procname);
    //     auto proc = eglproc.find(procname);
    //     if(proc != eglproc.end()) {
    //         return proc->second;
    //     }
    //     return (void*)+[]() {
    //     // Log::warn("Launcher", "EGL stub called");
    //     };
    // });
    hybris_hook("eglGetProcAddress", (void*) windowManager->getProcAddrFunc());
    MinecraftUtils::setupGLES2Symbols((void* (*)(const char*)) windowManager->getProcAddrFunc());
#ifdef USE_ARMHF_SUPPORT
    ArmhfSupport::install();
#endif

    Log::trace("Launcher", "Loading Minecraft library");
    void* handle = MinecraftUtils::loadMinecraftLib();
    Log::info("Launcher", "Loaded Minecraft library");
    Log::debug("Launcher", "Minecraft is at offset 0x%x", MinecraftUtils::getLibraryBase(handle));

    ModLoader modLoader;
    modLoader.loadModsFromDirectory(PathHelper::getPrimaryDataDirectory() + "mods/");
    MinecraftUtils::initSymbolBindings(handle);
    // Log::info("Launcher", "Game version: %s", Common::getGameVersionStringNet().c_str());
    SharedConstants::RevisionVersion = new int[1] { 1 };
    SharedConstants::MajorVersion = new int[1] { 0 };
    SharedConstants::MinorVersion = new int[1] { 14 };
    SharedConstants::PatchVersion = new int[1] { 2 };
//     Log::info("Launcher", "Applying patches");
//     LauncherStore::install(handle);
//     TTSPatch::install(handle);
//     XboxLivePatches::install(handle);
    void* ptr = hybris_dlsym(handle, "_ZN3web4http6client7details35verify_cert_chain_platform_specificERN5boost4asio3ssl14verify_contextERKSs");
    PatchUtils::patchCallInstruction(ptr, (void*) + []() {
    Log::trace("web::http::client", "verify_cert_chain_platform_specific stub called");
    return true;
}, true);
        ShaderErrorPatch::install(handle);

// #ifdef __i386__
//     XboxShutdownPatch::install(handle);
//     TexelAAPatch::install(handle);
// #endif
//     LinuxHttpRequestHelper::install(handle);
//     HbuiPatch::install(handle);
//     SplitscreenPatch::install(handle);

//     SplitscreenPatch::onGLContextCreated();

//     Log::trace("Launcher", "Initializing AppPlatform (vtable)");
//     ClientAppPlatform::initVtable(handle);
    Log::trace("Launcher", "Initializing AppPlatform (create instance)");
    auto ANativeActivity_onCreate = (ANativeActivity_createFunc*)hybris_dlsym(handle, "ANativeActivity_onCreate");
    ANativeActivity activity;
    memset(&activity, 0, sizeof(ANativeActivity));
    activity.internalDataPath = "./idata";
    activity.externalDataPath = "./edata";
    activity.obbPath = "./obb";
    activity.sdkVersion = 200;
    activity.vm = jnivm::createJNIVM();
    ANativeActivityCallbacks callbacks;
    memset(&callbacks, 0, sizeof(ANativeActivityCallbacks));
    activity.callbacks = &callbacks;
    activity.vm->GetEnv(&(void*&)activity.env, 0);
    // Resolable by correctly implement Alooper
    memset((char*)hybris_dlsym(handle, "android_main") + 394, 0x90, 18);
    jint ver = ((jint (*)(JavaVM* vm, void* reserved))hybris_dlsym(handle, "JNI_OnLoad"))(activity.vm, 0);
    // activity.clazz = new jnivm::Object<void> { .cl = activity.env->FindClass("com/mojang/minecraftpe/MainActivity"), .value = new int() };
    // ANativeActivity_onCreate(&activity, 0, 0);
    // appPlatform = std::unique_ptr<ClientAppPlatform>(new ClientAppPlatform());
    // appPlatform->setWindow(window);
    // Log::trace("Launcher", "Initializing AppPlatform (initialize call)");
    // if (MinecraftVersion::isAtLeast(0, 17, 2))
    //     appPlatform->initialize();
    // if (MinecraftVersion::isAtLeast(0, 16) && !MinecraftVersion::isAtLeast(1, 13, 0, 9))
    //     mce::Platform::OGL::InitBindings();

    // // Log::info("Launcher", "OpenGL: version: %s, renderer: %s, vendor: %s",
    // //           gl::getOpenGLVersion().c_str(), gl::getOpenGLRenderer().c_str(), gl::getOpenGLVendor().c_str());



    // Log::trace("Launcher", "Initializing MinecraftGame (create instance)");
    // std::unique_ptr<MinecraftGameWrapper> game (MinecraftGameWrapper::create(argc, argv));
    // Log::trace("Launcher", "Initializing MinecraftGame (init call)");
    // AppContext ctx;
    // ctx.platform = appPlatform.get();
    // ctx.doRender = true;
    // game->init(ctx);
    // Log::info("Launcher", "Game initialized");

    // modLoader.onGameInitialized((MinecraftGame*) game->getWrapped());

    // WindowCallbacks windowCallbacks (*game, *appPlatform, *window);
    // windowCallbacks.setPixelScale(pixelScale);
    // windowCallbacks.registerCallbacks();
    // if (MinecraftVersion::isAtLeast(1, 8)) {
    //     game->getWrapped()->doPrimaryClientReadyWork([&windowCallbacks]() {
    //         windowCallbacks.handleInitialWindowSize();
    //     });
    // } else {
    //     windowCallbacks.handleInitialWindowSize();
    // }
    // window->runLoop();

    // game->leaveGame();
    // game.reset();

    // MinecraftUtils::workaroundShutdownCrash(handle);
    // XboxLivePatches::workaroundShutdownFreeze(handle);
    // XboxShutdownPatch::notifyShutdown();

    // XboxLiveHelper::getInstance().shutdown();
    // appPlatform->teardown();
    // appPlatform->setWindow(nullptr);
    // activity.callbacks->onInputQueueCreated(&activity, (AInputQueue*)2);
    // activity.callbacks->onNativeWindowCreated(&activity, (ANativeWindow*)window.get());
    // activity.callbacks->onStart(&activity);
    // activity.callbacks->onResume(&activity);
    // activity.callbacks->onWindowFocusChanged(&activity, true);
    // std::this_thread::sleep_for(std::chrono::hours(10));
    std::cout << jnivm::GeneratePreDeclaration(activity.env);
    std::cout << jnivm::GenerateHeader(activity.env);
    std::cout << jnivm::GenerateStubs(activity.env);
    std::cout << jnivm::GenerateJNIBinding(activity.env);
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