#include "../JNIBinding.h"

// Needed for loading pictures
jint android::os::Build::VERSION::SDK_INT = 28;

jnivm::android::view::View* android::view::Window::getDecorView(jnivm::ENV* env) {
    auto view = new jnivm::android::view::View();
    view->clazz = env->GetClass("android/view/View");
    return view;
}

jnivm::android::os::IBinder* android::view::View::getWindowToken(jnivm::ENV* env) {
    auto ib = new jnivm::android::os::IBinder();
    ib->clazz = env->GetClass("android/os/IBinder");
    return ib;
}

std::shared_ptr<jnivm::java::lang::String> android::content::Context::INPUT_METHOD_SERVICE = {};

void android::content::Context::startActivity(jnivm::ENV* env, std::shared_ptr<jnivm::android::content::Intent> arg0) {
    
}
std::shared_ptr<jnivm::java::lang::String> android::content::Context::getPackageName(jnivm::ENV* env) {
    return std::make_shared<jnivm::java::lang::String>("");
}

jnivm::java::io::File* android::content::ContextWrapper::getFilesDir(jnivm::ENV* env) {
    return new jnivm::java::io::File { "" };
}

jnivm::java::io::File* android::content::ContextWrapper::getCacheDir(jnivm::ENV* env) {
    return new jnivm::java::io::File { PathHelper::getCacheDirectory() };
}

jnivm::android::content::Context* android::app::NativeActivity::getApplicationContext(jnivm::ENV* env) {
    auto ctx = new jnivm::android::content::Context();
    ctx->clazz = env->GetClass("android/content/Context");
    return ctx;
}

std::shared_ptr<jnivm::java::lang::Class> java::lang::ClassLoader::loadClass(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    return env->GetClass(arg0->data());
}

std::shared_ptr<jnivm::java::lang::String> java::io::File::getPath(jnivm::ENV* env) {
    return std::shared_ptr<jnivm::java::lang::String>(shared_from_this(), this);
}