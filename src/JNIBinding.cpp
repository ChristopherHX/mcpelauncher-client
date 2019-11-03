
#include <tuple>
#include <vector>
#include <fstream>
#include <jni.h>
#include <jnivm.h>
#include <log.h>
#include <mcpelauncher/path_helper.h>
#include <sstream>

namespace com {
    namespace mojang {
        namespace minecraftpe {
            class MainActivity;
            class HardwareInformation;
            namespace store {
                class NativeStoreListener;
                class Product;
                class Purchase;
                class StoreFactory;
                class StoreListener;
                class Store;
                class ExtraLicenseResponseData;
            }
        }
    }
    namespace microsoft {
        namespace xbox {
            namespace idp {
                namespace interop {
                    class Interop;
                    class LocalConfig;
                    class XboxLiveAppConfig;
                }
                namespace util {
                    class HttpCall;
                    class AuthFlowResult;
                }
            }
        }
        namespace xboxtcui {
            class Interop;
        }
    }
}
namespace android {
    namespace os {
        class Build;
        class IBinder;
    }
    namespace view {
        class Window;
        class View;
        namespace inputmethod {
            class InputMethodManager;
        }
    }
    namespace content {
        class Context;
        class Intent;
        class ContextWrapper;
    }
    namespace app {
        class NativeActivity;
    }
}
namespace java {
    namespace lang {
        class String;
        class Object;
        class ClassLoader;
        class Class;
    }
    namespace io {
        class File;
    }
}
class com::mojang::minecraftpe::MainActivity {
public:
    static void saveScreenshot(JNIEnv *, jnivm::Object<java::lang::String>*, jint, jint, jnivm::Array<jint>*);
    void postScreenshotToFacebook(JNIEnv *, jnivm::Object<java::lang::String>*, jint, jint, jnivm::Array<jint>*);
    jnivm::Array<jint>* getImageData(JNIEnv *, jnivm::Object<java::lang::String>*);
    jnivm::Array<jbyte>* getFileDataBytes(JNIEnv *, jnivm::Object<java::lang::String>*);
    void displayDialog(JNIEnv *, jint);
    void tick(JNIEnv *);
    void quit(JNIEnv *);
    void initiateUserInput(JNIEnv *, jint);
    jint getUserInputStatus(JNIEnv *);
    jnivm::Array<jnivm::Object<java::lang::String>*>* getUserInputString(JNIEnv *);
    jint checkLicense(JNIEnv *);
    jboolean hasBuyButtonWhenInvalidLicense(JNIEnv *);
    void buyGame(JNIEnv *);
    void vibrate(JNIEnv *, jint);
    void setIsPowerVR(JNIEnv *, jboolean);
    jboolean isNetworkEnabled(JNIEnv *, jboolean);
    jfloat getPixelsPerMillimeter(JNIEnv *);
    jnivm::Object<java::lang::String>* getPlatformStringVar(JNIEnv *, jint);
    jnivm::Object<java::lang::Object>* getSystemService(JNIEnv *, jnivm::Object<java::lang::String>*);
    jnivm::Object<android::view::Window>* getWindow(JNIEnv *);
    jint getKeyFromKeyCode(JNIEnv *, jint, jint, jint);
    void updateLocalization(JNIEnv *, jnivm::Object<java::lang::String>*, jnivm::Object<java::lang::String>*);
    void showKeyboard(JNIEnv *, jnivm::Object<java::lang::String>*, jint, jboolean, jboolean, jboolean);
    void hideKeyboard(JNIEnv *);
    jfloat getKeyboardHeight(JNIEnv *);
    void updateTextboxText(JNIEnv *, jnivm::Object<java::lang::String>*);
    jint getCursorPosition(JNIEnv *);
    jnivm::Object<java::lang::String>* getAccessToken(JNIEnv *);
    jnivm::Object<java::lang::String>* getClientId(JNIEnv *);
    jnivm::Object<java::lang::String>* getProfileId(JNIEnv *);
    jnivm::Object<java::lang::String>* getProfileName(JNIEnv *);
    jnivm::Array<jnivm::Object<java::lang::String>*>* getBroadcastAddresses(JNIEnv *);
    jnivm::Array<jnivm::Object<java::lang::String>*>* getIPAddresses(JNIEnv *);
    jlong getTotalMemory(JNIEnv *);
    jlong getMemoryLimit(JNIEnv *);
    jlong getUsedMemory(JNIEnv *);
    jlong getFreeMemory(JNIEnv *);
    void launchUri(JNIEnv *, jnivm::Object<java::lang::String>*);
    void setClipboard(JNIEnv *, jnivm::Object<java::lang::String>*);
    void share(JNIEnv *, jnivm::Object<java::lang::String>*, jnivm::Object<java::lang::String>*, jnivm::Object<java::lang::String>*);
    jnivm::Object<android::content::Intent>* createAndroidLaunchIntent(JNIEnv *);
    jlong calculateAvailableDiskFreeSpace(JNIEnv *, jnivm::Object<java::lang::String>*);
    jnivm::Object<java::lang::String>* getExternalStoragePath(JNIEnv *);
    void requestStoragePermission(JNIEnv *, jint);
    jboolean hasWriteExternalStoragePermission(JNIEnv *);
    void deviceIdCorrelationStart(JNIEnv *);
    jboolean isMixerCreateInstalled(JNIEnv *);
    void navigateToPlaystoreForMixerCreate(JNIEnv *);
    jboolean launchMixerCreateForBroadcast(JNIEnv *);
    jboolean isTTSEnabled(JNIEnv *);
    jnivm::Object<com::mojang::minecraftpe::HardwareInformation>* getHardwareInfo(JNIEnv *);
    void setCachedDeviceId(JNIEnv *, jnivm::Object<java::lang::String>*);
    void setLastDeviceSessionId(JNIEnv *, jnivm::Object<java::lang::String>*);
    jnivm::Object<java::lang::String>* getLastDeviceSessionId(JNIEnv *);
    jint getAPIVersion(JNIEnv *, jnivm::Object<java::lang::String>*);
    jnivm::Object<java::lang::String>* getSecureStorageKey(JNIEnv *, jnivm::Object<java::lang::String>*);
    void setSecureStorageKey(JNIEnv *, jnivm::Object<java::lang::String>*, jnivm::Object<java::lang::String>*);
    void trackPurchaseEvent(JNIEnv *, jnivm::Object<java::lang::String>*, jnivm::Object<java::lang::String>*, jnivm::Object<java::lang::String>*, jnivm::Object<java::lang::String>*, jnivm::Object<java::lang::String>*, jnivm::Object<java::lang::String>*, jnivm::Object<java::lang::String>*, jnivm::Object<java::lang::String>*);
    void sendBrazeEvent(JNIEnv *, jnivm::Object<java::lang::String>*);
    void sendBrazeEventWithProperty(JNIEnv *, jnivm::Object<java::lang::String>*, jnivm::Object<java::lang::String>*, jint);
    void sendBrazeEventWithStringProperty(JNIEnv *, jnivm::Object<java::lang::String>*, jnivm::Object<java::lang::String>*, jnivm::Object<java::lang::String>*);
    void sendBrazeToastClick(JNIEnv *);
    void sendBrazeDialogButtonClick(JNIEnv *, jint);
    void pickImage(JNIEnv *, jlong);
    void setFileDialogCallback(JNIEnv *, jlong);
    jnivm::Object<java::lang::String>* getLegacyDeviceID(JNIEnv *);
    jnivm::Object<java::lang::String>* createUUID(JNIEnv *);
    jboolean hasHardwareKeyboard(JNIEnv *);
    void startTextToSpeech(JNIEnv *, jnivm::Object<java::lang::String>*);
    void stopTextToSpeech(JNIEnv *);
    jboolean isTextToSpeechInProgress(JNIEnv *);
    void setTextToSpeechEnabled(JNIEnv *, jboolean);
    jint getScreenWidth(JNIEnv *);
    jint getScreenHeight(JNIEnv *);
    jnivm::Object<java::lang::String>* getDeviceModel(JNIEnv *);
    jint getAndroidVersion(JNIEnv *);
    jnivm::Object<java::lang::String>* getLocale(JNIEnv *);
    jboolean isTablet(JNIEnv *);
    jnivm::Object<java::lang::ClassLoader>* getClassLoader(JNIEnv *);
};
class com::mojang::minecraftpe::HardwareInformation {
public:
    static jnivm::Object<java::lang::String>* getDeviceModelName(JNIEnv *);
    static jnivm::Object<java::lang::String>* getAndroidVersion(JNIEnv *);
    static jnivm::Object<java::lang::String>* getCPUType(JNIEnv *);
    static jnivm::Object<java::lang::String>* getCPUName(JNIEnv *);
    static jnivm::Object<java::lang::String>* getCPUFeatures(JNIEnv *);
    static jint getNumCores(JNIEnv *);
    jnivm::Object<java::lang::String>* getSecureId(JNIEnv *);
    static jnivm::Object<java::lang::String>* getSerialNumber(JNIEnv *);
    static jnivm::Object<java::lang::String>* getBoard(JNIEnv *);
    jnivm::Object<java::lang::String>* getInstallerPackageName(JNIEnv *);
    jint getSignaturesHashCode(JNIEnv *);
    jboolean getIsRooted(JNIEnv *);
};
class com::mojang::minecraftpe::store::NativeStoreListener {
public:
    NativeStoreListener(JNIEnv *, jlong);
};
class com::mojang::minecraftpe::store::Product {
public:
    jnivm::Object<java::lang::String>* mId;
    jnivm::Object<java::lang::String>* mPrice;
    jnivm::Object<java::lang::String>* mCurrencyCode;
    jnivm::Object<java::lang::String>* mUnformattedPrice;
};
class com::mojang::minecraftpe::store::Purchase {
public:
    jnivm::Object<java::lang::String>* mProductId;
    jnivm::Object<java::lang::String>* mReceipt;
    jboolean mPurchaseActive;
};
class com::mojang::minecraftpe::store::StoreFactory {
public:
    static jnivm::Object<com::mojang::minecraftpe::store::Store>* createGooglePlayStore(JNIEnv *, jnivm::Object<java::lang::String>*, jnivm::Object<com::mojang::minecraftpe::store::StoreListener>*);
    static jnivm::Object<com::mojang::minecraftpe::store::Store>* createAmazonAppStore(JNIEnv *, jnivm::Object<com::mojang::minecraftpe::store::StoreListener>*, jboolean);
};
class com::mojang::minecraftpe::store::StoreListener {
public:
};
class com::mojang::minecraftpe::store::Store {
public:
    jnivm::Object<java::lang::String>* getStoreId(JNIEnv *);
    jnivm::Object<java::lang::String>* getProductSkuPrefix(JNIEnv *);
    jnivm::Object<java::lang::String>* getRealmsSkuPrefix(JNIEnv *);
    jboolean hasVerifiedLicense(JNIEnv *);
    jnivm::Object<com::mojang::minecraftpe::store::ExtraLicenseResponseData>* getExtraLicenseData(JNIEnv *);
    jboolean receivedLicenseResponse(JNIEnv *);
    void queryProducts(JNIEnv *, jnivm::Array<jnivm::Object<java::lang::String>*>*);
    void purchase(JNIEnv *, jnivm::Object<java::lang::String>*, jboolean, jnivm::Object<java::lang::String>*);
    void acknowledgePurchase(JNIEnv *, jnivm::Object<java::lang::String>*, jnivm::Object<java::lang::String>*);
    void queryPurchases(JNIEnv *);
    void destructor(JNIEnv *);
};
class com::mojang::minecraftpe::store::ExtraLicenseResponseData {
public:
};

class com::microsoft::xbox::idp::interop::Interop {
public:
    static jnivm::Object<java::lang::String>* GetLocalStoragePath(JNIEnv *, jnivm::Object<android::content::Context>*);
    static jnivm::Object<java::lang::String>* ReadConfigFile(JNIEnv *, jnivm::Object<android::content::Context>*);
    static jnivm::Object<java::lang::String>* getSystemProxy(JNIEnv *);
    static void InitCLL(JNIEnv *, jnivm::Object<android::content::Context>*, jnivm::Object<java::lang::String>*);
};
class com::microsoft::xbox::idp::interop::LocalConfig {
public:
};
class com::microsoft::xbox::idp::interop::XboxLiveAppConfig {
public:
};

class com::microsoft::xbox::idp::util::HttpCall {
public:
};
class com::microsoft::xbox::idp::util::AuthFlowResult {
public:
};



class com::microsoft::xboxtcui::Interop {
public:
};


class android::os::Build {
public:
    class VERSION;
};
class android::os::Build::VERSION {
public:
    static jint SDK_INT;
};
class android::os::IBinder {
public:
};

class android::view::Window {
public:
    jnivm::Object<android::view::View>* getDecorView(JNIEnv *);
};
class android::view::View {
public:
    jnivm::Object<android::os::IBinder>* getWindowToken(JNIEnv *);
};
class android::view::inputmethod::InputMethodManager {
public:
    jboolean showSoftInput(JNIEnv *, jnivm::Object<android::view::View>*, jint);
    jboolean hideSoftInputFromWindow(JNIEnv *, jnivm::Object<android::os::IBinder>*, jint);
};


class android::content::Context {
public:
    static jnivm::Object<java::lang::String>* INPUT_METHOD_SERVICE;
    void startActivity(JNIEnv *, jnivm::Object<android::content::Intent>*);
};
class android::content::Intent {
public:
};
class android::content::ContextWrapper {
public:
    jnivm::Object<java::io::File>* getFilesDir(JNIEnv *);
    jnivm::Object<java::io::File>* getCacheDir(JNIEnv *);
};

class android::app::NativeActivity {
public:
    jnivm::Object<android::content::Context>* getApplicationContext(JNIEnv *);
};


class java::lang::String {
public:
    std::string str;
};
class java::lang::Object {
public:
};
class java::lang::ClassLoader {
public:
    jnivm::Object<java::lang::Class>* loadClass(JNIEnv *, jnivm::Object<java::lang::String>*);
};
class java::lang::Class {
public:
};

class java::io::File {
public:
    jnivm::Object<java::lang::String>* getPath(JNIEnv *);
};


void com::mojang::minecraftpe::MainActivity::saveScreenshot(JNIEnv *env, jnivm::Object<java::lang::String>* arg0, jint arg1, jint arg2, jnivm::Array<jint>* arg3) {
    
}

void com::mojang::minecraftpe::MainActivity::postScreenshotToFacebook(JNIEnv *env, jnivm::Object<java::lang::String>* arg0, jint arg1, jint arg2, jnivm::Array<jint>* arg3) {
    
}

jnivm::Array<jint>* com::mojang::minecraftpe::MainActivity::getImageData(JNIEnv *env, jnivm::Object<java::lang::String>* arg0) {
    auto ret = new jnivm::Array<jint>();
    ret->cl = 0;
    ret->value = new jint[20] { 0 };
    ret->length = 2;
    return ret;
}

jnivm::Array<jbyte>* com::mojang::minecraftpe::MainActivity::getFileDataBytes(JNIEnv *env, jnivm::Object<java::lang::String>* arg0) {
    std::ifstream file(arg0->value->str, std::ios::binary | std::ios::ate);
    Log::trace("getFileDataBytes", "%s", arg0->value->str.data());
    if(file.is_open()) {
        auto ret = new jnivm::Array<jbyte>();
        ret->length = file.tellg();
        ret->value = new jbyte[ret->length];
        file.seekg(0, std::ios::beg);
        file.read((char*)ret->value, ret->length);
        return ret;
    } else {
        auto ret = new jnivm::Array<jbyte>();
        ret->length = 0;
        ret->value = 0;
        return ret;
    }
}

void com::mojang::minecraftpe::MainActivity::displayDialog(JNIEnv *env, jint arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::tick(JNIEnv *env) {
    
}

void com::mojang::minecraftpe::MainActivity::quit(JNIEnv *env) {
    
}

void com::mojang::minecraftpe::MainActivity::initiateUserInput(JNIEnv *env, jint arg0) {
    
}

jint com::mojang::minecraftpe::MainActivity::getUserInputStatus(JNIEnv *env) {
    
}

jnivm::Array<jnivm::Object<java::lang::String>*>* com::mojang::minecraftpe::MainActivity::getUserInputString(JNIEnv *env) {
    
}

jint com::mojang::minecraftpe::MainActivity::checkLicense(JNIEnv *env) {
    return 1;
}

jboolean com::mojang::minecraftpe::MainActivity::hasBuyButtonWhenInvalidLicense(JNIEnv *env) {
    return false;
}

void com::mojang::minecraftpe::MainActivity::buyGame(JNIEnv *env) {
    
}

void com::mojang::minecraftpe::MainActivity::vibrate(JNIEnv *env, jint arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setIsPowerVR(JNIEnv *env, jboolean arg0) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isNetworkEnabled(JNIEnv *env, jboolean arg0) {
    return true;
}

jfloat com::mojang::minecraftpe::MainActivity::getPixelsPerMillimeter(JNIEnv *env) {
    return 80;
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getPlatformStringVar(JNIEnv *env, jint arg0) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "Android" } };    
}

jnivm::Object<java::lang::Object>* com::mojang::minecraftpe::MainActivity::getSystemService(JNIEnv *env, jnivm::Object<java::lang::String>* arg0) {
    return new jnivm::Object<java::lang::Object> { env->FindClass("android/lang/Object"), new java::lang::Object { } };    
}

jnivm::Object<android::view::Window>* com::mojang::minecraftpe::MainActivity::getWindow(JNIEnv *env) {
    return new jnivm::Object<android::view::Window> { env->FindClass("android/view/Window"), new android::view::Window { } };
}

jint com::mojang::minecraftpe::MainActivity::getKeyFromKeyCode(JNIEnv *env, jint arg0, jint arg1, jint arg2) {
    return arg0;
}

void com::mojang::minecraftpe::MainActivity::updateLocalization(JNIEnv *env, jnivm::Object<java::lang::String>* arg0, jnivm::Object<java::lang::String>* arg1) {
    
}

void com::mojang::minecraftpe::MainActivity::showKeyboard(JNIEnv *env, jnivm::Object<java::lang::String>* arg0, jint arg1, jboolean arg2, jboolean arg3, jboolean arg4) {
    
}

void com::mojang::minecraftpe::MainActivity::hideKeyboard(JNIEnv *env) {
    
}

jfloat com::mojang::minecraftpe::MainActivity::getKeyboardHeight(JNIEnv *env) {
    return 0;
}

void com::mojang::minecraftpe::MainActivity::updateTextboxText(JNIEnv *env, jnivm::Object<java::lang::String>* arg0) {
    
}

jint com::mojang::minecraftpe::MainActivity::getCursorPosition(JNIEnv *env) {
    return 0;
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getAccessToken(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "Android" } };
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getClientId(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "Android" } };
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getProfileId(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "Android" } };
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getProfileName(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "Android" } };
}

jnivm::Array<jnivm::Object<java::lang::String>*>* com::mojang::minecraftpe::MainActivity::getBroadcastAddresses(JNIEnv *env) {
    auto ret = new jnivm::Array<jnivm::Object<java::lang::String>*>();
    ret->length = 0;
    ret->value = 0;
    return ret;
}

jnivm::Array<jnivm::Object<java::lang::String>*>* com::mojang::minecraftpe::MainActivity::getIPAddresses(JNIEnv *env) {
    auto ret = new jnivm::Array<jnivm::Object<java::lang::String>*>();
    ret->length = 0;
    ret->value = 0;
    return ret;
}

jlong com::mojang::minecraftpe::MainActivity::getTotalMemory(JNIEnv *env) {
    
}

jlong com::mojang::minecraftpe::MainActivity::getMemoryLimit(JNIEnv *env) {
    
}

jlong com::mojang::minecraftpe::MainActivity::getUsedMemory(JNIEnv *env) {
    
}

jlong com::mojang::minecraftpe::MainActivity::getFreeMemory(JNIEnv *env) {
    
}

void com::mojang::minecraftpe::MainActivity::launchUri(JNIEnv *env, jnivm::Object<java::lang::String>* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setClipboard(JNIEnv *env, jnivm::Object<java::lang::String>* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::share(JNIEnv *env, jnivm::Object<java::lang::String>* arg0, jnivm::Object<java::lang::String>* arg1, jnivm::Object<java::lang::String>* arg2) {
    
}

jnivm::Object<android::content::Intent>* com::mojang::minecraftpe::MainActivity::createAndroidLaunchIntent(JNIEnv *env) {
    
}

jlong com::mojang::minecraftpe::MainActivity::calculateAvailableDiskFreeSpace(JNIEnv *env, jnivm::Object<java::lang::String>* arg0) {
    
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getExternalStoragePath(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { PathHelper::getPrimaryDataDirectory() } };
}

void com::mojang::minecraftpe::MainActivity::requestStoragePermission(JNIEnv *env, jint arg0) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::hasWriteExternalStoragePermission(JNIEnv *env) {
    return true;
}

void com::mojang::minecraftpe::MainActivity::deviceIdCorrelationStart(JNIEnv *env) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isMixerCreateInstalled(JNIEnv *env) {
    return false;
}

void com::mojang::minecraftpe::MainActivity::navigateToPlaystoreForMixerCreate(JNIEnv *env) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::launchMixerCreateForBroadcast(JNIEnv *env) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isTTSEnabled(JNIEnv *env) {
    return false;
}

jnivm::Object<com::mojang::minecraftpe::HardwareInformation>* com::mojang::minecraftpe::MainActivity::getHardwareInfo(JNIEnv *env) {
    return new jnivm::Object<com::mojang::minecraftpe::HardwareInformation> { env->FindClass("com/mojang/minecraftpe/HardwareInformation"), new com::mojang::minecraftpe::HardwareInformation() };
}

void com::mojang::minecraftpe::MainActivity::setCachedDeviceId(JNIEnv *env, jnivm::Object<java::lang::String>* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setLastDeviceSessionId(JNIEnv *env, jnivm::Object<java::lang::String>* arg0) {
    
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getLastDeviceSessionId(JNIEnv *env) {
    
}

jint com::mojang::minecraftpe::MainActivity::getAPIVersion(JNIEnv *env, jnivm::Object<java::lang::String>* arg0) {
    return 27;
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getSecureStorageKey(JNIEnv *env, jnivm::Object<java::lang::String>* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setSecureStorageKey(JNIEnv *env, jnivm::Object<java::lang::String>* arg0, jnivm::Object<java::lang::String>* arg1) {
    
}

void com::mojang::minecraftpe::MainActivity::trackPurchaseEvent(JNIEnv *env, jnivm::Object<java::lang::String>* arg0, jnivm::Object<java::lang::String>* arg1, jnivm::Object<java::lang::String>* arg2, jnivm::Object<java::lang::String>* arg3, jnivm::Object<java::lang::String>* arg4, jnivm::Object<java::lang::String>* arg5, jnivm::Object<java::lang::String>* arg6, jnivm::Object<java::lang::String>* arg7) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeEvent(JNIEnv *env, jnivm::Object<java::lang::String>* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeEventWithProperty(JNIEnv *env, jnivm::Object<java::lang::String>* arg0, jnivm::Object<java::lang::String>* arg1, jint arg2) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeEventWithStringProperty(JNIEnv *env, jnivm::Object<java::lang::String>* arg0, jnivm::Object<java::lang::String>* arg1, jnivm::Object<java::lang::String>* arg2) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeToastClick(JNIEnv *env) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeDialogButtonClick(JNIEnv *env, jint arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::pickImage(JNIEnv *env, jlong arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setFileDialogCallback(JNIEnv *env, jlong arg0) {
    
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getLegacyDeviceID(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "Andy" } };    
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::createUUID(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "daa78df1-373a-444d-9b1d-4c71a14bb559" } };
}

jboolean com::mojang::minecraftpe::MainActivity::hasHardwareKeyboard(JNIEnv *env) {
    return true;
}

void com::mojang::minecraftpe::MainActivity::startTextToSpeech(JNIEnv *env, jnivm::Object<java::lang::String>* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::stopTextToSpeech(JNIEnv *env) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isTextToSpeechInProgress(JNIEnv *env) {
    
}

void com::mojang::minecraftpe::MainActivity::setTextToSpeechEnabled(JNIEnv *env, jboolean arg0) {
    
}

jint com::mojang::minecraftpe::MainActivity::getScreenWidth(JNIEnv *env) {
    
}

jint com::mojang::minecraftpe::MainActivity::getScreenHeight(JNIEnv *env) {
    
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getDeviceModel(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "Android" } };    
}

jint com::mojang::minecraftpe::MainActivity::getAndroidVersion(JNIEnv *env) {
    
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getLocale(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "en" } };    
}

jboolean com::mojang::minecraftpe::MainActivity::isTablet(JNIEnv *env) {
    return false;
}

jnivm::Object<java::lang::ClassLoader>* com::mojang::minecraftpe::MainActivity::getClassLoader(JNIEnv *env) {
    return new jnivm::Object<java::lang::ClassLoader> { env->FindClass("java/lang/ClassLoader"), new java::lang::ClassLoader() };
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getDeviceModelName(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "Android" } };
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getAndroidVersion(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "0000000000000000" } };
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getCPUType(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "" } };
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getCPUName(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "" } };
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getCPUFeatures(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "" } };
}

jint com::mojang::minecraftpe::HardwareInformation::getNumCores(JNIEnv *env) {
    return 4;
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getSecureId(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "0000000000000000" } };
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getSerialNumber(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "0000000000000000" } };
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getBoard(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "Android" } };
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getInstallerPackageName(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "com.mojang.minecraftpe" } };
}

jint com::mojang::minecraftpe::HardwareInformation::getSignaturesHashCode(JNIEnv *env) {
    return 0xccccccc;
}

jboolean com::mojang::minecraftpe::HardwareInformation::getIsRooted(JNIEnv *env) {
    return false;
}

jlong nativestore = 0;

com::mojang::minecraftpe::store::NativeStoreListener::NativeStoreListener(JNIEnv *env, jlong arg0) {
    nativestore = arg0;
}

jnivm::Object<com::mojang::minecraftpe::store::Store>* com::mojang::minecraftpe::store::StoreFactory::createGooglePlayStore(JNIEnv *env, jnivm::Object<java::lang::String>* arg0, jnivm::Object<com::mojang::minecraftpe::store::StoreListener>* arg1) {
    auto store = new jnivm::Object<com::mojang::minecraftpe::store::Store> { env->FindClass("com/mojang/minecraftpe/store/Store"), new com::mojang::minecraftpe::store::Store() };
    auto callback = (void(*)(JNIEnv*,jnivm::Object<com::mojang::minecraftpe::store::StoreListener>*, jlong, jboolean)) env->functions->reserved3;
    callback(env, arg1, nativestore, true);
    return store;
}

jnivm::Object<com::mojang::minecraftpe::store::Store>* com::mojang::minecraftpe::store::StoreFactory::createAmazonAppStore(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::store::StoreListener>* arg0, jboolean arg1) {
    // return new jnivm::Object<com::mojang::minecraftpe::store::Store> { env->FindClass("com/mojang/minecraftpe/store/Store"), new com::mojang::minecraftpe::store::Store() };    
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::store::Store::getStoreId(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "android.googleplay" } };
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::store::Store::getProductSkuPrefix(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "com.linux" } };    
}

jnivm::Object<java::lang::String>* com::mojang::minecraftpe::store::Store::getRealmsSkuPrefix(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "com.linux" } };    
}

jboolean com::mojang::minecraftpe::store::Store::hasVerifiedLicense(JNIEnv *env) {
    return true;
}

jnivm::Object<com::mojang::minecraftpe::store::ExtraLicenseResponseData>* com::mojang::minecraftpe::store::Store::getExtraLicenseData(JNIEnv *env) {
    
}

jboolean com::mojang::minecraftpe::store::Store::receivedLicenseResponse(JNIEnv *env) {
    return true;
}

void com::mojang::minecraftpe::store::Store::queryProducts(JNIEnv *env, jnivm::Array<jnivm::Object<java::lang::String>*>* arg0) {
    
}

void com::mojang::minecraftpe::store::Store::purchase(JNIEnv *env, jnivm::Object<java::lang::String>* arg0, jboolean arg1, jnivm::Object<java::lang::String>* arg2) {
    
}

void com::mojang::minecraftpe::store::Store::acknowledgePurchase(JNIEnv *env, jnivm::Object<java::lang::String>* arg0, jnivm::Object<java::lang::String>* arg1) {
    
}

void com::mojang::minecraftpe::store::Store::queryPurchases(JNIEnv *env) {
    
}

void com::mojang::minecraftpe::store::Store::destructor(JNIEnv *env) {
    
}

jnivm::Object<java::lang::String>* com::microsoft::xbox::idp::interop::Interop::GetLocalStoragePath(JNIEnv *env, jnivm::Object<android::content::Context>* arg0) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "xboxstor/" } };
}

jnivm::Object<java::lang::String>* com::microsoft::xbox::idp::interop::Interop::ReadConfigFile(JNIEnv *env, jnivm::Object<android::content::Context>* arg0) {
    Log::trace("XBOXLive", "Reading xbox config file");
    std::ifstream f("xboxservices.config");
    std::stringstream s;
    s << f.rdbuf();
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { s.str() } };
}

jnivm::Object<java::lang::String>* com::microsoft::xbox::idp::interop::Interop::getSystemProxy(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "System.Proxy" } };
}

void com::microsoft::xbox::idp::interop::Interop::InitCLL(JNIEnv *env, jnivm::Object<android::content::Context>* arg0, jnivm::Object<java::lang::String>* arg1) {
    
}

jint android::os::Build::VERSION::SDK_INT = 27;

jnivm::Object<android::view::View>* android::view::Window::getDecorView(JNIEnv *env) {
    return new jnivm::Object<android::view::View> { env->FindClass("android/view/View"), new android::view::View() };
}

jnivm::Object<android::os::IBinder>* android::view::View::getWindowToken(JNIEnv *env) {
    return new jnivm::Object<android::os::IBinder> { env->FindClass("android/os/IBinder"), new android::os::IBinder() };
}

jboolean android::view::inputmethod::InputMethodManager::showSoftInput(JNIEnv *env, jnivm::Object<android::view::View>* arg0, jint arg1) {
    return true;
}

jboolean android::view::inputmethod::InputMethodManager::hideSoftInputFromWindow(JNIEnv *env, jnivm::Object<android::os::IBinder>* arg0, jint arg1) {
    
}

jnivm::Object<java::lang::String>* android::content::Context::INPUT_METHOD_SERVICE = {};

void android::content::Context::startActivity(JNIEnv *env, jnivm::Object<android::content::Intent>* arg0) {
    
}

jnivm::Object<java::io::File>* android::content::ContextWrapper::getFilesDir(JNIEnv *env) {
    
}

jnivm::Object<java::io::File>* android::content::ContextWrapper::getCacheDir(JNIEnv *env) {
    
}

jnivm::Object<android::content::Context>* android::app::NativeActivity::getApplicationContext(JNIEnv *env) {
    return new jnivm::Object<android::content::Context> { env->FindClass("android/content/Context"), new android::content::Context() };
}

jnivm::Object<java::lang::Class>* java::lang::ClassLoader::loadClass(JNIEnv *env, jnivm::Object<java::lang::String>* arg0) {
    return (jnivm::Object<java::lang::Class>*)env->FindClass(arg0->value->str.data());
}

jnivm::Object<java::lang::String>* java::io::File::getPath(JNIEnv *env) {
    return new jnivm::Object<java::lang::String> { env->FindClass("java/lang/String"), new java::lang::String { "" } };    
}

extern "C" void com_mojang_minecraftpe_MainActivity_saveScreenshot(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::MainActivity::saveScreenshot(env, (jnivm::Object<java::lang::String>*&)values[0], (jint&)values[1], (jint&)values[2], (jnivm::Array<jint>*&)values[3]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_postScreenshotToFacebook(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->postScreenshotToFacebook(env, (jnivm::Object<java::lang::String>*&)values[0], (jint&)values[1], (jint&)values[2], (jnivm::Array<jint>*&)values[3]);
}
extern "C" jnivm::Array<jint>* com_mojang_minecraftpe_MainActivity_getImageData(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getImageData(env, (jnivm::Object<java::lang::String>*&)values[0]);
}
extern "C" jnivm::Array<jbyte>* com_mojang_minecraftpe_MainActivity_getFileDataBytes(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getFileDataBytes(env, (jnivm::Object<java::lang::String>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_displayDialog(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->displayDialog(env, (jint&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_tick(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->tick(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_quit(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->quit(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_initiateUserInput(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->initiateUserInput(env, (jint&)values[0]);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getUserInputStatus(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getUserInputStatus(env);
}
extern "C" jnivm::Array<jnivm::Object<java::lang::String>*>* com_mojang_minecraftpe_MainActivity_getUserInputString(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getUserInputString(env);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_checkLicense(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->checkLicense(env);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_hasBuyButtonWhenInvalidLicense(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->hasBuyButtonWhenInvalidLicense(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_buyGame(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->buyGame(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_vibrate(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->vibrate(env, (jint&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setIsPowerVR(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->setIsPowerVR(env, (jboolean&)values[0]);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_isNetworkEnabled(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->isNetworkEnabled(env, (jboolean&)values[0]);
}
extern "C" jfloat com_mojang_minecraftpe_MainActivity_getPixelsPerMillimeter(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getPixelsPerMillimeter(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getPlatformStringVar(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getPlatformStringVar(env, (jint&)values[0]);
}
extern "C" jnivm::Object<java::lang::Object>* com_mojang_minecraftpe_MainActivity_getSystemService(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getSystemService(env, (jnivm::Object<java::lang::String>*&)values[0]);
}
extern "C" jnivm::Object<android::view::Window>* com_mojang_minecraftpe_MainActivity_getWindow(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getWindow(env);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getKeyFromKeyCode(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getKeyFromKeyCode(env, (jint&)values[0], (jint&)values[1], (jint&)values[2]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_updateLocalization(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->updateLocalization(env, (jnivm::Object<java::lang::String>*&)values[0], (jnivm::Object<java::lang::String>*&)values[1]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_showKeyboard(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->showKeyboard(env, (jnivm::Object<java::lang::String>*&)values[0], (jint&)values[1], (jboolean&)values[2], (jboolean&)values[3], (jboolean&)values[4]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_hideKeyboard(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->hideKeyboard(env);
}
extern "C" jfloat com_mojang_minecraftpe_MainActivity_getKeyboardHeight(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getKeyboardHeight(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_updateTextboxText(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->updateTextboxText(env, (jnivm::Object<java::lang::String>*&)values[0]);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getCursorPosition(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getCursorPosition(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getAccessToken(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getAccessToken(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getClientId(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getClientId(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getProfileId(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getProfileId(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getProfileName(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getProfileName(env);
}
extern "C" jnivm::Array<jnivm::Object<java::lang::String>*>* com_mojang_minecraftpe_MainActivity_getBroadcastAddresses(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getBroadcastAddresses(env);
}
extern "C" jnivm::Array<jnivm::Object<java::lang::String>*>* com_mojang_minecraftpe_MainActivity_getIPAddresses(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getIPAddresses(env);
}
extern "C" jlong com_mojang_minecraftpe_MainActivity_getTotalMemory(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getTotalMemory(env);
}
extern "C" jlong com_mojang_minecraftpe_MainActivity_getMemoryLimit(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getMemoryLimit(env);
}
extern "C" jlong com_mojang_minecraftpe_MainActivity_getUsedMemory(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getUsedMemory(env);
}
extern "C" jlong com_mojang_minecraftpe_MainActivity_getFreeMemory(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getFreeMemory(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_launchUri(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->launchUri(env, (jnivm::Object<java::lang::String>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setClipboard(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->setClipboard(env, (jnivm::Object<java::lang::String>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_share(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->share(env, (jnivm::Object<java::lang::String>*&)values[0], (jnivm::Object<java::lang::String>*&)values[1], (jnivm::Object<java::lang::String>*&)values[2]);
}
extern "C" jnivm::Object<android::content::Intent>* com_mojang_minecraftpe_MainActivity_createAndroidLaunchIntent(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->createAndroidLaunchIntent(env);
}
extern "C" jlong com_mojang_minecraftpe_MainActivity_calculateAvailableDiskFreeSpace(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->calculateAvailableDiskFreeSpace(env, (jnivm::Object<java::lang::String>*&)values[0]);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getExternalStoragePath(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getExternalStoragePath(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_requestStoragePermission(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->requestStoragePermission(env, (jint&)values[0]);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_hasWriteExternalStoragePermission(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->hasWriteExternalStoragePermission(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_deviceIdCorrelationStart(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->deviceIdCorrelationStart(env);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_isMixerCreateInstalled(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->isMixerCreateInstalled(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_navigateToPlaystoreForMixerCreate(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->navigateToPlaystoreForMixerCreate(env);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_launchMixerCreateForBroadcast(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->launchMixerCreateForBroadcast(env);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_isTTSEnabled(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->isTTSEnabled(env);
}
extern "C" jnivm::Object<com::mojang::minecraftpe::HardwareInformation>* com_mojang_minecraftpe_MainActivity_getHardwareInfo(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getHardwareInfo(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setCachedDeviceId(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->setCachedDeviceId(env, (jnivm::Object<java::lang::String>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setLastDeviceSessionId(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->setLastDeviceSessionId(env, (jnivm::Object<java::lang::String>*&)values[0]);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getLastDeviceSessionId(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getLastDeviceSessionId(env);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getAPIVersion(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getAPIVersion(env, (jnivm::Object<java::lang::String>*&)values[0]);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getSecureStorageKey(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getSecureStorageKey(env, (jnivm::Object<java::lang::String>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setSecureStorageKey(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->setSecureStorageKey(env, (jnivm::Object<java::lang::String>*&)values[0], (jnivm::Object<java::lang::String>*&)values[1]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_trackPurchaseEvent(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->trackPurchaseEvent(env, (jnivm::Object<java::lang::String>*&)values[0], (jnivm::Object<java::lang::String>*&)values[1], (jnivm::Object<java::lang::String>*&)values[2], (jnivm::Object<java::lang::String>*&)values[3], (jnivm::Object<java::lang::String>*&)values[4], (jnivm::Object<java::lang::String>*&)values[5], (jnivm::Object<java::lang::String>*&)values[6], (jnivm::Object<java::lang::String>*&)values[7]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeEvent(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->sendBrazeEvent(env, (jnivm::Object<java::lang::String>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeEventWithProperty(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->sendBrazeEventWithProperty(env, (jnivm::Object<java::lang::String>*&)values[0], (jnivm::Object<java::lang::String>*&)values[1], (jint&)values[2]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeEventWithStringProperty(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->sendBrazeEventWithStringProperty(env, (jnivm::Object<java::lang::String>*&)values[0], (jnivm::Object<java::lang::String>*&)values[1], (jnivm::Object<java::lang::String>*&)values[2]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeToastClick(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->sendBrazeToastClick(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeDialogButtonClick(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->sendBrazeDialogButtonClick(env, (jint&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_pickImage(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->pickImage(env, (jlong&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setFileDialogCallback(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->setFileDialogCallback(env, (jlong&)values[0]);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getLegacyDeviceID(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getLegacyDeviceID(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_createUUID(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->createUUID(env);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_hasHardwareKeyboard(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->hasHardwareKeyboard(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_startTextToSpeech(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->startTextToSpeech(env, (jnivm::Object<java::lang::String>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_stopTextToSpeech(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->stopTextToSpeech(env);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_isTextToSpeechInProgress(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->isTextToSpeechInProgress(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setTextToSpeechEnabled(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->setTextToSpeechEnabled(env, (jboolean&)values[0]);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getScreenWidth(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getScreenWidth(env);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getScreenHeight(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getScreenHeight(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getDeviceModel(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getDeviceModel(env);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getAndroidVersion(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getAndroidVersion(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getLocale(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getLocale(env);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_isTablet(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->isTablet(env);
}
extern "C" jnivm::Object<java::lang::ClassLoader>* com_mojang_minecraftpe_MainActivity_getClassLoader(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getClassLoader(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getDeviceModelName(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getDeviceModelName(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getAndroidVersion(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getAndroidVersion(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getCPUType(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getCPUType(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getCPUName(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getCPUName(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getCPUFeatures(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getCPUFeatures(env);
}
extern "C" jint com_mojang_minecraftpe_HardwareInformation_getNumCores(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getNumCores(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getSecureId(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::HardwareInformation>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getSecureId(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getSerialNumber(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getSerialNumber(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getBoard(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getBoard(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getInstallerPackageName(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::HardwareInformation>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getInstallerPackageName(env);
}
extern "C" jint com_mojang_minecraftpe_HardwareInformation_getSignaturesHashCode(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::HardwareInformation>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getSignaturesHashCode(env);
}
extern "C" jboolean com_mojang_minecraftpe_HardwareInformation_getIsRooted(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::HardwareInformation>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getIsRooted(env);
}
extern "C" void com_mojang_minecraftpe_store_NativeStoreListener_NativeStoreListener(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::store::NativeStoreListener>* obj, jvalue* values) {
    new (obj ? obj->value : nullptr) com::mojang::minecraftpe::store::NativeStoreListener(env, (jlong&)values[0]);
}
extern "C" jnivm::Object<java::lang::String>* get_com_mojang_minecraftpe_store_Product_mId(jnivm::Object<com::mojang::minecraftpe::store::Product>* obj) {
    return obj->value->mId;
}

extern "C" void set_com_mojang_minecraftpe_store_Product_mId(jnivm::Object<com::mojang::minecraftpe::store::Product>* obj, jnivm::Object<java::lang::String>* value) {
    obj->value->mId = value;
}

extern "C" jnivm::Object<java::lang::String>* get_com_mojang_minecraftpe_store_Product_mPrice(jnivm::Object<com::mojang::minecraftpe::store::Product>* obj) {
    return obj->value->mPrice;
}

extern "C" void set_com_mojang_minecraftpe_store_Product_mPrice(jnivm::Object<com::mojang::minecraftpe::store::Product>* obj, jnivm::Object<java::lang::String>* value) {
    obj->value->mPrice = value;
}

extern "C" jnivm::Object<java::lang::String>* get_com_mojang_minecraftpe_store_Product_mCurrencyCode(jnivm::Object<com::mojang::minecraftpe::store::Product>* obj) {
    return obj->value->mCurrencyCode;
}

extern "C" void set_com_mojang_minecraftpe_store_Product_mCurrencyCode(jnivm::Object<com::mojang::minecraftpe::store::Product>* obj, jnivm::Object<java::lang::String>* value) {
    obj->value->mCurrencyCode = value;
}

extern "C" jnivm::Object<java::lang::String>* get_com_mojang_minecraftpe_store_Product_mUnformattedPrice(jnivm::Object<com::mojang::minecraftpe::store::Product>* obj) {
    return obj->value->mUnformattedPrice;
}

extern "C" void set_com_mojang_minecraftpe_store_Product_mUnformattedPrice(jnivm::Object<com::mojang::minecraftpe::store::Product>* obj, jnivm::Object<java::lang::String>* value) {
    obj->value->mUnformattedPrice = value;
}

extern "C" jnivm::Object<java::lang::String>* get_com_mojang_minecraftpe_store_Purchase_mProductId(jnivm::Object<com::mojang::minecraftpe::store::Purchase>* obj) {
    return obj->value->mProductId;
}

extern "C" void set_com_mojang_minecraftpe_store_Purchase_mProductId(jnivm::Object<com::mojang::minecraftpe::store::Purchase>* obj, jnivm::Object<java::lang::String>* value) {
    obj->value->mProductId = value;
}

extern "C" jnivm::Object<java::lang::String>* get_com_mojang_minecraftpe_store_Purchase_mReceipt(jnivm::Object<com::mojang::minecraftpe::store::Purchase>* obj) {
    return obj->value->mReceipt;
}

extern "C" void set_com_mojang_minecraftpe_store_Purchase_mReceipt(jnivm::Object<com::mojang::minecraftpe::store::Purchase>* obj, jnivm::Object<java::lang::String>* value) {
    obj->value->mReceipt = value;
}

extern "C" jboolean get_com_mojang_minecraftpe_store_Purchase_mPurchaseActive(jnivm::Object<com::mojang::minecraftpe::store::Purchase>* obj) {
    return obj->value->mPurchaseActive;
}

extern "C" void set_com_mojang_minecraftpe_store_Purchase_mPurchaseActive(jnivm::Object<com::mojang::minecraftpe::store::Purchase>* obj, jboolean value) {
    obj->value->mPurchaseActive = value;
}

extern "C" jnivm::Object<com::mojang::minecraftpe::store::Store>* com_mojang_minecraftpe_store_StoreFactory_createGooglePlayStore(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::store::StoreFactory::createGooglePlayStore(env, (jnivm::Object<java::lang::String>*&)values[0], (jnivm::Object<com::mojang::minecraftpe::store::StoreListener>*&)values[1]);
}
extern "C" jnivm::Object<com::mojang::minecraftpe::store::Store>* com_mojang_minecraftpe_store_StoreFactory_createAmazonAppStore(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::store::StoreFactory::createAmazonAppStore(env, (jnivm::Object<com::mojang::minecraftpe::store::StoreListener>*&)values[0], (jboolean&)values[1]);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_store_Store_getStoreId(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getStoreId(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_store_Store_getProductSkuPrefix(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getProductSkuPrefix(env);
}
extern "C" jnivm::Object<java::lang::String>* com_mojang_minecraftpe_store_Store_getRealmsSkuPrefix(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getRealmsSkuPrefix(env);
}
extern "C" jboolean com_mojang_minecraftpe_store_Store_hasVerifiedLicense(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->hasVerifiedLicense(env);
}
extern "C" jnivm::Object<com::mojang::minecraftpe::store::ExtraLicenseResponseData>* com_mojang_minecraftpe_store_Store_getExtraLicenseData(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getExtraLicenseData(env);
}
extern "C" jboolean com_mojang_minecraftpe_store_Store_receivedLicenseResponse(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->receivedLicenseResponse(env);
}
extern "C" void com_mojang_minecraftpe_store_Store_queryProducts(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->queryProducts(env, (jnivm::Array<jnivm::Object<java::lang::String>*>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_store_Store_purchase(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->purchase(env, (jnivm::Object<java::lang::String>*&)values[0], (jboolean&)values[1], (jnivm::Object<java::lang::String>*&)values[2]);
}
extern "C" void com_mojang_minecraftpe_store_Store_acknowledgePurchase(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->acknowledgePurchase(env, (jnivm::Object<java::lang::String>*&)values[0], (jnivm::Object<java::lang::String>*&)values[1]);
}
extern "C" void com_mojang_minecraftpe_store_Store_queryPurchases(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->queryPurchases(env);
}
extern "C" void com_mojang_minecraftpe_store_Store_destructor(JNIEnv *env, jnivm::Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->destructor(env);
}
extern "C" jnivm::Object<java::lang::String>* com_microsoft_xbox_idp_interop_Interop_GetLocalStoragePath(JNIEnv *env, jvalue* values) {
    return com::microsoft::xbox::idp::interop::Interop::GetLocalStoragePath(env, (jnivm::Object<android::content::Context>*&)values[0]);
}
extern "C" jnivm::Object<java::lang::String>* com_microsoft_xbox_idp_interop_Interop_ReadConfigFile(JNIEnv *env, jvalue* values) {
    return com::microsoft::xbox::idp::interop::Interop::ReadConfigFile(env, (jnivm::Object<android::content::Context>*&)values[0]);
}
extern "C" jnivm::Object<java::lang::String>* com_microsoft_xbox_idp_interop_Interop_getSystemProxy(JNIEnv *env, jvalue* values) {
    return com::microsoft::xbox::idp::interop::Interop::getSystemProxy(env);
}
extern "C" void com_microsoft_xbox_idp_interop_Interop_InitCLL(JNIEnv *env, jvalue* values) {
    return com::microsoft::xbox::idp::interop::Interop::InitCLL(env, (jnivm::Object<android::content::Context>*&)values[0], (jnivm::Object<java::lang::String>*&)values[1]);
}
extern "C" jint get_android_os_Build_VERSION_SDK_INT() {
    return android::os::Build::VERSION::SDK_INT;
}

extern "C" void set_android_os_Build_VERSION_SDK_INT(jint value) {
    android::os::Build::VERSION::SDK_INT = value;
}

extern "C" jnivm::Object<android::view::View>* android_view_Window_getDecorView(JNIEnv *env, jnivm::Object<android::view::Window>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getDecorView(env);
}
extern "C" jnivm::Object<android::os::IBinder>* android_view_View_getWindowToken(JNIEnv *env, jnivm::Object<android::view::View>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getWindowToken(env);
}
extern "C" jboolean android_view_inputmethod_InputMethodManager_showSoftInput(JNIEnv *env, jnivm::Object<android::view::inputmethod::InputMethodManager>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->showSoftInput(env, (jnivm::Object<android::view::View>*&)values[0], (jint&)values[1]);
}
extern "C" jboolean android_view_inputmethod_InputMethodManager_hideSoftInputFromWindow(JNIEnv *env, jnivm::Object<android::view::inputmethod::InputMethodManager>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->hideSoftInputFromWindow(env, (jnivm::Object<android::os::IBinder>*&)values[0], (jint&)values[1]);
}
extern "C" jnivm::Object<java::lang::String>* get_android_content_Context_INPUT_METHOD_SERVICE() {
    return android::content::Context::INPUT_METHOD_SERVICE;
}

extern "C" void set_android_content_Context_INPUT_METHOD_SERVICE(jnivm::Object<java::lang::String>* value) {
    android::content::Context::INPUT_METHOD_SERVICE = value;
}

extern "C" void android_content_Context_startActivity(JNIEnv *env, jnivm::Object<android::content::Context>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->startActivity(env, (jnivm::Object<android::content::Intent>*&)values[0]);
}
extern "C" jnivm::Object<java::io::File>* android_content_ContextWrapper_getFilesDir(JNIEnv *env, jnivm::Object<android::content::ContextWrapper>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getFilesDir(env);
}
extern "C" jnivm::Object<java::io::File>* android_content_ContextWrapper_getCacheDir(JNIEnv *env, jnivm::Object<android::content::ContextWrapper>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getCacheDir(env);
}
extern "C" jnivm::Object<android::content::Context>* android_app_NativeActivity_getApplicationContext(JNIEnv *env, jnivm::Object<android::app::NativeActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getApplicationContext(env);
}
extern "C" jnivm::Object<java::lang::Class>* java_lang_ClassLoader_loadClass(JNIEnv *env, jnivm::Object<java::lang::ClassLoader>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->loadClass(env, (jnivm::Object<java::lang::String>*&)values[0]);
}
extern "C" jnivm::Object<java::lang::String>* java_io_File_getPath(JNIEnv *env, jnivm::Object<java::io::File>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getPath(env);
}