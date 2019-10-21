
#include <tuple>
#include <vector>
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

template<class T,class ...Types>
struct Create { 
public:
    static void create(T obj, Types...args){
        new (obj) std::remove_pointer_t<T>(args...);
    }
};

template<class ...Types>
struct Create<std::tuple<Types...>> : Create<Types...> {

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
    class VERSION {
    public:
        static jint SDK_INT;
};
};

jint android::os::Build::VERSION::SDK_INT = 29;

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
    Object<java::lang::String> str;
    Object<java::lang::String>* getPath();
};


void com::mojang::minecraftpe::MainActivity::saveScreenshot(Object<java::lang::String>* arg0, jint arg1, jint arg2, Array<jint>* arg3) {
    
}

void com::mojang::minecraftpe::MainActivity::postScreenshotToFacebook(Object<java::lang::String>* arg0, jint arg1, jint arg2, Array<jint>* arg3) {
    
}

Array<jint>* com::mojang::minecraftpe::MainActivity::getImageData(Object<java::lang::String>* arg0) {
    
}

#include <fstream>
Array<jbyte>* com::mojang::minecraftpe::MainActivity::getFileDataBytes(Object<java::lang::String>* arg0) {
    std::ifstream file("/home/christopher/.local/share/mcpelauncher/versions/1.14.0.2/assets/" + arg0->value->str, std::ios::binary | std::ios::ate);
    auto ret = new Array<jbyte>();
    ret->length = file.tellg();
    ret->value = new jbyte[ret->length];
    file.seekg(0, std::ios::beg);
    file.read((char*)ret->value, ret->length);
    return ret;
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
    return 1;
}

jboolean com::mojang::minecraftpe::MainActivity::hasBuyButtonWhenInvalidLicense() {
    return false;
}

void com::mojang::minecraftpe::MainActivity::buyGame() {
    
}

void com::mojang::minecraftpe::MainActivity::vibrate(jint arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setIsPowerVR(jboolean arg0) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isNetworkEnabled(jboolean arg0) {
    return true;
}

jfloat com::mojang::minecraftpe::MainActivity::getPixelsPerMillimeter() {
    return 10;
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
    return 0;
}

void com::mojang::minecraftpe::MainActivity::updateTextboxText(Object<java::lang::String>* arg0) {
    
}

jint com::mojang::minecraftpe::MainActivity::getCursorPosition() {
    return 0;
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getAccessToken() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getClientId() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getProfileId() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getProfileName() {
    return new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "Unknown" } };
}

Array<Object<java::lang::String>*>* com::mojang::minecraftpe::MainActivity::getBroadcastAddresses() {
    // auto array = new Array<Object<java::lang::String>*>();
    // array->value = new Object<java::lang::String>*[]{(new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "255.255.255.255" } })};
    // return array;
}

Array<Object<java::lang::String>*>* com::mojang::minecraftpe::MainActivity::getIPAddresses() {
    // auto array = new Array<Object<java::lang::String>*>();
    // array->value->push_back(new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "127.0.0.1" } });
    // return array;
}

jlong com::mojang::minecraftpe::MainActivity::getTotalMemory() {
    return 16 * 1024 * 1024 * 1024;
}

jlong com::mojang::minecraftpe::MainActivity::getMemoryLimit() {
    return 4 * 1024 * 1024 * 1024;    
}

jlong com::mojang::minecraftpe::MainActivity::getUsedMemory() {
    return 0;
}

jlong com::mojang::minecraftpe::MainActivity::getFreeMemory() {
    return 4 * 1024 * 1024 * 1024; 
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
    return new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "~/Dokumente/mcpe" } };
}

void com::mojang::minecraftpe::MainActivity::requestStoragePermission(jint arg0) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::hasWriteExternalStoragePermission() {
    return true;
}

void com::mojang::minecraftpe::MainActivity::deviceIdCorrelationStart() {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isMixerCreateInstalled() {
    return false;
}

void com::mojang::minecraftpe::MainActivity::navigateToPlaystoreForMixerCreate() {
    
}

jboolean com::mojang::minecraftpe::MainActivity::launchMixerCreateForBroadcast() {
    return false;
}

jboolean com::mojang::minecraftpe::MainActivity::isTTSEnabled() {
    return false;
}

Object<com::mojang::minecraftpe::HardwareInformation>* com::mojang::minecraftpe::MainActivity::getHardwareInfo() {
    
}

void com::mojang::minecraftpe::MainActivity::setCachedDeviceId(Object<java::lang::String>* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setLastDeviceSessionId(Object<java::lang::String>* arg0) {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getLastDeviceSessionId() {
    return new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "" } };
}

jint com::mojang::minecraftpe::MainActivity::getAPIVersion(Object<java::lang::String>* arg0) {
    return 29;
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::getSecureStorageKey(Object<java::lang::String>* arg0) {
    return new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "" } };
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
    return new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "8229fb7c-f1e7-4731-a1eb-1815adb220cb" } };    
}

Object<java::lang::String>* com::mojang::minecraftpe::MainActivity::createUUID() {
    return new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "8229fb7c-f1e7-4731-a1eb-1815adb220cb" } };
}

jboolean com::mojang::minecraftpe::MainActivity::hasHardwareKeyboard() {
    return true;
}

void com::mojang::minecraftpe::MainActivity::startTextToSpeech(Object<java::lang::String>* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::stopTextToSpeech() {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isTextToSpeechInProgress() {
    return false;
}

void com::mojang::minecraftpe::MainActivity::setTextToSpeechEnabled(jboolean arg0) {
    
}

jint com::mojang::minecraftpe::MainActivity::getScreenWidth() {
    return 1920;
}

jint com::mojang::minecraftpe::MainActivity::getScreenHeight() {
    return 1080;
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
    return new Object<java::lang::ClassLoader>();
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getDeviceModelName() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getAndroidVersion() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getCPUType() {
    return new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "Unknown" } };
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getCPUName() {
    return new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "Unknown" } };
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getCPUFeatures() {
    return new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "" } };
}

jint com::mojang::minecraftpe::HardwareInformation::getNumCores() {
    return 4;
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getSecureId() {
    return new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "8229fb7c-f1e7-4731-a1eb-1815adb220cb" } };
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getSerialNumber() {
    return new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "8229fb7c-f1e7-4731-a1eb-1815adb220cb" } };
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getBoard() {
    return new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "Unknown" } };
}

Object<java::lang::String>* com::mojang::minecraftpe::HardwareInformation::getInstallerPackageName() {
    return new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "com.mojang.minecraftpe" } };
}

jint com::mojang::minecraftpe::HardwareInformation::getSignaturesHashCode() {
    return 0;
}

jboolean com::mojang::minecraftpe::HardwareInformation::getIsRooted() {
    return false;
}

com::mojang::minecraftpe::store::NativeStoreListener::NativeStoreListener(jlong arg0) {
    
}

Object<com::mojang::minecraftpe::store::Store>* com::mojang::minecraftpe::store::StoreFactory::createGooglePlayStore(Object<java::lang::String>* arg0, Object<com::mojang::minecraftpe::store::StoreListener>* arg1) {
    
}

Object<com::mojang::minecraftpe::store::Store>* com::mojang::minecraftpe::store::StoreFactory::createAmazonAppStore(Object<com::mojang::minecraftpe::store::StoreListener>* arg0, jboolean arg1) {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::store::Store::getStoreId() {
    return new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "play" } };
}

Object<java::lang::String>* com::mojang::minecraftpe::store::Store::getProductSkuPrefix() {
    
}

Object<java::lang::String>* com::mojang::minecraftpe::store::Store::getRealmsSkuPrefix() {
    
}

jboolean com::mojang::minecraftpe::store::Store::hasVerifiedLicense() {
    return true;
}

Object<com::mojang::minecraftpe::store::ExtraLicenseResponseData>* com::mojang::minecraftpe::store::Store::getExtraLicenseData() {
    
}

jboolean com::mojang::minecraftpe::store::Store::receivedLicenseResponse() {
    return true;
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

Object<android::view::View>* android::view::Window::getDecorView() {
    
}

Object<android::os::IBinder>* android::view::View::getWindowToken() {
    
}

jboolean android::view::inputmethod::InputMethodManager::showSoftInput(Object<android::view::View>* arg0, jint arg1) {
    return false;
}

jboolean android::view::inputmethod::InputMethodManager::hideSoftInputFromWindow(Object<android::os::IBinder>* arg0, jint arg1) {
    return false;
}

void android::content::Context::startActivity(Object<android::content::Intent>* arg0) {
    
}

Object<java::io::File>* android::content::ContextWrapper::getFilesDir() {
    
}

Object<java::io::File>* android::content::ContextWrapper::getCacheDir() {
    
}

Object<android::content::Context>* android::app::NativeActivity::getApplicationContext() {
    
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

extern "C" void com_mojang_minecraftpe_MainActivity_saveScreenshot(va_list list) {
    using Param = std::tuple<Object<java::lang::String>*, jint, jint, Array<jint>*>;
    Param param;
    std::get<0>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<1>(param) = va_arg(list, jint);
    std::get<2>(param) = va_arg(list, jint);
    std::get<3>(param) = va_arg(list, Array<jint>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::saveScreenshot, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_postScreenshotToFacebook(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*, jint, jint, Array<jint>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<2>(param) = va_arg(list, jint);
    std::get<3>(param) = va_arg(list, jint);
    std::get<4>(param) = va_arg(list, Array<jint>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::postScreenshotToFacebook, param);
}

extern "C" Array<jint>* com_mojang_minecraftpe_MainActivity_getImageData(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getImageData, param);
}

extern "C" Array<jbyte>* com_mojang_minecraftpe_MainActivity_getFileDataBytes(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getFileDataBytes, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_displayDialog(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, jint>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, jint);
    return std::apply(&com::mojang::minecraftpe::MainActivity::displayDialog, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_tick(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::tick, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_quit(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::quit, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_initiateUserInput(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, jint>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, jint);
    return std::apply(&com::mojang::minecraftpe::MainActivity::initiateUserInput, param);
}

extern "C" jint com_mojang_minecraftpe_MainActivity_getUserInputStatus(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getUserInputStatus, param);
}

extern "C" Array<Object<java::lang::String>*>* com_mojang_minecraftpe_MainActivity_getUserInputString(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getUserInputString, param);
}

extern "C" jint com_mojang_minecraftpe_MainActivity_checkLicense(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::checkLicense, param);
}

extern "C" jboolean com_mojang_minecraftpe_MainActivity_hasBuyButtonWhenInvalidLicense(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::hasBuyButtonWhenInvalidLicense, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_buyGame(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::buyGame, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_vibrate(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, jint>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, jint);
    return std::apply(&com::mojang::minecraftpe::MainActivity::vibrate, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_setIsPowerVR(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, jboolean>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, int);
    return std::apply(&com::mojang::minecraftpe::MainActivity::setIsPowerVR, param);
}

extern "C" jboolean com_mojang_minecraftpe_MainActivity_isNetworkEnabled(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, jboolean>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, int);
    return std::apply(&com::mojang::minecraftpe::MainActivity::isNetworkEnabled, param);
}

extern "C" jfloat com_mojang_minecraftpe_MainActivity_getPixelsPerMillimeter(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getPixelsPerMillimeter, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getPlatformStringVar(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, jint>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, jint);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getPlatformStringVar, param);
}

extern "C" Object<java::lang::Object>* com_mojang_minecraftpe_MainActivity_getSystemService(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getSystemService, param);
}

extern "C" Object<android::view::Window>* com_mojang_minecraftpe_MainActivity_getWindow(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getWindow, param);
}

extern "C" jint com_mojang_minecraftpe_MainActivity_getKeyFromKeyCode(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, jint, jint, jint>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, jint);
    std::get<2>(param) = va_arg(list, jint);
    std::get<3>(param) = va_arg(list, jint);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getKeyFromKeyCode, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_updateLocalization(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<2>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::updateLocalization, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_showKeyboard(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*, jint, jboolean, jboolean, jboolean>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<2>(param) = va_arg(list, jint);
    std::get<3>(param) = va_arg(list, int);
    std::get<4>(param) = va_arg(list, int);
    std::get<5>(param) = va_arg(list, int);
    return std::apply(&com::mojang::minecraftpe::MainActivity::showKeyboard, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_hideKeyboard(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::hideKeyboard, param);
}

extern "C" jfloat com_mojang_minecraftpe_MainActivity_getKeyboardHeight(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getKeyboardHeight, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_updateTextboxText(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::updateTextboxText, param);
}

extern "C" jint com_mojang_minecraftpe_MainActivity_getCursorPosition(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getCursorPosition, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getAccessToken(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getAccessToken, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getClientId(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getClientId, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getProfileId(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getProfileId, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getProfileName(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getProfileName, param);
}

extern "C" Array<Object<java::lang::String>*>* com_mojang_minecraftpe_MainActivity_getBroadcastAddresses(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getBroadcastAddresses, param);
}

extern "C" Array<Object<java::lang::String>*>* com_mojang_minecraftpe_MainActivity_getIPAddresses(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getIPAddresses, param);
}

extern "C" jlong com_mojang_minecraftpe_MainActivity_getTotalMemory(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getTotalMemory, param);
}

extern "C" jlong com_mojang_minecraftpe_MainActivity_getMemoryLimit(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getMemoryLimit, param);
}

extern "C" jlong com_mojang_minecraftpe_MainActivity_getUsedMemory(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getUsedMemory, param);
}

extern "C" jlong com_mojang_minecraftpe_MainActivity_getFreeMemory(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getFreeMemory, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_launchUri(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::launchUri, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_setClipboard(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::setClipboard, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_share(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*, Object<java::lang::String>*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<2>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<3>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::share, param);
}

extern "C" Object<android::content::Intent>* com_mojang_minecraftpe_MainActivity_createAndroidLaunchIntent(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::createAndroidLaunchIntent, param);
}

extern "C" jlong com_mojang_minecraftpe_MainActivity_calculateAvailableDiskFreeSpace(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::calculateAvailableDiskFreeSpace, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getExternalStoragePath(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getExternalStoragePath, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_requestStoragePermission(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, jint>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, jint);
    return std::apply(&com::mojang::minecraftpe::MainActivity::requestStoragePermission, param);
}

extern "C" jboolean com_mojang_minecraftpe_MainActivity_hasWriteExternalStoragePermission(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::hasWriteExternalStoragePermission, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_deviceIdCorrelationStart(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::deviceIdCorrelationStart, param);
}

extern "C" jboolean com_mojang_minecraftpe_MainActivity_isMixerCreateInstalled(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::isMixerCreateInstalled, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_navigateToPlaystoreForMixerCreate(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::navigateToPlaystoreForMixerCreate, param);
}

extern "C" jboolean com_mojang_minecraftpe_MainActivity_launchMixerCreateForBroadcast(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::launchMixerCreateForBroadcast, param);
}

extern "C" jboolean com_mojang_minecraftpe_MainActivity_isTTSEnabled(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::isTTSEnabled, param);
}

extern "C" Object<com::mojang::minecraftpe::HardwareInformation>* com_mojang_minecraftpe_MainActivity_getHardwareInfo(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getHardwareInfo, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_setCachedDeviceId(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::setCachedDeviceId, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_setLastDeviceSessionId(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::setLastDeviceSessionId, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getLastDeviceSessionId(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getLastDeviceSessionId, param);
}

extern "C" jint com_mojang_minecraftpe_MainActivity_getAPIVersion(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getAPIVersion, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getSecureStorageKey(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getSecureStorageKey, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_setSecureStorageKey(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<2>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::setSecureStorageKey, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_trackPurchaseEvent(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*, Object<java::lang::String>*, Object<java::lang::String>*, Object<java::lang::String>*, Object<java::lang::String>*, Object<java::lang::String>*, Object<java::lang::String>*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<2>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<3>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<4>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<5>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<6>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<7>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<8>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::trackPurchaseEvent, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeEvent(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::sendBrazeEvent, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeEventWithProperty(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*, Object<java::lang::String>*, jint>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<2>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<3>(param) = va_arg(list, jint);
    return std::apply(&com::mojang::minecraftpe::MainActivity::sendBrazeEventWithProperty, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeEventWithStringProperty(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*, Object<java::lang::String>*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<2>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<3>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::sendBrazeEventWithStringProperty, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeToastClick(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::sendBrazeToastClick, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeDialogButtonClick(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, jint>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, jint);
    return std::apply(&com::mojang::minecraftpe::MainActivity::sendBrazeDialogButtonClick, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_pickImage(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, jlong>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, jlong);
    return std::apply(&com::mojang::minecraftpe::MainActivity::pickImage, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_setFileDialogCallback(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, jlong>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, jlong);
    return std::apply(&com::mojang::minecraftpe::MainActivity::setFileDialogCallback, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getLegacyDeviceID(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getLegacyDeviceID, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_createUUID(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::createUUID, param);
}

extern "C" jboolean com_mojang_minecraftpe_MainActivity_hasHardwareKeyboard(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::hasHardwareKeyboard, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_startTextToSpeech(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::MainActivity::startTextToSpeech, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_stopTextToSpeech(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::stopTextToSpeech, param);
}

extern "C" jboolean com_mojang_minecraftpe_MainActivity_isTextToSpeechInProgress(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::isTextToSpeechInProgress, param);
}

extern "C" void com_mojang_minecraftpe_MainActivity_setTextToSpeechEnabled(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*, jboolean>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, int);
    return std::apply(&com::mojang::minecraftpe::MainActivity::setTextToSpeechEnabled, param);
}

extern "C" jint com_mojang_minecraftpe_MainActivity_getScreenWidth(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getScreenWidth, param);
}

extern "C" jint com_mojang_minecraftpe_MainActivity_getScreenHeight(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getScreenHeight, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getDeviceModel(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getDeviceModel, param);
}

extern "C" jint com_mojang_minecraftpe_MainActivity_getAndroidVersion(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getAndroidVersion, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_MainActivity_getLocale(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getLocale, param);
}

extern "C" jboolean com_mojang_minecraftpe_MainActivity_isTablet(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::isTablet, param);
}

extern "C" Object<java::lang::ClassLoader>* com_mojang_minecraftpe_MainActivity_getClassLoader(Object<com::mojang::minecraftpe::MainActivity>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::MainActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::MainActivity::getClassLoader, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getDeviceModelName(va_list list) {
    using Param = std::tuple<>;
    Param param;
    return std::apply(&com::mojang::minecraftpe::HardwareInformation::getDeviceModelName, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getAndroidVersion(va_list list) {
    using Param = std::tuple<>;
    Param param;
    return std::apply(&com::mojang::minecraftpe::HardwareInformation::getAndroidVersion, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getCPUType(va_list list) {
    using Param = std::tuple<>;
    Param param;
    return std::apply(&com::mojang::minecraftpe::HardwareInformation::getCPUType, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getCPUName(va_list list) {
    using Param = std::tuple<>;
    Param param;
    return std::apply(&com::mojang::minecraftpe::HardwareInformation::getCPUName, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getCPUFeatures(va_list list) {
    using Param = std::tuple<>;
    Param param;
    return std::apply(&com::mojang::minecraftpe::HardwareInformation::getCPUFeatures, param);
}

extern "C" jint com_mojang_minecraftpe_HardwareInformation_getNumCores(va_list list) {
    using Param = std::tuple<>;
    Param param;
    return std::apply(&com::mojang::minecraftpe::HardwareInformation::getNumCores, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getSecureId(Object<com::mojang::minecraftpe::HardwareInformation>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::HardwareInformation*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::HardwareInformation::getSecureId, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getSerialNumber(va_list list) {
    using Param = std::tuple<>;
    Param param;
    return std::apply(&com::mojang::minecraftpe::HardwareInformation::getSerialNumber, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getBoard(va_list list) {
    using Param = std::tuple<>;
    Param param;
    return std::apply(&com::mojang::minecraftpe::HardwareInformation::getBoard, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_HardwareInformation_getInstallerPackageName(Object<com::mojang::minecraftpe::HardwareInformation>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::HardwareInformation*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::HardwareInformation::getInstallerPackageName, param);
}

extern "C" jint com_mojang_minecraftpe_HardwareInformation_getSignaturesHashCode(Object<com::mojang::minecraftpe::HardwareInformation>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::HardwareInformation*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::HardwareInformation::getSignaturesHashCode, param);
}

extern "C" jboolean com_mojang_minecraftpe_HardwareInformation_getIsRooted(Object<com::mojang::minecraftpe::HardwareInformation>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::HardwareInformation*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::HardwareInformation::getIsRooted, param);
}

extern "C" void com_mojang_minecraftpe_store_NativeStoreListener_NativeStoreListener(Object<com::mojang::minecraftpe::store::NativeStoreListener>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::store::NativeStoreListener*, jlong>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, jlong);
    return std::apply(&Create<Param>::create, param);
}

extern "C" Object<java::lang::String>* get_com_mojang_minecraftpe_store_Product_mId(Object<com::mojang::minecraftpe::store::Product>* obj) {
    return (obj ? obj->value : nullptr)->mId;
}

extern "C" void set_com_mojang_minecraftpe_store_Product_mId(Object<com::mojang::minecraftpe::store::Product>* obj, Object<java::lang::String>* value) {
    (obj ? obj->value : nullptr)->mId = value;
}

extern "C" Object<java::lang::String>* get_com_mojang_minecraftpe_store_Product_mPrice(Object<com::mojang::minecraftpe::store::Product>* obj) {
    return (obj ? obj->value : nullptr)->mPrice;
}

extern "C" void set_com_mojang_minecraftpe_store_Product_mPrice(Object<com::mojang::minecraftpe::store::Product>* obj, Object<java::lang::String>* value) {
    (obj ? obj->value : nullptr)->mPrice = value;
}

extern "C" Object<java::lang::String>* get_com_mojang_minecraftpe_store_Product_mCurrencyCode(Object<com::mojang::minecraftpe::store::Product>* obj) {
    return (obj ? obj->value : nullptr)->mCurrencyCode;
}

extern "C" void set_com_mojang_minecraftpe_store_Product_mCurrencyCode(Object<com::mojang::minecraftpe::store::Product>* obj, Object<java::lang::String>* value) {
    (obj ? obj->value : nullptr)->mCurrencyCode = value;
}

extern "C" Object<java::lang::String>* get_com_mojang_minecraftpe_store_Product_mUnformattedPrice(Object<com::mojang::minecraftpe::store::Product>* obj) {
    return (obj ? obj->value : nullptr)->mUnformattedPrice;
}

extern "C" void set_com_mojang_minecraftpe_store_Product_mUnformattedPrice(Object<com::mojang::minecraftpe::store::Product>* obj, Object<java::lang::String>* value) {
    (obj ? obj->value : nullptr)->mUnformattedPrice = value;
}

extern "C" Object<java::lang::String>* get_com_mojang_minecraftpe_store_Purchase_mProductId(Object<com::mojang::minecraftpe::store::Purchase>* obj) {
    return (obj ? obj->value : nullptr)->mProductId;
}

extern "C" void set_com_mojang_minecraftpe_store_Purchase_mProductId(Object<com::mojang::minecraftpe::store::Purchase>* obj, Object<java::lang::String>* value) {
    (obj ? obj->value : nullptr)->mProductId = value;
}

extern "C" Object<java::lang::String>* get_com_mojang_minecraftpe_store_Purchase_mReceipt(Object<com::mojang::minecraftpe::store::Purchase>* obj) {
    return (obj ? obj->value : nullptr)->mReceipt;
}

extern "C" void set_com_mojang_minecraftpe_store_Purchase_mReceipt(Object<com::mojang::minecraftpe::store::Purchase>* obj, Object<java::lang::String>* value) {
    (obj ? obj->value : nullptr)->mReceipt = value;
}

extern "C" jboolean get_com_mojang_minecraftpe_store_Purchase_mPurchaseActive(Object<com::mojang::minecraftpe::store::Purchase>* obj) {
    return (obj ? obj->value : nullptr)->mPurchaseActive;
}

extern "C" void set_com_mojang_minecraftpe_store_Purchase_mPurchaseActive(Object<com::mojang::minecraftpe::store::Purchase>* obj, jboolean value) {
    (obj ? obj->value : nullptr)->mPurchaseActive = value;
}

extern "C" Object<com::mojang::minecraftpe::store::Store>* com_mojang_minecraftpe_store_StoreFactory_createGooglePlayStore(va_list list) {
    using Param = std::tuple<Object<java::lang::String>*, Object<com::mojang::minecraftpe::store::StoreListener>*>;
    Param param;
    std::get<0>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<1>(param) = va_arg(list, Object<com::mojang::minecraftpe::store::StoreListener>*);
    return std::apply(&com::mojang::minecraftpe::store::StoreFactory::createGooglePlayStore, param);
}

extern "C" Object<com::mojang::minecraftpe::store::Store>* com_mojang_minecraftpe_store_StoreFactory_createAmazonAppStore(va_list list) {
    using Param = std::tuple<Object<com::mojang::minecraftpe::store::StoreListener>*, jboolean>;
    Param param;
    std::get<0>(param) = va_arg(list, Object<com::mojang::minecraftpe::store::StoreListener>*);
    std::get<1>(param) = va_arg(list, int);
    return std::apply(&com::mojang::minecraftpe::store::StoreFactory::createAmazonAppStore, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_store_Store_getStoreId(Object<com::mojang::minecraftpe::store::Store>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::store::Store*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::store::Store::getStoreId, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_store_Store_getProductSkuPrefix(Object<com::mojang::minecraftpe::store::Store>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::store::Store*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::store::Store::getProductSkuPrefix, param);
}

extern "C" Object<java::lang::String>* com_mojang_minecraftpe_store_Store_getRealmsSkuPrefix(Object<com::mojang::minecraftpe::store::Store>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::store::Store*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::store::Store::getRealmsSkuPrefix, param);
}

extern "C" jboolean com_mojang_minecraftpe_store_Store_hasVerifiedLicense(Object<com::mojang::minecraftpe::store::Store>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::store::Store*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::store::Store::hasVerifiedLicense, param);
}

extern "C" Object<com::mojang::minecraftpe::store::ExtraLicenseResponseData>* com_mojang_minecraftpe_store_Store_getExtraLicenseData(Object<com::mojang::minecraftpe::store::Store>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::store::Store*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::store::Store::getExtraLicenseData, param);
}

extern "C" jboolean com_mojang_minecraftpe_store_Store_receivedLicenseResponse(Object<com::mojang::minecraftpe::store::Store>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::store::Store*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::store::Store::receivedLicenseResponse, param);
}

extern "C" void com_mojang_minecraftpe_store_Store_queryProducts(Object<com::mojang::minecraftpe::store::Store>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::store::Store*, Array<Object<java::lang::String>*>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Array<Object<java::lang::String>*>*);
    return std::apply(&com::mojang::minecraftpe::store::Store::queryProducts, param);
}

extern "C" void com_mojang_minecraftpe_store_Store_purchase(Object<com::mojang::minecraftpe::store::Store>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::store::Store*, Object<java::lang::String>*, jboolean, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<2>(param) = va_arg(list, int);
    std::get<3>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::store::Store::purchase, param);
}

extern "C" void com_mojang_minecraftpe_store_Store_acknowledgePurchase(Object<com::mojang::minecraftpe::store::Store>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::store::Store*, Object<java::lang::String>*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    std::get<2>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&com::mojang::minecraftpe::store::Store::acknowledgePurchase, param);
}

extern "C" void com_mojang_minecraftpe_store_Store_queryPurchases(Object<com::mojang::minecraftpe::store::Store>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::store::Store*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::store::Store::queryPurchases, param);
}

extern "C" void com_mojang_minecraftpe_store_Store_destructor(Object<com::mojang::minecraftpe::store::Store>* obj, va_list list) {
    using Param = std::tuple<com::mojang::minecraftpe::store::Store*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&com::mojang::minecraftpe::store::Store::destructor, param);
}

extern "C" jint get_android_os_Build_VERSION_SDK_INT() {
    return android::os::Build::VERSION::SDK_INT;
}

extern "C" void set_android_os_Build_VERSION_SDK_INT(jint value) {
    android::os::Build::VERSION::SDK_INT = value;
}

extern "C" Object<android::view::View>* android_view_Window_getDecorView(Object<android::view::Window>* obj, va_list list) {
    using Param = std::tuple<android::view::Window*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&android::view::Window::getDecorView, param);
}

extern "C" Object<android::os::IBinder>* android_view_View_getWindowToken(Object<android::view::View>* obj, va_list list) {
    using Param = std::tuple<android::view::View*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&android::view::View::getWindowToken, param);
}

extern "C" jboolean android_view_inputmethod_InputMethodManager_showSoftInput(Object<android::view::inputmethod::InputMethodManager>* obj, va_list list) {
    using Param = std::tuple<android::view::inputmethod::InputMethodManager*, Object<android::view::View>*, jint>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<android::view::View>*);
    std::get<2>(param) = va_arg(list, jint);
    return std::apply(&android::view::inputmethod::InputMethodManager::showSoftInput, param);
}

extern "C" jboolean android_view_inputmethod_InputMethodManager_hideSoftInputFromWindow(Object<android::view::inputmethod::InputMethodManager>* obj, va_list list) {
    using Param = std::tuple<android::view::inputmethod::InputMethodManager*, Object<android::os::IBinder>*, jint>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<android::os::IBinder>*);
    std::get<2>(param) = va_arg(list, jint);
    return std::apply(&android::view::inputmethod::InputMethodManager::hideSoftInputFromWindow, param);
}

extern "C" Object<java::lang::String>* get_android_content_Context_INPUT_METHOD_SERVICE() {
    return android::content::Context::INPUT_METHOD_SERVICE;
}

extern "C" void set_android_content_Context_INPUT_METHOD_SERVICE(Object<java::lang::String>* value) {
    android::content::Context::INPUT_METHOD_SERVICE = value;
}

extern "C" void android_content_Context_startActivity(Object<android::content::Context>* obj, va_list list) {
    using Param = std::tuple<android::content::Context*, Object<android::content::Intent>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<android::content::Intent>*);
    return std::apply(&android::content::Context::startActivity, param);
}

extern "C" Object<java::io::File>* android_content_ContextWrapper_getFilesDir(Object<android::content::ContextWrapper>* obj, va_list list) {
    using Param = std::tuple<android::content::ContextWrapper*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&android::content::ContextWrapper::getFilesDir, param);
}

extern "C" Object<java::io::File>* android_content_ContextWrapper_getCacheDir(Object<android::content::ContextWrapper>* obj, va_list list) {
    using Param = std::tuple<android::content::ContextWrapper*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&android::content::ContextWrapper::getCacheDir, param);
}

extern "C" Object<android::content::Context>* android_app_NativeActivity_getApplicationContext(Object<android::app::NativeActivity>* obj, va_list list) {
    using Param = std::tuple<android::app::NativeActivity*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&android::app::NativeActivity::getApplicationContext, param);
}

extern "C" Object<java::lang::Class>* java_lang_ClassLoader_loadClass(Object<java::lang::ClassLoader>* obj, va_list list) {
    using Param = std::tuple<java::lang::ClassLoader*, Object<java::lang::String>*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    std::get<1>(param) = va_arg(list, Object<java::lang::String>*);
    return std::apply(&java::lang::ClassLoader::loadClass, param);
}

extern "C" Object<java::lang::String>* java_io_File_getPath(Object<java::io::File>* obj, va_list list) {
    using Param = std::tuple<java::io::File*>;
    Param param;
    std::get<0>(param) = (obj ? obj->value : nullptr);
    return std::apply(&java::io::File::getPath, param);
}

Object<java::lang::String>* android::content::Context::INPUT_METHOD_SERVICE = new Object<java::lang::String> { .cl = 0, .value = new java::lang::String { "INPUT_METHOD_SERVICE" } };