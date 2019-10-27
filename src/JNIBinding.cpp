
#include <tuple>
#include <vector>
#include <fstream>
#include "jni.h"

template<class T> class Object {
public:
    // Object(jclass cl, T* value);
    jclass cl;
    T* value;
};

template<class T> class Array : public Object<T> {
public:
    size_t length;
};

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
    static void saveScreenshot(Object<java::lang::String>*, jint, jint, Array<jint>*);
    void postScreenshotToFacebook(Object<java::lang::String>*, jint, jint, Array<jint>*);
    Array<jint>* getImageData(Object<java::lang::String>*);
    Array<jbyte>* getFileDataBytes(Object<java::lang::String>*);
    void displayDialog(jint);
    void tick();
    void quit();
    void initiateUserInput(jint);
    jint getUserInputStatus();
    Array<Object<java::lang::String>*>* getUserInputString();
    jint checkLicense();
    jboolean hasBuyButtonWhenInvalidLicense();
    void buyGame();
    void vibrate(jint);
    void setIsPowerVR(jboolean);
    jboolean isNetworkEnabled(jboolean);
    jfloat getPixelsPerMillimeter();
    Object<java::lang::String>* getPlatformStringVar(jint);
    Object<java::lang::Object>* getSystemService(Object<java::lang::String>*);
    Object<android::view::Window>* getWindow();
    jint getKeyFromKeyCode(jint, jint, jint);
    void updateLocalization(Object<java::lang::String>*, Object<java::lang::String>*);
    void showKeyboard(Object<java::lang::String>*, jint, jboolean, jboolean, jboolean);
    void hideKeyboard();
    jfloat getKeyboardHeight();
    void updateTextboxText(Object<java::lang::String>*);
    jint getCursorPosition();
    Object<java::lang::String>* getAccessToken();
    Object<java::lang::String>* getClientId();
    Object<java::lang::String>* getProfileId();
    Object<java::lang::String>* getProfileName();
    Array<Object<java::lang::String>*>* getBroadcastAddresses();
    Array<Object<java::lang::String>*>* getIPAddresses();
    jlong getTotalMemory();
    jlong getMemoryLimit();
    jlong getUsedMemory();
    jlong getFreeMemory();
    void launchUri(Object<java::lang::String>*);
    void setClipboard(Object<java::lang::String>*);
    void share(Object<java::lang::String>*, Object<java::lang::String>*, Object<java::lang::String>*);
    Object<android::content::Intent>* createAndroidLaunchIntent();
    jlong calculateAvailableDiskFreeSpace(Object<java::lang::String>*);
    Object<java::lang::String>* getExternalStoragePath();
    void requestStoragePermission(jint);
    jboolean hasWriteExternalStoragePermission();
    void deviceIdCorrelationStart();
    jboolean isMixerCreateInstalled();
    void navigateToPlaystoreForMixerCreate();
    jboolean launchMixerCreateForBroadcast();
    jboolean isTTSEnabled();
    Object<com::mojang::minecraftpe::HardwareInformation>* getHardwareInfo();
    void setCachedDeviceId(Object<java::lang::String>*);
    void setLastDeviceSessionId(Object<java::lang::String>*);
    Object<java::lang::String>* getLastDeviceSessionId();
    jint getAPIVersion(Object<java::lang::String>*);
    Object<java::lang::String>* getSecureStorageKey(Object<java::lang::String>*);
    void setSecureStorageKey(Object<java::lang::String>*, Object<java::lang::String>*);
    void trackPurchaseEvent(Object<java::lang::String>*, Object<java::lang::String>*, Object<java::lang::String>*, Object<java::lang::String>*, Object<java::lang::String>*, Object<java::lang::String>*, Object<java::lang::String>*, Object<java::lang::String>*);
    void sendBrazeEvent(Object<java::lang::String>*);
    void sendBrazeEventWithProperty(Object<java::lang::String>*, Object<java::lang::String>*, jint);
    void sendBrazeEventWithStringProperty(Object<java::lang::String>*, Object<java::lang::String>*, Object<java::lang::String>*);
    void sendBrazeToastClick();
    void sendBrazeDialogButtonClick(jint);
    void pickImage(jlong);
    void setFileDialogCallback(jlong);
    Object<java::lang::String>* getLegacyDeviceID();
    Object<java::lang::String>* createUUID();
    jboolean hasHardwareKeyboard();
    void startTextToSpeech(Object<java::lang::String>*);
    void stopTextToSpeech();
    jboolean isTextToSpeechInProgress();
    void setTextToSpeechEnabled(jboolean);
    jint getScreenWidth();
    jint getScreenHeight();
    Object<java::lang::String>* getDeviceModel();
    jint getAndroidVersion();
    Object<java::lang::String>* getLocale();
    jboolean isTablet();
    Object<java::lang::ClassLoader>* getClassLoader();
};
class com::mojang::minecraftpe::HardwareInformation {
public:
    static Object<java::lang::String>* getDeviceModelName();
    static Object<java::lang::String>* getAndroidVersion();
    static Object<java::lang::String>* getCPUType();
    static Object<java::lang::String>* getCPUName();
    static Object<java::lang::String>* getCPUFeatures();
    static jint getNumCores();
    Object<java::lang::String>* getSecureId();
    static Object<java::lang::String>* getSerialNumber();
    static Object<java::lang::String>* getBoard();
    Object<java::lang::String>* getInstallerPackageName();
    jint getSignaturesHashCode();
    jboolean getIsRooted();
};
class com::mojang::minecraftpe::store::NativeStoreListener {
public:
    NativeStoreListener(jlong);
};
class com::mojang::minecraftpe::store::Product {
public:
    Object<java::lang::String>* mId;
    Object<java::lang::String>* mPrice;
    Object<java::lang::String>* mCurrencyCode;
    Object<java::lang::String>* mUnformattedPrice;
};
class com::mojang::minecraftpe::store::Purchase {
public:
    Object<java::lang::String>* mProductId;
    Object<java::lang::String>* mReceipt;
    jboolean mPurchaseActive;
};
class com::mojang::minecraftpe::store::StoreFactory {
public:
    static Object<com::mojang::minecraftpe::store::Store>* createGooglePlayStore(Object<java::lang::String>*, Object<com::mojang::minecraftpe::store::StoreListener>*);
    static Object<com::mojang::minecraftpe::store::Store>* createAmazonAppStore(Object<com::mojang::minecraftpe::store::StoreListener>*, jboolean);
};
class com::mojang::minecraftpe::store::StoreListener {
public:
};
class com::mojang::minecraftpe::store::Store {
public:
    Object<java::lang::String>* getStoreId();
    Object<java::lang::String>* getProductSkuPrefix();
    Object<java::lang::String>* getRealmsSkuPrefix();
    jboolean hasVerifiedLicense();
    Object<com::mojang::minecraftpe::store::ExtraLicenseResponseData>* getExtraLicenseData();
    jboolean receivedLicenseResponse();
    void queryProducts(Array<Object<java::lang::String>*>*);
    void purchase(Object<java::lang::String>*, jboolean, Object<java::lang::String>*);
    void acknowledgePurchase(Object<java::lang::String>*, Object<java::lang::String>*);
    void queryPurchases();
    void destructor();
};
class com::mojang::minecraftpe::store::ExtraLicenseResponseData {
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
    Object<android::view::View>* getDecorView();
};
class android::view::View {
public:
    Object<android::os::IBinder>* getWindowToken();
};
class android::view::inputmethod::InputMethodManager {
public:
    jboolean showSoftInput(Object<android::view::View>*, jint);
    jboolean hideSoftInputFromWindow(Object<android::os::IBinder>*, jint);
};


class android::content::Context {
public:
    static Object<java::lang::String>* INPUT_METHOD_SERVICE;
    void startActivity(Object<android::content::Intent>*);
};
class android::content::Intent {
public:
};
class android::content::ContextWrapper {
public:
    Object<java::io::File>* getFilesDir();
    Object<java::io::File>* getCacheDir();
};

class android::app::NativeActivity {
public:
    Object<android::content::Context>* getApplicationContext();
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
    ::Object<java::lang::Class>* loadClass(::Object<java::lang::String>*);
};
class java::lang::Class {
public:
};

class java::io::File {
public:
    Object<java::lang::String>* getPath();
};


void com::mojang::minecraftpe::MainActivity::saveScreenshot(Object<java::lang::String>* arg0, jint arg1, jint arg2, Array<jint>* arg3) {
    
}

void com::mojang::minecraftpe::MainActivity::postScreenshotToFacebook(Object<java::lang::String>* arg0, jint arg1, jint arg2, Array<jint>* arg3) {
    
}

Array<jint>* com::mojang::minecraftpe::MainActivity::getImageData(Object<java::lang::String>* arg0) {
    auto ret = new Array<jint>();
    ret->cl = 0;
    ret->value = new jint[20] { 0 };
    ret->length = 2;
    return ret;
}

Array<jbyte>* com::mojang::minecraftpe::MainActivity::getFileDataBytes(Object<java::lang::String>* arg0) {
    std::ifstream file(arg0->value->str, std::ios::binary | std::ios::ate);
    if(file.is_open()) {
        auto ret = new Array<jbyte>();
        ret->length = file.tellg();
        ret->value = new jbyte[ret->length];
        file.seekg(0, std::ios::beg);
        file.read((char*)ret->value, ret->length);
        return ret;
    }
    return nullptr;
}

void com::mojang::minecraftpe::MainActivity::displayDialog(jint arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::tick() {
    
}

void com::mojang::minecraftpe::MainActivity::quit() {
    
}

void com::mojang::minecraftpe::MainActivity::initiateUserInput(jint arg0) {
    
}

jint com::mojang::minecraftpe::MainActivity::getUserInputStatus() {
    
}

Array<Object<java::lang::String>*>* com::mojang::minecraftpe::MainActivity::getUserInputString() {
    
}

jint com::mojang::minecraftpe::MainActivity::checkLicense() {
    
}

jboolean com::mojang::minecraftpe::MainActivity::hasBuyButtonWhenInvalidLicense() {
    
}

void com::mojang::minecraftpe::MainActivity::buyGame() {
    
}

void com::mojang::minecraftpe::MainActivity::vibrate(jint arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setIsPowerVR(jboolean arg0) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isNetworkEnabled(jboolean arg0) {
    
}

jfloat com::mojang::minecraftpe::MainActivity::getPixelsPerMillimeter() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getPlatformStringVar(jint arg0) {
    
}

Object<java::lang::Object>* com::mojang::minecraftpe::MainActivity::getSystemService(Object<java::lang::String>* arg0) {
    
}

Object<android::view::Window>* com::mojang::minecraftpe::MainActivity::getWindow() {
    
}

jint com::mojang::minecraftpe::MainActivity::getKeyFromKeyCode(jint arg0, jint arg1, jint arg2) {
    
}

void com::mojang::minecraftpe::MainActivity::updateLocalization(Object<java::lang::String>* arg0, Object<java::lang::String>* arg1) {
    
}

void com::mojang::minecraftpe::MainActivity::showKeyboard(Object<java::lang::String>* arg0, jint arg1, jboolean arg2, jboolean arg3, jboolean arg4) {
    
}

void com::mojang::minecraftpe::MainActivity::hideKeyboard() {
    
}

jfloat com::mojang::minecraftpe::MainActivity::getKeyboardHeight() {
    
}

void com::mojang::minecraftpe::MainActivity::updateTextboxText(Object<java::lang::String>* arg0) {
    
}

jint com::mojang::minecraftpe::MainActivity::getCursorPosition() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getAccessToken() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getClientId() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getProfileId() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getProfileName() {
    
}

Array<Object<java::lang::String>*>* com::mojang::minecraftpe::MainActivity::getBroadcastAddresses() {
    
}

Array<Object<java::lang::String>*>* com::mojang::minecraftpe::MainActivity::getIPAddresses() {
    
}

jlong com::mojang::minecraftpe::MainActivity::getTotalMemory() {
    
}

jlong com::mojang::minecraftpe::MainActivity::getMemoryLimit() {
    
}

jlong com::mojang::minecraftpe::MainActivity::getUsedMemory() {
    
}

jlong com::mojang::minecraftpe::MainActivity::getFreeMemory() {
    
}

void com::mojang::minecraftpe::MainActivity::launchUri(Object<java::lang::String>* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setClipboard(Object<java::lang::String>* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::share(Object<java::lang::String>* arg0, Object<java::lang::String>* arg1, Object<java::lang::String>* arg2) {
    
}

Object<android::content::Intent>* com::mojang::minecraftpe::MainActivity::createAndroidLaunchIntent() {
    
}

jlong com::mojang::minecraftpe::MainActivity::calculateAvailableDiskFreeSpace(Object<java::lang::String>* arg0) {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getExternalStoragePath() {
    
}

void com::mojang::minecraftpe::MainActivity::requestStoragePermission(jint arg0) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::hasWriteExternalStoragePermission() {
    
}

void com::mojang::minecraftpe::MainActivity::deviceIdCorrelationStart() {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isMixerCreateInstalled() {
    
}

void com::mojang::minecraftpe::MainActivity::navigateToPlaystoreForMixerCreate() {
    
}

jboolean com::mojang::minecraftpe::MainActivity::launchMixerCreateForBroadcast() {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isTTSEnabled() {
    
}

Object<com::mojang::minecraftpe::HardwareInformation>* com::mojang::minecraftpe::MainActivity::getHardwareInfo() {
    
}

void com::mojang::minecraftpe::MainActivity::setCachedDeviceId(Object<java::lang::String>* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setLastDeviceSessionId(Object<java::lang::String>* arg0) {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getLastDeviceSessionId() {
    
}

jint com::mojang::minecraftpe::MainActivity::getAPIVersion(Object<java::lang::String>* arg0) {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getSecureStorageKey(Object<java::lang::String>* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setSecureStorageKey(Object<java::lang::String>* arg0, Object<java::lang::String>* arg1) {
    
}

void com::mojang::minecraftpe::MainActivity::trackPurchaseEvent(Object<java::lang::String>* arg0, Object<java::lang::String>* arg1, Object<java::lang::String>* arg2, Object<java::lang::String>* arg3, Object<java::lang::String>* arg4, Object<java::lang::String>* arg5, Object<java::lang::String>* arg6, Object<java::lang::String>* arg7) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeEvent(Object<java::lang::String>* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeEventWithProperty(Object<java::lang::String>* arg0, Object<java::lang::String>* arg1, jint arg2) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeEventWithStringProperty(Object<java::lang::String>* arg0, Object<java::lang::String>* arg1, Object<java::lang::String>* arg2) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeToastClick() {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeDialogButtonClick(jint arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::pickImage(jlong arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setFileDialogCallback(jlong arg0) {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getLegacyDeviceID() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::createUUID() {
    
}

jboolean com::mojang::minecraftpe::MainActivity::hasHardwareKeyboard() {
    
}

void com::mojang::minecraftpe::MainActivity::startTextToSpeech(Object<java::lang::String>* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::stopTextToSpeech() {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isTextToSpeechInProgress() {
    
}

void com::mojang::minecraftpe::MainActivity::setTextToSpeechEnabled(jboolean arg0) {
    
}

jint com::mojang::minecraftpe::MainActivity::getScreenWidth() {
    
}

jint com::mojang::minecraftpe::MainActivity::getScreenHeight() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getDeviceModel() {
    
}

jint com::mojang::minecraftpe::MainActivity::getAndroidVersion() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getLocale() {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isTablet() {
    
}

Object<java::lang::ClassLoader>* com::mojang::minecraftpe::MainActivity::getClassLoader() {
    return new Object<java::lang::ClassLoader> { .cl = 0, .value = new java::lang::ClassLoader() };
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getDeviceModelName() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getAndroidVersion() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getCPUType() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getCPUName() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getCPUFeatures() {
    
}

jint com::mojang::minecraftpe::HardwareInformation::getNumCores() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getSecureId() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getSerialNumber() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getBoard() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getInstallerPackageName() {
    
}

jint com::mojang::minecraftpe::HardwareInformation::getSignaturesHashCode() {
    
}

jboolean com::mojang::minecraftpe::HardwareInformation::getIsRooted() {
    
}

com::mojang::minecraftpe::store::NativeStoreListener::NativeStoreListener(jlong arg0) {
    
}

Object<com::mojang::minecraftpe::store::Store>* com::mojang::minecraftpe::store::StoreFactory::createGooglePlayStore(Object<java::lang::String>* arg0, Object<com::mojang::minecraftpe::store::StoreListener>* arg1) {
    
}

Object<com::mojang::minecraftpe::store::Store>* com::mojang::minecraftpe::store::StoreFactory::createAmazonAppStore(Object<com::mojang::minecraftpe::store::StoreListener>* arg0, jboolean arg1) {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::store::Store::getStoreId() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::store::Store::getProductSkuPrefix() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::store::Store::getRealmsSkuPrefix() {
    
}

jboolean com::mojang::minecraftpe::store::Store::hasVerifiedLicense() {
    
}

Object<com::mojang::minecraftpe::store::ExtraLicenseResponseData>* com::mojang::minecraftpe::store::Store::getExtraLicenseData() {
    
}

jboolean com::mojang::minecraftpe::store::Store::receivedLicenseResponse() {
    
}

void com::mojang::minecraftpe::store::Store::queryProducts(Array<Object<java::lang::String>*>* arg0) {
    
}

void com::mojang::minecraftpe::store::Store::purchase(Object<java::lang::String>* arg0, jboolean arg1, Object<java::lang::String>* arg2) {
    
}

void com::mojang::minecraftpe::store::Store::acknowledgePurchase(Object<java::lang::String>* arg0, Object<java::lang::String>* arg1) {
    
}

void com::mojang::minecraftpe::store::Store::queryPurchases() {
    
}

void com::mojang::minecraftpe::store::Store::destructor() {
    
}

jint android::os::Build::VERSION::SDK_INT = jint();

Object<android::view::View>* android::view::Window::getDecorView() {
    
}

Object<android::os::IBinder>* android::view::View::getWindowToken() {
    
}

jboolean android::view::inputmethod::InputMethodManager::showSoftInput(Object<android::view::View>* arg0, jint arg1) {
    
}

jboolean android::view::inputmethod::InputMethodManager::hideSoftInputFromWindow(Object<android::os::IBinder>* arg0, jint arg1) {
    
}

Object<java::lang::String>* android::content::Context::INPUT_METHOD_SERVICE = (Object<java::lang::String>*)(0);

void android::content::Context::startActivity(Object<android::content::Intent>* arg0) {
    
}

Object<java::io::File>* android::content::ContextWrapper::getFilesDir() {
    
}

Object<java::io::File>* android::content::ContextWrapper::getCacheDir() {
    
}

Object<android::content::Context>* android::app::NativeActivity::getApplicationContext() {
    return new Object<android::content::Context> { .cl = 0, .value = new android::content::Context() };
}

#include <memory>
::Object<java::lang::Class>* java::lang::ClassLoader::loadClass(::Object<java::lang::String>* arg0) {
    class Class {
    public:
        std::string name;
        std::string nativeprefix;
        std::vector<std::shared_ptr<Class>> classes;
        std::vector<std::shared_ptr<void>> fields;
        std::vector<std::shared_ptr<void>> methods;
    };
    
    return (::Object<java::lang::Class>*)(new Class { arg0->value->str, "", {}, {}, {} });
}

Object<java::lang::String>* java::io::File::getPath() {
    
}

extern "C" void com_mojang_minecraftpe_MainActivity_saveScreenshot(jvalue* values) {
    return com::mojang::minecraftpe::MainActivity::saveScreenshot((Object<java::lang::String>*&)values[0], (jint&)values[1], (jint&)values[2], (Array<jint>*&)values[3]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_postScreenshotToFacebook(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->postScreenshotToFacebook((Object<java::lang::String>*&)values[0], (jint&)values[1], (jint&)values[2], (Array<jint>*&)values[3]);
}
extern "C" Array<jint>* com_mojang_minecraftpe_MainActivity_getImageData(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getImageData((Object<java::lang::String>*&)values[0]);
}
extern "C" Array<jbyte>* com_mojang_minecraftpe_MainActivity_getFileDataBytes(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getFileDataBytes((Object<java::lang::String>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_displayDialog(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->displayDialog((jint&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_tick(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->tick();
}
extern "C" void com_mojang_minecraftpe_MainActivity_quit(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->quit();
}
extern "C" void com_mojang_minecraftpe_MainActivity_initiateUserInput(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->initiateUserInput((jint&)values[0]);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getUserInputStatus(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getUserInputStatus();
}
extern "C" Array<Object<java::lang::String>*>* com_mojang_minecraftpe_MainActivity_getUserInputString(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getUserInputString();
}
extern "C" jint com_mojang_minecraftpe_MainActivity_checkLicense(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->checkLicense();
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_hasBuyButtonWhenInvalidLicense(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->hasBuyButtonWhenInvalidLicense();
}
extern "C" void com_mojang_minecraftpe_MainActivity_buyGame(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->buyGame();
}
extern "C" void com_mojang_minecraftpe_MainActivity_vibrate(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->vibrate((jint&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setIsPowerVR(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->setIsPowerVR((jboolean&)values[0]);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_isNetworkEnabled(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->isNetworkEnabled((jboolean&)values[0]);
}
extern "C" jfloat com_mojang_minecraftpe_MainActivity_getPixelsPerMillimeter(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getPixelsPerMillimeter();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getPlatformStringVar(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getPlatformStringVar((jint&)values[0]);
}
extern "C" Object<java::lang::Object>* com_mojang_minecraftpe_MainActivity_getSystemService(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getSystemService((Object<java::lang::String>*&)values[0]);
}
extern "C" Object<android::view::Window>* com_mojang_minecraftpe_MainActivity_getWindow(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getWindow();
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getKeyFromKeyCode(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getKeyFromKeyCode((jint&)values[0], (jint&)values[1], (jint&)values[2]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_updateLocalization(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->updateLocalization((Object<java::lang::String>*&)values[0], (Object<java::lang::String>*&)values[1]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_showKeyboard(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->showKeyboard((Object<java::lang::String>*&)values[0], (jint&)values[1], (jboolean&)values[2], (jboolean&)values[3], (jboolean&)values[4]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_hideKeyboard(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->hideKeyboard();
}
extern "C" jfloat com_mojang_minecraftpe_MainActivity_getKeyboardHeight(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getKeyboardHeight();
}
extern "C" void com_mojang_minecraftpe_MainActivity_updateTextboxText(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->updateTextboxText((Object<java::lang::String>*&)values[0]);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getCursorPosition(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getCursorPosition();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getAccessToken(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getAccessToken();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getClientId(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getClientId();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getProfileId(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getProfileId();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getProfileName(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getProfileName();
}
extern "C" Array<Object<java::lang::String>*>* com_mojang_minecraftpe_MainActivity_getBroadcastAddresses(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getBroadcastAddresses();
}
extern "C" Array<Object<java::lang::String>*>* com_mojang_minecraftpe_MainActivity_getIPAddresses(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getIPAddresses();
}
extern "C" jlong com_mojang_minecraftpe_MainActivity_getTotalMemory(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getTotalMemory();
}
extern "C" jlong com_mojang_minecraftpe_MainActivity_getMemoryLimit(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getMemoryLimit();
}
extern "C" jlong com_mojang_minecraftpe_MainActivity_getUsedMemory(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getUsedMemory();
}
extern "C" jlong com_mojang_minecraftpe_MainActivity_getFreeMemory(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getFreeMemory();
}
extern "C" void com_mojang_minecraftpe_MainActivity_launchUri(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->launchUri((Object<java::lang::String>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setClipboard(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->setClipboard((Object<java::lang::String>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_share(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->share((Object<java::lang::String>*&)values[0], (Object<java::lang::String>*&)values[1], (Object<java::lang::String>*&)values[2]);
}
extern "C" Object<android::content::Intent>* com_mojang_minecraftpe_MainActivity_createAndroidLaunchIntent(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->createAndroidLaunchIntent();
}
extern "C" jlong com_mojang_minecraftpe_MainActivity_calculateAvailableDiskFreeSpace(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->calculateAvailableDiskFreeSpace((Object<java::lang::String>*&)values[0]);
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getExternalStoragePath(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getExternalStoragePath();
}
extern "C" void com_mojang_minecraftpe_MainActivity_requestStoragePermission(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->requestStoragePermission((jint&)values[0]);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_hasWriteExternalStoragePermission(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->hasWriteExternalStoragePermission();
}
extern "C" void com_mojang_minecraftpe_MainActivity_deviceIdCorrelationStart(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->deviceIdCorrelationStart();
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_isMixerCreateInstalled(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->isMixerCreateInstalled();
}
extern "C" void com_mojang_minecraftpe_MainActivity_navigateToPlaystoreForMixerCreate(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->navigateToPlaystoreForMixerCreate();
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_launchMixerCreateForBroadcast(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->launchMixerCreateForBroadcast();
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_isTTSEnabled(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->isTTSEnabled();
}
extern "C" Object<com::mojang::minecraftpe::HardwareInformation>* com_mojang_minecraftpe_MainActivity_getHardwareInfo(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getHardwareInfo();
}
extern "C" void com_mojang_minecraftpe_MainActivity_setCachedDeviceId(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->setCachedDeviceId((Object<java::lang::String>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setLastDeviceSessionId(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->setLastDeviceSessionId((Object<java::lang::String>*&)values[0]);
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getLastDeviceSessionId(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getLastDeviceSessionId();
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getAPIVersion(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getAPIVersion((Object<java::lang::String>*&)values[0]);
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getSecureStorageKey(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getSecureStorageKey((Object<java::lang::String>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setSecureStorageKey(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->setSecureStorageKey((Object<java::lang::String>*&)values[0], (Object<java::lang::String>*&)values[1]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_trackPurchaseEvent(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->trackPurchaseEvent((Object<java::lang::String>*&)values[0], (Object<java::lang::String>*&)values[1], (Object<java::lang::String>*&)values[2], (Object<java::lang::String>*&)values[3], (Object<java::lang::String>*&)values[4], (Object<java::lang::String>*&)values[5], (Object<java::lang::String>*&)values[6], (Object<java::lang::String>*&)values[7]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeEvent(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->sendBrazeEvent((Object<java::lang::String>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeEventWithProperty(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->sendBrazeEventWithProperty((Object<java::lang::String>*&)values[0], (Object<java::lang::String>*&)values[1], (jint&)values[2]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeEventWithStringProperty(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->sendBrazeEventWithStringProperty((Object<java::lang::String>*&)values[0], (Object<java::lang::String>*&)values[1], (Object<java::lang::String>*&)values[2]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeToastClick(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->sendBrazeToastClick();
}
extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeDialogButtonClick(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->sendBrazeDialogButtonClick((jint&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_pickImage(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->pickImage((jlong&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setFileDialogCallback(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->setFileDialogCallback((jlong&)values[0]);
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getLegacyDeviceID(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getLegacyDeviceID();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_createUUID(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->createUUID();
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_hasHardwareKeyboard(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->hasHardwareKeyboard();
}
extern "C" void com_mojang_minecraftpe_MainActivity_startTextToSpeech(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->startTextToSpeech((Object<java::lang::String>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_stopTextToSpeech(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->stopTextToSpeech();
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_isTextToSpeechInProgress(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->isTextToSpeechInProgress();
}
extern "C" void com_mojang_minecraftpe_MainActivity_setTextToSpeechEnabled(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->setTextToSpeechEnabled((jboolean&)values[0]);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getScreenWidth(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getScreenWidth();
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getScreenHeight(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getScreenHeight();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getDeviceModel(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getDeviceModel();
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getAndroidVersion(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getAndroidVersion();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getLocale(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getLocale();
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_isTablet(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->isTablet();
}
extern "C" Object<java::lang::ClassLoader>* com_mojang_minecraftpe_MainActivity_getClassLoader(Object<com::mojang::minecraftpe::MainActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getClassLoader();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getDeviceModelName(jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getDeviceModelName();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getAndroidVersion(jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getAndroidVersion();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getCPUType(jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getCPUType();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getCPUName(jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getCPUName();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getCPUFeatures(jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getCPUFeatures();
}
extern "C" jint com_mojang_minecraftpe_HardwareInformation_getNumCores(jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getNumCores();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getSecureId(Object<com::mojang::minecraftpe::HardwareInformation>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getSecureId();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getSerialNumber(jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getSerialNumber();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getBoard(jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getBoard();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getInstallerPackageName(Object<com::mojang::minecraftpe::HardwareInformation>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getInstallerPackageName();
}
extern "C" jint com_mojang_minecraftpe_HardwareInformation_getSignaturesHashCode(Object<com::mojang::minecraftpe::HardwareInformation>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getSignaturesHashCode();
}
extern "C" jboolean com_mojang_minecraftpe_HardwareInformation_getIsRooted(Object<com::mojang::minecraftpe::HardwareInformation>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getIsRooted();
}
extern "C" void com_mojang_minecraftpe_store_NativeStoreListener_NativeStoreListener(Object<com::mojang::minecraftpe::store::NativeStoreListener>* obj, jvalue* values) {
    new (obj ? obj->value : nullptr) com::mojang::minecraftpe::store::NativeStoreListener((jlong&)values[0]);
}
extern "C" Object<java::lang::String>* get_com_mojang_minecraftpe_store_Product_mId(Object<com::mojang::minecraftpe::store::Product>* obj) {
    return obj->value->mId;
}

extern "C" void set_com_mojang_minecraftpe_store_Product_mId(Object<com::mojang::minecraftpe::store::Product>* obj, Object<java::lang::String>* value) {
    obj->value->mId = value;
}

extern "C" Object<java::lang::String>* get_com_mojang_minecraftpe_store_Product_mPrice(Object<com::mojang::minecraftpe::store::Product>* obj) {
    return obj->value->mPrice;
}

extern "C" void set_com_mojang_minecraftpe_store_Product_mPrice(Object<com::mojang::minecraftpe::store::Product>* obj, Object<java::lang::String>* value) {
    obj->value->mPrice = value;
}

extern "C" Object<java::lang::String>* get_com_mojang_minecraftpe_store_Product_mCurrencyCode(Object<com::mojang::minecraftpe::store::Product>* obj) {
    return obj->value->mCurrencyCode;
}

extern "C" void set_com_mojang_minecraftpe_store_Product_mCurrencyCode(Object<com::mojang::minecraftpe::store::Product>* obj, Object<java::lang::String>* value) {
    obj->value->mCurrencyCode = value;
}

extern "C" Object<java::lang::String>* get_com_mojang_minecraftpe_store_Product_mUnformattedPrice(Object<com::mojang::minecraftpe::store::Product>* obj) {
    return obj->value->mUnformattedPrice;
}

extern "C" void set_com_mojang_minecraftpe_store_Product_mUnformattedPrice(Object<com::mojang::minecraftpe::store::Product>* obj, Object<java::lang::String>* value) {
    obj->value->mUnformattedPrice = value;
}

extern "C" Object<java::lang::String>* get_com_mojang_minecraftpe_store_Purchase_mProductId(Object<com::mojang::minecraftpe::store::Purchase>* obj) {
    return obj->value->mProductId;
}

extern "C" void set_com_mojang_minecraftpe_store_Purchase_mProductId(Object<com::mojang::minecraftpe::store::Purchase>* obj, Object<java::lang::String>* value) {
    obj->value->mProductId = value;
}

extern "C" Object<java::lang::String>* get_com_mojang_minecraftpe_store_Purchase_mReceipt(Object<com::mojang::minecraftpe::store::Purchase>* obj) {
    return obj->value->mReceipt;
}

extern "C" void set_com_mojang_minecraftpe_store_Purchase_mReceipt(Object<com::mojang::minecraftpe::store::Purchase>* obj, Object<java::lang::String>* value) {
    obj->value->mReceipt = value;
}

extern "C" jboolean get_com_mojang_minecraftpe_store_Purchase_mPurchaseActive(Object<com::mojang::minecraftpe::store::Purchase>* obj) {
    return obj->value->mPurchaseActive;
}

extern "C" void set_com_mojang_minecraftpe_store_Purchase_mPurchaseActive(Object<com::mojang::minecraftpe::store::Purchase>* obj, jboolean value) {
    obj->value->mPurchaseActive = value;
}

extern "C" Object<com::mojang::minecraftpe::store::Store>* com_mojang_minecraftpe_store_StoreFactory_createGooglePlayStore(jvalue* values) {
    return com::mojang::minecraftpe::store::StoreFactory::createGooglePlayStore((Object<java::lang::String>*&)values[0], (Object<com::mojang::minecraftpe::store::StoreListener>*&)values[1]);
}
extern "C" Object<com::mojang::minecraftpe::store::Store>* com_mojang_minecraftpe_store_StoreFactory_createAmazonAppStore(jvalue* values) {
    return com::mojang::minecraftpe::store::StoreFactory::createAmazonAppStore((Object<com::mojang::minecraftpe::store::StoreListener>*&)values[0], (jboolean&)values[1]);
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_store_Store_getStoreId(Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getStoreId();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_store_Store_getProductSkuPrefix(Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getProductSkuPrefix();
}
extern "C" Object<java::lang::String>* com_mojang_minecraftpe_store_Store_getRealmsSkuPrefix(Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getRealmsSkuPrefix();
}
extern "C" jboolean com_mojang_minecraftpe_store_Store_hasVerifiedLicense(Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->hasVerifiedLicense();
}
extern "C" Object<com::mojang::minecraftpe::store::ExtraLicenseResponseData>* com_mojang_minecraftpe_store_Store_getExtraLicenseData(Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getExtraLicenseData();
}
extern "C" jboolean com_mojang_minecraftpe_store_Store_receivedLicenseResponse(Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->receivedLicenseResponse();
}
extern "C" void com_mojang_minecraftpe_store_Store_queryProducts(Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->queryProducts((Array<Object<java::lang::String>*>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_store_Store_purchase(Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->purchase((Object<java::lang::String>*&)values[0], (jboolean&)values[1], (Object<java::lang::String>*&)values[2]);
}
extern "C" void com_mojang_minecraftpe_store_Store_acknowledgePurchase(Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->acknowledgePurchase((Object<java::lang::String>*&)values[0], (Object<java::lang::String>*&)values[1]);
}
extern "C" void com_mojang_minecraftpe_store_Store_queryPurchases(Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->queryPurchases();
}
extern "C" void com_mojang_minecraftpe_store_Store_destructor(Object<com::mojang::minecraftpe::store::Store>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->destructor();
}
extern "C" jint get_android_os_Build_VERSION_SDK_INT() {
    return android::os::Build::VERSION::SDK_INT;
}

extern "C" void set_android_os_Build_VERSION_SDK_INT(jint value) {
    android::os::Build::VERSION::SDK_INT = value;
}

extern "C" Object<android::view::View>* android_view_Window_getDecorView(Object<android::view::Window>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getDecorView();
}
extern "C" Object<android::os::IBinder>* android_view_View_getWindowToken(Object<android::view::View>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getWindowToken();
}
extern "C" jboolean android_view_inputmethod_InputMethodManager_showSoftInput(Object<android::view::inputmethod::InputMethodManager>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->showSoftInput((Object<android::view::View>*&)values[0], (jint&)values[1]);
}
extern "C" jboolean android_view_inputmethod_InputMethodManager_hideSoftInputFromWindow(Object<android::view::inputmethod::InputMethodManager>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->hideSoftInputFromWindow((Object<android::os::IBinder>*&)values[0], (jint&)values[1]);
}
extern "C" Object<java::lang::String>* get_android_content_Context_INPUT_METHOD_SERVICE() {
    return android::content::Context::INPUT_METHOD_SERVICE;
}

extern "C" void set_android_content_Context_INPUT_METHOD_SERVICE(Object<java::lang::String>* value) {
    android::content::Context::INPUT_METHOD_SERVICE = value;
}

extern "C" void android_content_Context_startActivity(Object<android::content::Context>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->startActivity((Object<android::content::Intent>*&)values[0]);
}

extern "C" Object<java::io::File>* android_content_ContextWrapper_getFilesDir(Object<android::content::ContextWrapper>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getFilesDir();
}
extern "C" Object<java::io::File>* android_content_ContextWrapper_getCacheDir(Object<android::content::ContextWrapper>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getCacheDir();
}

extern "C" Object<android::content::Context>* android_app_NativeActivity_getApplicationContext(Object<android::app::NativeActivity>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getApplicationContext();
}

extern "C" Object<java::lang::String>* java_io_File_getPath(Object<java::io::File>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->getPath();
}

extern "C" Object<java::lang::Class>* java_lang_ClassLoader_loadClass(Object<java::lang::ClassLoader>* obj, jvalue* values) {
    return (obj ? obj->value : nullptr)->loadClass((Object<java::lang::String>*&)values[0]);
}