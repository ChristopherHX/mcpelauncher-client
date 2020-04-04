#include "../JNIBinding.h"

jboolean android::view::inputmethod::InputMethodManager::showSoftInput(jnivm::ENV* env, jnivm::android::view::View* arg0, jint arg1) {
    return true;
}

jboolean android::view::inputmethod::InputMethodManager::hideSoftInputFromWindow(jnivm::ENV* env, jnivm::android::os::IBinder* arg0, jint arg1) {
    return true;
}