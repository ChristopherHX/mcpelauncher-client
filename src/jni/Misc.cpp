#include "../JNIBinding.h"

// Needed for loading pictures
jint android::os::Build::VERSION::SDK_INT = 28;

std::shared_ptr<jnivm::android::view::View> android::view::Window::getDecorView(ENV *env) {
    auto view = std::make_shared<jnivm::android::view::View>();
    auto cl = (jnivm::java::lang::Class*)env->env.FindClass("android/view/View");
    view->clazz = { cl->shared_from_this(), cl };
    return view;
}

std::shared_ptr<jnivm::android::os::IBinder> android::view::View::getWindowToken(ENV *env) {
    auto ib = std::make_shared<jnivm::android::os::IBinder>();
    auto cl = (jnivm::java::lang::Class*)env->env.FindClass("android/os/IBinder");
    ib->clazz = { cl->shared_from_this(), cl };
    return ib;
}

std::shared_ptr<jnivm::java::lang::String> android::content::Context::INPUT_METHOD_SERVICE = {};

void android::content::Context::startActivity(ENV *env, std::shared_ptr<jnivm::android::content::Intent> arg0) {
    
}
std::shared_ptr<jnivm::java::lang::String> android::content::Context::getPackageName(ENV *env) {
    // return std::make_shared<jnivm::java::lang::String>("com.mojang.minecraftpe");
    return nullptr;
}

std::shared_ptr<jnivm::java::io::File> android::content::ContextWrapper::getFilesDir(ENV *env) {
    return std::make_shared<jnivm::java::io::File>("");
}

std::shared_ptr<jnivm::java::io::File> android::content::ContextWrapper::getCacheDir(ENV *env) {
    return std::make_shared<jnivm::java::io::File>(PathHelper::getCacheDirectory());
}

std::shared_ptr<jnivm::android::content::Context> android::app::NativeActivity::getApplicationContext(ENV *env) {
    auto ctx = std::make_shared<jnivm::android::content::Context>();
    auto cl = (jnivm::java::lang::Class*)env->env.FindClass("android/content/Context");
    ctx->clazz = { cl->shared_from_this(), cl };
    return ctx;
}

std::shared_ptr<jnivm::java::lang::Class> java::lang::ClassLoader::loadClass(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    auto cl = (jnivm::java::lang::Class*)env->env.FindClass(arg0->data());
    return { cl->shared_from_this(), cl };
}

std::shared_ptr<jnivm::java::lang::String> java::io::File::getPath(ENV *env) {
    return { shared_from_this(), this };
}