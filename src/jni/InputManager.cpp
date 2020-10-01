#include "../JNIBinding.h"

jboolean android::view::inputmethod::InputMethodManager::showSoftInput(ENV *env, std::shared_ptr<jnivm::android::view::View> arg0, jint arg1) {
    return true;
}

jboolean android::view::inputmethod::InputMethodManager::hideSoftInputFromWindow(ENV *env, std::shared_ptr<jnivm::android::os::IBinder> arg0, jint arg1) {
    return true;
}