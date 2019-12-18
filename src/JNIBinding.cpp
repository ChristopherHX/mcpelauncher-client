
#include <tuple>
#include <vector>
#include <fstream>
#include <jni.h>
#include <jnivm.h>
#include <log.h>
#include <mcpelauncher/path_helper.h>
#include <sstream>
#include "client_app_platform.h"
#include "xbox_live_game_interface.h"
#include "xbox_live_helper.h"
#ifdef HAS_LIBPNG
#include <png.h>
#endif
#include <file_picker_factory.h>
#include <hybris/dlfcn.h>
#include <mcpelauncher/path_helper.h>

namespace jnivm {
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
        namespace android {
            namespace net {
                class HTTPResponse;
                class HTTPRequest;
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
        class Activity;
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
namespace org {
    namespace apache {
        namespace http {
            class Header;
        }
    }
}
class XBLoginCallback;
}
using namespace jnivm;

class jnivm::XBLoginCallback : public jnivm::java::lang::Object {
public:
    jlong userptr;
    std::string cid;
    std::string token;
    std::unordered_map<std::string,void*>* cl;
    void(*auth_flow_callback)(JNIEnv *env, void*, jlong paramLong, jint paramInt, jstring paramString);
    void onLogin(JNIEnv *, jlong, jboolean);
    void onError(JNIEnv *, jint, jint, jnivm::java::lang::String*);
    void onSuccess(JNIEnv *);
};
class com::mojang::minecraftpe::MainActivity : public jnivm::java::lang::Object {
public:
    static void saveScreenshot(JNIEnv *, jnivm::java::lang::String*, jint, jint, jnivm::Array<jint>*);
    void postScreenshotToFacebook(JNIEnv *, jnivm::java::lang::String*, jint, jint, jnivm::Array<jint>*);
    jnivm::Array<jint>* getImageData(JNIEnv *, jnivm::java::lang::String*);
    jnivm::Array<jbyte>* getFileDataBytes(JNIEnv *, jnivm::java::lang::String*);
    void displayDialog(JNIEnv *, jint);
    void tick(JNIEnv *);
    void quit(JNIEnv *);
    void initiateUserInput(JNIEnv *, jint);
    jint getUserInputStatus(JNIEnv *);
    jnivm::Array<jnivm::java::lang::String*>* getUserInputString(JNIEnv *);
    jint checkLicense(JNIEnv *);
    jboolean hasBuyButtonWhenInvalidLicense(JNIEnv *);
    void buyGame(JNIEnv *);
    void vibrate(JNIEnv *, jint);
    void setIsPowerVR(JNIEnv *, jboolean);
    jboolean isNetworkEnabled(JNIEnv *, jboolean);
    jfloat getPixelsPerMillimeter(JNIEnv *);
    jnivm::java::lang::String* getPlatformStringVar(JNIEnv *, jint);
    jnivm::java::lang::Object* getSystemService(JNIEnv *, jnivm::java::lang::String*);
    jnivm::android::view::Window* getWindow(JNIEnv *);
    jint getKeyFromKeyCode(JNIEnv *, jint, jint, jint);
    void updateLocalization(JNIEnv *, jnivm::java::lang::String*, jnivm::java::lang::String*);
    void showKeyboard(JNIEnv *, jnivm::java::lang::String*, jint, jboolean, jboolean, jboolean);
    void hideKeyboard(JNIEnv *);
    jfloat getKeyboardHeight(JNIEnv *);
    void updateTextboxText(JNIEnv *, jnivm::java::lang::String*);
    jint getCursorPosition(JNIEnv *);
    jnivm::java::lang::String* getAccessToken(JNIEnv *);
    jnivm::java::lang::String* getClientId(JNIEnv *);
    jnivm::java::lang::String* getProfileId(JNIEnv *);
    jnivm::java::lang::String* getProfileName(JNIEnv *);
    jnivm::Array<jnivm::java::lang::String*>* getBroadcastAddresses(JNIEnv *);
    jnivm::Array<jnivm::java::lang::String*>* getIPAddresses(JNIEnv *);
    jlong getTotalMemory(JNIEnv *);
    jlong getMemoryLimit(JNIEnv *);
    jlong getUsedMemory(JNIEnv *);
    jlong getFreeMemory(JNIEnv *);
    void launchUri(JNIEnv *, jnivm::java::lang::String*);
    void setClipboard(JNIEnv *, jnivm::java::lang::String*);
    void share(JNIEnv *, jnivm::java::lang::String*, jnivm::java::lang::String*, jnivm::java::lang::String*);
    jnivm::android::content::Intent* createAndroidLaunchIntent(JNIEnv *);
    jlong calculateAvailableDiskFreeSpace(JNIEnv *, jnivm::java::lang::String*);
    jnivm::java::lang::String* getExternalStoragePath(JNIEnv *);
    void requestStoragePermission(JNIEnv *, jint);
    jboolean hasWriteExternalStoragePermission(JNIEnv *);
    void deviceIdCorrelationStart(JNIEnv *);
    jboolean isMixerCreateInstalled(JNIEnv *);
    void navigateToPlaystoreForMixerCreate(JNIEnv *);
    jboolean launchMixerCreateForBroadcast(JNIEnv *);
    jboolean isTTSEnabled(JNIEnv *);
    jnivm::com::mojang::minecraftpe::HardwareInformation* getHardwareInfo(JNIEnv *);
    void setCachedDeviceId(JNIEnv *, jnivm::java::lang::String*);
    void setLastDeviceSessionId(JNIEnv *, jnivm::java::lang::String*);
    jnivm::java::lang::String* getLastDeviceSessionId(JNIEnv *);
    jint getAPIVersion(JNIEnv *, jnivm::java::lang::String*);
    jnivm::java::lang::String* getSecureStorageKey(JNIEnv *, jnivm::java::lang::String*);
    void setSecureStorageKey(JNIEnv *, jnivm::java::lang::String*, jnivm::java::lang::String*);
    void trackPurchaseEvent(JNIEnv *, jnivm::java::lang::String*, jnivm::java::lang::String*, jnivm::java::lang::String*, jnivm::java::lang::String*, jnivm::java::lang::String*, jnivm::java::lang::String*, jnivm::java::lang::String*, jnivm::java::lang::String*);
    void sendBrazeEvent(JNIEnv *, jnivm::java::lang::String*);
    void sendBrazeEventWithProperty(JNIEnv *, jnivm::java::lang::String*, jnivm::java::lang::String*, jint);
    void sendBrazeEventWithStringProperty(JNIEnv *, jnivm::java::lang::String*, jnivm::java::lang::String*, jnivm::java::lang::String*);
    void sendBrazeToastClick(JNIEnv *);
    void sendBrazeDialogButtonClick(JNIEnv *, jint);
    void pickImage(JNIEnv *, jlong);
    void setFileDialogCallback(JNIEnv *, jlong);
    jnivm::java::lang::String* getLegacyDeviceID(JNIEnv *);
    jnivm::java::lang::String* createUUID(JNIEnv *);
    jboolean hasHardwareKeyboard(JNIEnv *);
    void startTextToSpeech(JNIEnv *, jnivm::java::lang::String*);
    void stopTextToSpeech(JNIEnv *);
    jboolean isTextToSpeechInProgress(JNIEnv *);
    void setTextToSpeechEnabled(JNIEnv *, jboolean);
    jint getScreenWidth(JNIEnv *);
    jint getScreenHeight(JNIEnv *);
    jnivm::java::lang::String* getDeviceModel(JNIEnv *);
    jint getAndroidVersion(JNIEnv *);
    jnivm::java::lang::String* getLocale(JNIEnv *);
    jboolean isFirstSnooperStart(JNIEnv *);
    jboolean hasHardwareChanged(JNIEnv *);
    jboolean isTablet(JNIEnv *);
    jnivm::java::lang::ClassLoader* getClassLoader(JNIEnv *);
};
class com::mojang::minecraftpe::HardwareInformation : public jnivm::java::lang::Object {
public:
    static jnivm::java::lang::String* getDeviceModelName(JNIEnv *);
    static jnivm::java::lang::String* getAndroidVersion(JNIEnv *);
    static jnivm::java::lang::String* getCPUType(JNIEnv *);
    static jnivm::java::lang::String* getCPUName(JNIEnv *);
    static jnivm::java::lang::String* getCPUFeatures(JNIEnv *);
    static jint getNumCores(JNIEnv *);
    jnivm::java::lang::String* getSecureId(JNIEnv *);
    static jnivm::java::lang::String* getSerialNumber(JNIEnv *);
    static jnivm::java::lang::String* getBoard(JNIEnv *);
    jnivm::java::lang::String* getInstallerPackageName(JNIEnv *);
    jint getSignaturesHashCode(JNIEnv *);
    jboolean getIsRooted(JNIEnv *);
};
class com::mojang::minecraftpe::store::NativeStoreListener : public jnivm::java::lang::Object {
public:
    NativeStoreListener(JNIEnv *, jlong);
};
class com::mojang::minecraftpe::store::Product : public jnivm::java::lang::Object {
public:
    jnivm::java::lang::String* mId;
    jnivm::java::lang::String* mPrice;
    jnivm::java::lang::String* mCurrencyCode;
    jnivm::java::lang::String* mUnformattedPrice;
};
class com::mojang::minecraftpe::store::Purchase : public jnivm::java::lang::Object {
public:
    jnivm::java::lang::String* mProductId;
    jnivm::java::lang::String* mReceipt;
    jboolean mPurchaseActive;
};
class com::mojang::minecraftpe::store::StoreFactory : public jnivm::java::lang::Object {
public:
    static jnivm::com::mojang::minecraftpe::store::Store* createGooglePlayStore(JNIEnv *, jnivm::java::lang::String*, jnivm::com::mojang::minecraftpe::store::StoreListener*);
    static jnivm::com::mojang::minecraftpe::store::Store* createAmazonAppStore(JNIEnv *, jnivm::com::mojang::minecraftpe::store::StoreListener*, jboolean);
};
class com::mojang::minecraftpe::store::StoreListener : public jnivm::java::lang::Object {
public:
};
class com::mojang::minecraftpe::store::Store : public jnivm::java::lang::Object {
public:
    jnivm::java::lang::String* getStoreId(JNIEnv *);
    jnivm::java::lang::String* getProductSkuPrefix(JNIEnv *);
    jnivm::java::lang::String* getRealmsSkuPrefix(JNIEnv *);
    jboolean hasVerifiedLicense(JNIEnv *);
    jnivm::com::mojang::minecraftpe::store::ExtraLicenseResponseData* getExtraLicenseData(JNIEnv *);
    jboolean receivedLicenseResponse(JNIEnv *);
    void queryProducts(JNIEnv *, jnivm::Array<jnivm::java::lang::String*>*);
    void purchase(JNIEnv *, jnivm::java::lang::String*, jboolean, jnivm::java::lang::String*);
    void acknowledgePurchase(JNIEnv *, jnivm::java::lang::String*, jnivm::java::lang::String*);
    void queryPurchases(JNIEnv *);
    void destructor(JNIEnv *);
};
class com::mojang::minecraftpe::store::ExtraLicenseResponseData : public jnivm::java::lang::Object {
public:
    jlong getValidationTime(JNIEnv *);
    jlong getRetryUntilTime(JNIEnv *);
    jlong getRetryAttempts(JNIEnv *);
};

class com::mojang::android::net::HTTPResponse : public jnivm::java::lang::Object {
public:
    jint getStatus(JNIEnv *);
    jnivm::java::lang::String* getBody(JNIEnv *);
    jint getResponseCode(JNIEnv *);
    jnivm::Array<jnivm::org::apache::http::Header*>* getHeaders(JNIEnv *);
};
class com::mojang::android::net::HTTPRequest : public jnivm::java::lang::Object {
public:
    HTTPRequest(JNIEnv *);
    void setURL(JNIEnv *, jnivm::java::lang::String*);
    void setRequestBody(JNIEnv *, jnivm::java::lang::String*);
    void setCookieData(JNIEnv *, jnivm::java::lang::String*);
    void setContentType(JNIEnv *, jnivm::java::lang::String*);
    jnivm::com::mojang::android::net::HTTPResponse* send(JNIEnv *, jnivm::java::lang::String*);
    void abort(JNIEnv *);
};

class com::microsoft::xbox::idp::interop::Interop : public jnivm::java::lang::Object {
public:
    static jnivm::java::lang::String* GetLocalStoragePath(JNIEnv *, jnivm::android::content::Context*);
    static jnivm::java::lang::String* ReadConfigFile(JNIEnv *, jnivm::android::content::Context*);
    static jnivm::java::lang::String* getSystemProxy(JNIEnv *);
    static void InitCLL(JNIEnv *, jnivm::android::content::Context*, jnivm::java::lang::String*);
    static void LogTelemetrySignIn(JNIEnv *, jnivm::java::lang::String*, jnivm::java::lang::String*);
    static void InvokeMSA(JNIEnv *, jnivm::android::content::Context*, jint, jboolean, jnivm::java::lang::String*);
    static void InvokeAuthFlow(JNIEnv *, jlong, jnivm::android::app::Activity*, jboolean, jnivm::java::lang::String*);
    static jnivm::java::lang::String* getLocale(JNIEnv *);
    static void RegisterWithGNS(JNIEnv *, jnivm::android::content::Context*);
    static void LogCLL(JNIEnv *, jnivm::java::lang::String*, jnivm::java::lang::String*, jnivm::java::lang::String*);
};
class com::microsoft::xbox::idp::interop::LocalConfig : public jnivm::java::lang::Object {
public:
};
class com::microsoft::xbox::idp::interop::XboxLiveAppConfig : public jnivm::java::lang::Object {
public:
};

class com::microsoft::xbox::idp::util::HttpCall : public jnivm::java::lang::Object {
public:
};
class com::microsoft::xbox::idp::util::AuthFlowResult : public jnivm::java::lang::Object {
public:
};



class com::microsoft::xboxtcui::Interop : public jnivm::java::lang::Object {
public:
};


class android::os::Build : public jnivm::java::lang::Object {
public:
    class VERSION;
};
class android::os::Build::VERSION : public jnivm::java::lang::Object {
public:
    static jint SDK_INT;
};
class android::os::IBinder : public jnivm::java::lang::Object {
public:
};

class android::view::Window : public jnivm::java::lang::Object {
public:
    jnivm::android::view::View* getDecorView(JNIEnv *);
};
class android::view::View : public jnivm::java::lang::Object {
public:
    jnivm::android::os::IBinder* getWindowToken(JNIEnv *);
};
class android::view::inputmethod::InputMethodManager : public jnivm::java::lang::Object {
public:
    jboolean showSoftInput(JNIEnv *, jnivm::android::view::View*, jint);
    jboolean hideSoftInputFromWindow(JNIEnv *, jnivm::android::os::IBinder*, jint);
};


class android::content::Context : public jnivm::java::lang::Object {
public:
    static jnivm::java::lang::String* INPUT_METHOD_SERVICE;
    void startActivity(JNIEnv *, jnivm::android::content::Intent*);
    jnivm::java::lang::String* getPackageName(JNIEnv *);
};
class android::content::Intent : public jnivm::java::lang::Object {
public:
};
class android::content::ContextWrapper : public jnivm::java::lang::Object {
public:
    jnivm::java::io::File* getFilesDir(JNIEnv *);
    jnivm::java::io::File* getCacheDir(JNIEnv *);
};

class android::app::NativeActivity : public jnivm::java::lang::Object {
public:
    jnivm::android::content::Context* getApplicationContext(JNIEnv *);
};
class android::app::Activity : public jnivm::java::lang::Object {
public:
};


class java::lang::String : public jnivm::java::lang::Object {
public:
    std::string str;
};
class java::lang::Object : public jnivm::java::lang::Object {
public:
};
class java::lang::ClassLoader : public jnivm::java::lang::Object {
public:
    jnivm::java::lang::Class* loadClass(JNIEnv *, jnivm::java::lang::String*);
};
class java::lang::Class : public jnivm::java::lang::Object {
public:
};

class java::io::File : public jnivm::java::lang::String {
public:
    using jnivm::java::lang::String::String;
    jnivm::java::lang::String* getPath(JNIEnv *);
};

void XBLoginCallback::onLogin(JNIEnv *env, jlong arg0, jboolean arg1) {
    auto invoke_event_initialization = (void (*)(JNIEnv *env, jclass, jlong var0, jstring var2, XBLoginCallback* var3))cl->at("invoke_event_initialization");
    auto XBLoginCallbackcl = env->FindClass("XBLoginCallback");
    invoke_event_initialization(env, nullptr, userptr, env->NewStringUTF(token.data()), this);
}

void XBLoginCallback::onSuccess(JNIEnv *env) {
    auth_flow_callback(env, nullptr, userptr, /* No Error */0, env->NewStringUTF(cid.data()));    
}

void XBLoginCallback::onError(JNIEnv *env, jint arg0, jint arg1, jnivm::java::lang::String* arg2) {
    // ToDo Errorhandling
    // auth_flow_callback(env, nullptr, userptr, /* No Error */0, env->NewStringUTF(cid.data()));        
}

void com::mojang::minecraftpe::MainActivity::saveScreenshot(JNIEnv *env, jnivm::java::lang::String* arg0, jint arg1, jint arg2, jnivm::Array<jint>* arg3) {
    
}

void com::mojang::minecraftpe::MainActivity::postScreenshotToFacebook(JNIEnv *env, jnivm::java::lang::String* arg0, jint arg1, jint arg2, jnivm::Array<jint>* arg3) {
    
}

jnivm::Array<jint>* com::mojang::minecraftpe::MainActivity::getImageData(JNIEnv *env, jnivm::java::lang::String* arg0) {
#ifdef HAS_LIBPNG
    uint8_t header[8];
    FILE *fp = fopen(arg0->value->str.data(), "rb");
    if(fp) {
        int read = fread(header, 1, 8, fp);
        png_sig_cmp(header, 0, 8);
        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        png_infop info_ptr = png_create_info_struct(png_ptr);
        setjmp(png_jmpbuf(png_ptr));
        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);
        png_read_info(png_ptr, info_ptr);
        auto width = png_get_image_width(png_ptr, info_ptr);
        auto height = png_get_image_height(png_ptr, info_ptr);
        auto bit_depth = png_get_bit_depth(png_ptr, info_ptr);    
        auto color_type = png_get_color_type(png_ptr, info_ptr);
        png_read_update_info(png_ptr, info_ptr);
        setjmp(png_jmpbuf(png_ptr));
        auto rowbytes = width * (bit_depth >> 1);
        auto ret = new jnivm::Array<jint>();
        ret->cl = 0;
        ret->length = 2 + width * height;
        ret->value = new jint[ret->length] { 0 };
        auto buffer = new uint8_t*[height];
        for (int y = 0; y < height; y++)
            buffer[y] = (uint8_t*)(ret->value + 2 + width * y);
        png_read_image(png_ptr, buffer);
        delete[] buffer;
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        return ret;
    }
#endif
    return 0;
}

jnivm::Array<jbyte>* com::mojang::minecraftpe::MainActivity::getFileDataBytes(JNIEnv *env, jnivm::java::lang::String* arg0) {
    return 0;
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
    return 0;
}

jnivm::Array<jnivm::java::lang::String*>* com::mojang::minecraftpe::MainActivity::getUserInputString(JNIEnv *env) {
    return 0;
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

jnivm::java::lang::String* com::mojang::minecraftpe::MainActivity::getPlatformStringVar(JNIEnv *env, jint arg0) {
    return (jnivm::java::lang::String*)env->NewStringUTF("Android");
}

jnivm::java::lang::Object* com::mojang::minecraftpe::MainActivity::getSystemService(JNIEnv *env, jnivm::java::lang::String* arg0) {
    auto sc = new jnivm::java::lang::Object();
    sc->clazz = (jnivm::java::lang::Class*)env->FindClass("android/lang/Object");
    return sc;
}

jnivm::android::view::Window* com::mojang::minecraftpe::MainActivity::getWindow(JNIEnv *env) {
    auto w = new jnivm::android::view::Window();
    w->clazz = (jnivm::java::lang::Class*)env->FindClass("android/view/Window");
    return w;
}

jint com::mojang::minecraftpe::MainActivity::getKeyFromKeyCode(JNIEnv *env, jint arg0, jint arg1, jint arg2) {
    return arg0;
}

void com::mojang::minecraftpe::MainActivity::updateLocalization(JNIEnv *env, jnivm::java::lang::String* arg0, jnivm::java::lang::String* arg1) {
    
}

void com::mojang::minecraftpe::MainActivity::showKeyboard(JNIEnv *env, jnivm::java::lang::String* arg0, jint arg1, jboolean arg2, jboolean arg3, jboolean arg4) {
    
}

void com::mojang::minecraftpe::MainActivity::hideKeyboard(JNIEnv *env) {
    
}

jfloat com::mojang::minecraftpe::MainActivity::getKeyboardHeight(JNIEnv *env) {
    return 0;
}

void com::mojang::minecraftpe::MainActivity::updateTextboxText(JNIEnv *env, jnivm::java::lang::String* arg0) {
    
}

jint com::mojang::minecraftpe::MainActivity::getCursorPosition(JNIEnv *env) {
    return 0;
}

jnivm::java::lang::String* com::mojang::minecraftpe::MainActivity::getAccessToken(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("Android");
}

jnivm::java::lang::String* com::mojang::minecraftpe::MainActivity::getClientId(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("Android");
}

jnivm::java::lang::String* com::mojang::minecraftpe::MainActivity::getProfileId(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("Android");
}

jnivm::java::lang::String* com::mojang::minecraftpe::MainActivity::getProfileName(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("Android");
}

jnivm::Array<jnivm::java::lang::String*>* com::mojang::minecraftpe::MainActivity::getBroadcastAddresses(JNIEnv *env) {
    return nullptr;
}

jnivm::Array<jnivm::java::lang::String*>* com::mojang::minecraftpe::MainActivity::getIPAddresses(JNIEnv *env) {
    return nullptr;
}

jlong com::mojang::minecraftpe::MainActivity::getTotalMemory(JNIEnv *env) {
    return ((LauncherAppPlatform*)0)->getTotalPhysicalMemory();
}

jlong com::mojang::minecraftpe::MainActivity::getMemoryLimit(JNIEnv *env) {
    return ((LauncherAppPlatform*)0)->getMemoryLimit();    
}

jlong com::mojang::minecraftpe::MainActivity::getUsedMemory(JNIEnv *env) {
    return ((LauncherAppPlatform*)0)->getUsedMemory();    
}

jlong com::mojang::minecraftpe::MainActivity::getFreeMemory(JNIEnv *env) {
    return ((LauncherAppPlatform*)0)->getFreeMemory();        
}

void com::mojang::minecraftpe::MainActivity::launchUri(JNIEnv *env, jnivm::java::lang::String* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setClipboard(JNIEnv *env, jnivm::java::lang::String* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::share(JNIEnv *env, jnivm::java::lang::String* arg0, jnivm::java::lang::String* arg1, jnivm::java::lang::String* arg2) {
    
}

jnivm::android::content::Intent* com::mojang::minecraftpe::MainActivity::createAndroidLaunchIntent(JNIEnv *env) {
    return 0;
}

jlong com::mojang::minecraftpe::MainActivity::calculateAvailableDiskFreeSpace(JNIEnv *env, jnivm::java::lang::String* arg0) {
    return -1;
}

jnivm::java::lang::String* com::mojang::minecraftpe::MainActivity::getExternalStoragePath(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF(PathHelper::getPrimaryDataDirectory().data());
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
    return false;
}

jboolean com::mojang::minecraftpe::MainActivity::isTTSEnabled(JNIEnv *env) {
    return false;
}

jnivm::com::mojang::minecraftpe::HardwareInformation* com::mojang::minecraftpe::MainActivity::getHardwareInfo(JNIEnv *env) {
    auto hw = new jnivm::com::mojang::minecraftpe::HardwareInformation();
    hw->clazz = (jnivm::java::lang::Class*)env->FindClass("com/mojang/minecraftpe/HardwareInformation");
    return hw;
}

void com::mojang::minecraftpe::MainActivity::setCachedDeviceId(JNIEnv *env, jnivm::java::lang::String* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setLastDeviceSessionId(JNIEnv *env, jnivm::java::lang::String* arg0) {
    
}

jnivm::java::lang::String* com::mojang::minecraftpe::MainActivity::getLastDeviceSessionId(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("");
}

jint com::mojang::minecraftpe::MainActivity::getAPIVersion(JNIEnv *env, jnivm::java::lang::String* arg0) {
    return 27;
}

jnivm::java::lang::String* com::mojang::minecraftpe::MainActivity::getSecureStorageKey(JNIEnv *env, jnivm::java::lang::String* arg0) {
    return (jnivm::java::lang::String*)env->NewStringUTF("Unknown");
}

void com::mojang::minecraftpe::MainActivity::setSecureStorageKey(JNIEnv *env, jnivm::java::lang::String* arg0, jnivm::java::lang::String* arg1) {
    
}

void com::mojang::minecraftpe::MainActivity::trackPurchaseEvent(JNIEnv *env, jnivm::java::lang::String* arg0, jnivm::java::lang::String* arg1, jnivm::java::lang::String* arg2, jnivm::java::lang::String* arg3, jnivm::java::lang::String* arg4, jnivm::java::lang::String* arg5, jnivm::java::lang::String* arg6, jnivm::java::lang::String* arg7) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeEvent(JNIEnv *env, jnivm::java::lang::String* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeEventWithProperty(JNIEnv *env, jnivm::java::lang::String* arg0, jnivm::java::lang::String* arg1, jint arg2) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeEventWithStringProperty(JNIEnv *env, jnivm::java::lang::String* arg0, jnivm::java::lang::String* arg1, jnivm::java::lang::String* arg2) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeToastClick(JNIEnv *env) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeDialogButtonClick(JNIEnv *env, jint arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::pickImage(JNIEnv *env, jlong arg0) {
    Log::trace("MainActivity", "pickImage");
    auto picker = FilePickerFactory::createFilePicker();
    picker->setTitle("Select image");
    picker->setFileNameFilters({ "*.png" });
    if (picker->show()) {
        auto nativeOnPickImageSuccess = (void(*)(JNIEnv*, void*, jlong var1, jstring var3))hybris_dlsym(env->functions->reserved2, "Java_com_mojang_minecraftpe_MainActivity_nativeOnPickImageSuccess");
        nativeOnPickImageSuccess(env, nullptr, arg0, env->NewStringUTF(picker->getPickedFile().data()));
    } else {
        auto nativeOnPickImageCanceled = (void(*)(JNIEnv*, void*, jlong var1))hybris_dlsym(env->functions->reserved2, "Java_com_mojang_minecraftpe_MainActivity_nativeOnPickImageCanceled");
        nativeOnPickImageCanceled(env, nullptr, arg0);
    }
}

void com::mojang::minecraftpe::MainActivity::setFileDialogCallback(JNIEnv *env, jlong arg0) {
    
}

jnivm::java::lang::String* com::mojang::minecraftpe::MainActivity::getLegacyDeviceID(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("19af3ae9-b15a-44b0-a3c2-aa2c66df489e");
}

jnivm::java::lang::String* com::mojang::minecraftpe::MainActivity::createUUID(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("daa78df1-373a-444d-9b1d-4c71a14bb559");
}

jboolean com::mojang::minecraftpe::MainActivity::hasHardwareKeyboard(JNIEnv *env) {
    return true;
}

void com::mojang::minecraftpe::MainActivity::startTextToSpeech(JNIEnv *env, jnivm::java::lang::String* arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::stopTextToSpeech(JNIEnv *env) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isTextToSpeechInProgress(JNIEnv *env) {
    // return false;
    return false;
}

void com::mojang::minecraftpe::MainActivity::setTextToSpeechEnabled(JNIEnv *env, jboolean arg0) {
    
}

jint com::mojang::minecraftpe::MainActivity::getScreenWidth(JNIEnv *env) {
    return 0;
}

jint com::mojang::minecraftpe::MainActivity::getScreenHeight(JNIEnv *env) {
    return 0;    
}

jnivm::java::lang::String* com::mojang::minecraftpe::MainActivity::getDeviceModel(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("Android");
}

jint com::mojang::minecraftpe::MainActivity::getAndroidVersion(JNIEnv *env) {
    return 28;
}

jnivm::java::lang::String* com::mojang::minecraftpe::MainActivity::getLocale(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("en");
}

jboolean com::mojang::minecraftpe::MainActivity::isFirstSnooperStart(JNIEnv *env) {
    return false;
}

jboolean com::mojang::minecraftpe::MainActivity::hasHardwareChanged(JNIEnv *env) {
    return false;
}

jboolean com::mojang::minecraftpe::MainActivity::isTablet(JNIEnv *env) {
    return false;
}

jnivm::java::lang::ClassLoader* com::mojang::minecraftpe::MainActivity::getClassLoader(JNIEnv *env) {
    auto hw = new jnivm::java::lang::ClassLoader();
    hw->clazz = (jnivm::java::lang::Class*)env->FindClass("java/lang/ClassLoader");
    return hw;
}

jnivm::java::lang::String* com::mojang::minecraftpe::HardwareInformation::getDeviceModelName(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("Android");
}

jnivm::java::lang::String* com::mojang::minecraftpe::HardwareInformation::getAndroidVersion(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("");
}

jnivm::java::lang::String* com::mojang::minecraftpe::HardwareInformation::getCPUType(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("");
}

jnivm::java::lang::String* com::mojang::minecraftpe::HardwareInformation::getCPUName(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("");
}

jnivm::java::lang::String* com::mojang::minecraftpe::HardwareInformation::getCPUFeatures(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("");
}

jint com::mojang::minecraftpe::HardwareInformation::getNumCores(JNIEnv *env) {
    return 4;
}

jnivm::java::lang::String* com::mojang::minecraftpe::HardwareInformation::getSecureId(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("0000000000000000");
}

jnivm::java::lang::String* com::mojang::minecraftpe::HardwareInformation::getSerialNumber(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("");
}

jnivm::java::lang::String* com::mojang::minecraftpe::HardwareInformation::getBoard(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("Android");
}

jnivm::java::lang::String* com::mojang::minecraftpe::HardwareInformation::getInstallerPackageName(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("com.mojang.minecraftpe");
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

jnivm::com::mojang::minecraftpe::store::Store* com::mojang::minecraftpe::store::StoreFactory::createGooglePlayStore(JNIEnv *env, jnivm::java::lang::String* arg0, jnivm::com::mojang::minecraftpe::store::StoreListener* arg1) {
    auto store = new jnivm::com::mojang::minecraftpe::store::Store();
    store->clazz = (jnivm::java::lang::Class*)env->FindClass("com/mojang/minecraftpe/store/Store");
    auto callback = (void(*)(JNIEnv*,jnivm::com::mojang::minecraftpe::store::StoreListener*, jlong, jboolean)) env->functions->reserved3;
    callback(env, arg1, nativestore, true);
    return store;
}

jnivm::com::mojang::minecraftpe::store::Store* com::mojang::minecraftpe::store::StoreFactory::createAmazonAppStore(JNIEnv *env, jnivm::com::mojang::minecraftpe::store::StoreListener* arg0, jboolean arg1) {
    // return new jnivm::com::mojang::minecraftpe::store::Store { env->FindClass("com/mojang/minecraftpe/store/Store"), new com::mojang::minecraftpe::store::Store() };    
    return nullptr;
}

jnivm::java::lang::String* com::mojang::minecraftpe::store::Store::getStoreId(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("android.googleplay");
}

jnivm::java::lang::String* com::mojang::minecraftpe::store::Store::getProductSkuPrefix(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("com.linux");
}

jnivm::java::lang::String* com::mojang::minecraftpe::store::Store::getRealmsSkuPrefix(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("com.linux");
}

jboolean com::mojang::minecraftpe::store::Store::hasVerifiedLicense(JNIEnv *env) {
    return true;
}

jnivm::com::mojang::minecraftpe::store::ExtraLicenseResponseData* com::mojang::minecraftpe::store::Store::getExtraLicenseData(JNIEnv *env) {
    return 0;
}

jboolean com::mojang::minecraftpe::store::Store::receivedLicenseResponse(JNIEnv *env) {
    return true;
}

void com::mojang::minecraftpe::store::Store::queryProducts(JNIEnv *env, jnivm::Array<jnivm::java::lang::String*>* arg0) {
    
}

void com::mojang::minecraftpe::store::Store::purchase(JNIEnv *env, jnivm::java::lang::String* arg0, jboolean arg1, jnivm::java::lang::String* arg2) {
    
}

void com::mojang::minecraftpe::store::Store::acknowledgePurchase(JNIEnv *env, jnivm::java::lang::String* arg0, jnivm::java::lang::String* arg1) {
    
}

void com::mojang::minecraftpe::store::Store::queryPurchases(JNIEnv *env) {
    
}

void com::mojang::minecraftpe::store::Store::destructor(JNIEnv *env) {
    
}

jlong com::mojang::minecraftpe::store::ExtraLicenseResponseData::getValidationTime(JNIEnv *env) {
    return 0;
}

jlong com::mojang::minecraftpe::store::ExtraLicenseResponseData::getRetryUntilTime(JNIEnv *env) {
    return 0;    
}

jlong com::mojang::minecraftpe::store::ExtraLicenseResponseData::getRetryAttempts(JNIEnv *env) {
    return 0;    
}

jint com::mojang::android::net::HTTPResponse::getStatus(JNIEnv *env) {
    return 1;
}

jnivm::java::lang::String* com::mojang::android::net::HTTPResponse::getBody(JNIEnv *env) {
    return 0;
}

jint com::mojang::android::net::HTTPResponse::getResponseCode(JNIEnv *env) {
    return 200;
}

jnivm::Array<jnivm::org::apache::http::Header*>* com::mojang::android::net::HTTPResponse::getHeaders(JNIEnv *env) {
    return 0;
}

com::mojang::android::net::HTTPRequest::HTTPRequest(JNIEnv *env) {
    
}

void com::mojang::android::net::HTTPRequest::setURL(JNIEnv *env, jnivm::java::lang::String* arg0) {
    
}

void com::mojang::android::net::HTTPRequest::setRequestBody(JNIEnv *env, jnivm::java::lang::String* arg0) {
    
}

void com::mojang::android::net::HTTPRequest::setCookieData(JNIEnv *env, jnivm::java::lang::String* arg0) {
    
}

void com::mojang::android::net::HTTPRequest::setContentType(JNIEnv *env, jnivm::java::lang::String* arg0) {
    
}

jnivm::com::mojang::android::net::HTTPResponse* com::mojang::android::net::HTTPRequest::send(JNIEnv *env, jnivm::java::lang::String* arg0) {
    return 0;
}

void com::mojang::android::net::HTTPRequest::abort(JNIEnv *env) {
    
}

jnivm::java::lang::String* com::microsoft::xbox::idp::interop::Interop::GetLocalStoragePath(JNIEnv *env, jnivm::android::content::Context* arg0) {
    return (jnivm::java::lang::String*)env->NewStringUTF("com.linux");
}

jnivm::java::lang::String* com::microsoft::xbox::idp::interop::Interop::ReadConfigFile(JNIEnv *env, jnivm::android::content::Context* arg0) {
    Log::trace("XBOXLive", "Reading xbox config file");
    std::ifstream f("xboxservices.config");
    std::stringstream s;
    s << f.rdbuf();
    return (jnivm::java::lang::String*)env->NewStringUTF(s.str().data());
}

jnivm::java::lang::String* com::microsoft::xbox::idp::interop::Interop::getSystemProxy(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("");
}

void com::microsoft::xbox::idp::interop::Interop::InitCLL(JNIEnv *env, jnivm::android::content::Context* arg0, jnivm::java::lang::String* arg1) {
    
}

void com::microsoft::xbox::idp::interop::Interop::LogTelemetrySignIn(JNIEnv *env, jnivm::java::lang::String* arg0, jnivm::java::lang::String* arg1) {
    Log::info("com::microsoft::xbox::idp::interop::Interop::LogTelemetrySignIn", "%s:%s", arg0->data(), arg1->data());    
}

void com::microsoft::xbox::idp::interop::Interop::InvokeMSA(JNIEnv *env, jnivm::android::content::Context* arg0, jint requestCode, jboolean arg2, jnivm::java::lang::String* cid) {
    auto cl = (jnivm::java::lang::Class*)env->FindClass("com/microsoft/xbox/idp/interop/Interop");
    auto appconfig = (jnivm::java::lang::Class*)env->FindClass("com/microsoft/xbox/idp/interop/XboxLiveAppConfig");
    auto id = ((jlong(*)(JNIEnv * env, void*))appconfig->natives["create"])(env, nullptr);
    auto titleid = ((jint(*)(JNIEnv * env, void*, jlong))appconfig->natives["getTitleId"])(env, nullptr, id);
    auto scid = ((jnivm::java::lang::String*(*)(JNIEnv * env, void*, jlong))appconfig->natives["getScid"])(env, nullptr, id);
    auto sandbox = ((jnivm::java::lang::String*(*)(JNIEnv * env, void*, jlong))appconfig->natives["getSandbox"])(env, nullptr, id);
    auto proxy = ((jnivm::java::lang::String*(*)(JNIEnv * env, void*, jlong))appconfig->natives["getProxy"])(env, nullptr, id);
    auto overrideTitleId = ((jint(*)(JNIEnv * env, void*, jlong))appconfig->natives["getOverrideTitleId"])(env, nullptr, id);
    auto environment = ((jnivm::java::lang::String*(*)(JNIEnv * env, void*, jlong))appconfig->natives["getEnvironment"])(env, nullptr, id);
    ((void(*)(JNIEnv * env, void*, jlong))appconfig->natives["delete"])(env, nullptr, id);
    auto ticket_callback = ((void(*)(JNIEnv *env, void*, jstring paramString1, jint paramInt1, jint paramInt2, jstring paramString2))cl->natives["ticket_callback"]);
    if (requestCode == 1) { // silent signin
        if (!cid->empty()) {
             XboxLiveHelper::getInstance().requestXblToken(*cid, true,
                    [env,ticket_callback](std::string const& cid, std::string const& token) {
                        XboxLiveHelper::getInstance().initCll(cid);
                        ticket_callback(env, nullptr, env->NewStringUTF(token.data()), 0, /* Error None */ 0, env->NewStringUTF("Got ticket"));
                    }, [env,ticket_callback](simpleipc::rpc_error_code err, std::string const& msg) {
                        Log::error("JNILIVE", "Xbox Live sign in failed: %s", msg.c_str());
                        if (err == -100) { // No such account
                            ticket_callback(env, nullptr, env->NewStringUTF(""), 0, /* Error No such account */ 1, env->NewStringUTF("Must show UI to acquire an account."));
                        } else if (err == -102) { // Must show UI
                            ticket_callback(env, nullptr, env->NewStringUTF(""), 0, /* Error Must show UI */ 1, env->NewStringUTF("Must show UI to update account information."));
                        } else {
                            ticket_callback(env, nullptr, env->NewStringUTF(""), 0, /* Error */ 0x800704CF, env->NewStringUTF(msg.c_str()));
                        }
                    });
        } else {
            ticket_callback(env, nullptr, env->NewStringUTF(""), requestCode, /* Error No such account */ 1, env->NewStringUTF("Must show UI to acquire an account."));
        }
    } else if (requestCode == 6) { // sign out
        ((void(*)(JNIEnv*, void*))cl->natives["sign_out_callback"])(env, nullptr);
    }
}

void com::microsoft::xbox::idp::interop::Interop::InvokeAuthFlow(JNIEnv *env, jlong userptr, jnivm::android::app::Activity* arg1, jboolean arg2, jnivm::java::lang::String* arg3) {
    auto cl = (std::unordered_map<std::string,void*>*)env->FindClass("com/microsoft/xbox/idp/interop/Interop");
    auto auth_flow_callback = ((void(*)(JNIEnv *env, void*, jlong paramLong, jint paramInt, jstring paramString))cl->at("auth_flow_callback"));
    auto invoke_xb_login = (void(*)(JNIEnv*, void*, jlong paramLong, jstring paramString, jobject))cl->at("invoke_xb_login");    
    XboxLiveHelper::getInstance().invokeMsaAuthFlow([env, auth_flow_callback, userptr, invoke_xb_login,cl](std::string const& cid, std::string const& token) {
        auto XBLoginCallbackcl = env->FindClass("XBLoginCallback");
        auto xblc = new XBLoginCallback();
        xblc->clazz = (jnivm::java::lang::Class*)XBLoginCallbackcl;
        xblc->userptr = userptr;
        xblc->cid = cid;
        xblc->token = token;
        xblc->cl = cl;
        xblc->auth_flow_callback = auth_flow_callback;
        invoke_xb_login(env, nullptr, userptr, env->NewStringUTF(token.data()), (jobject)xblc);
    }, [env, auth_flow_callback](simpleipc::rpc_error_code, std::string const& msg) {
        Log::trace("JNILIVE", "Sign in error: %s", msg.c_str());
        // ToDo Errorhandling
    });
}

jnivm::java::lang::String* com::microsoft::xbox::idp::interop::Interop::getLocale(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("en");
}

void com::microsoft::xbox::idp::interop::Interop::RegisterWithGNS(JNIEnv *env, jnivm::android::content::Context* arg0) {
    
}

void com::microsoft::xbox::idp::interop::Interop::LogCLL(JNIEnv *env, jnivm::java::lang::String* arg0, jnivm::java::lang::String* arg1, jnivm::java::lang::String* arg2) {
    Log::info("com::microsoft::xbox::idp::interop::Interop::LogCLL", "%s/%s:%s", arg0->data(), arg1->data(), arg2->data());
}

jint android::os::Build::VERSION::SDK_INT = 27;

jnivm::android::view::View* android::view::Window::getDecorView(JNIEnv *env) {
    auto view = new jnivm::android::view::View();
    view->clazz = (jnivm::java::lang::Class*)env->FindClass("android/view/View");
    return view;
}

jnivm::android::os::IBinder* android::view::View::getWindowToken(JNIEnv *env) {
    auto ib = new jnivm::android::os::IBinder();
    ib->clazz = (jnivm::java::lang::Class*)env->FindClass("android/os/IBinder");
    return ib;
}

jboolean android::view::inputmethod::InputMethodManager::showSoftInput(JNIEnv *env, jnivm::android::view::View* arg0, jint arg1) {
    return true;
}

jboolean android::view::inputmethod::InputMethodManager::hideSoftInputFromWindow(JNIEnv *env, jnivm::android::os::IBinder* arg0, jint arg1) {
    return true;
}

jnivm::java::lang::String* android::content::Context::INPUT_METHOD_SERVICE = {};

void android::content::Context::startActivity(JNIEnv *env, jnivm::android::content::Intent* arg0) {
    
}
jnivm::java::lang::String* android::content::Context::getPackageName(JNIEnv *env) {
    return (jnivm::java::lang::String*)env->NewStringUTF("");
}

jnivm::java::io::File* android::content::ContextWrapper::getFilesDir(JNIEnv *env) {
    return new jnivm::java::io::File { PathHelper::getPrimaryDataDirectory() };
}

jnivm::java::io::File* android::content::ContextWrapper::getCacheDir(JNIEnv *env) {
    return new jnivm::java::io::File { PathHelper::getCacheDirectory() };
}

jnivm::android::content::Context* android::app::NativeActivity::getApplicationContext(JNIEnv *env) {
    auto ctx = new jnivm::android::content::Context();
    ctx->clazz = (jnivm::java::lang::Class*)env->FindClass("android/content/Context");
    return ctx;
}

jnivm::java::lang::Class* java::lang::ClassLoader::loadClass(JNIEnv *env, jnivm::java::lang::String* arg0) {
    return (jnivm::java::lang::Class*)env->FindClass(arg0->data());
}

jnivm::java::lang::String* java::io::File::getPath(JNIEnv *env) {
    return this;
}

extern "C" void XBLoginCallback_onLogin(JNIEnv *env, jnivm::XBLoginCallback* obj, jvalue* values) {
    return obj->onLogin(env, (jlong&)values[0], (jboolean&)values[1]);
}

extern "C" void XBLoginCallback_onSuccess(JNIEnv *env, jnivm::XBLoginCallback* obj, jvalue* values) {
    return obj->onSuccess(env);
}

extern "C" void XBLoginCallback_onError(JNIEnv *env, jnivm::XBLoginCallback* obj, jvalue* values) {
    return obj->onError(env, (jint&)values[0], (jint&)values[1], (jnivm::java::lang::String*&)values[2]);
}

extern "C" void com_mojang_minecraftpe_MainActivity_saveScreenshot(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::MainActivity::saveScreenshot(env, (jnivm::java::lang::String*&)values[0], (jint&)values[1], (jint&)values[2], (jnivm::Array<jint>*&)values[3]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_postScreenshotToFacebook(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->postScreenshotToFacebook(env, (jnivm::java::lang::String*&)values[0], (jint&)values[1], (jint&)values[2], (jnivm::Array<jint>*&)values[3]);
}
extern "C" jnivm::Array<jint>* com_mojang_minecraftpe_MainActivity_getImageData(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getImageData(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" jnivm::Array<jbyte>* com_mojang_minecraftpe_MainActivity_getFileDataBytes(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getFileDataBytes(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_displayDialog(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->displayDialog(env, (jint&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_tick(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->tick(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_quit(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->quit(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_initiateUserInput(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->initiateUserInput(env, (jint&)values[0]);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getUserInputStatus(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getUserInputStatus(env);
}
extern "C" jnivm::Array<jnivm::java::lang::String*>* com_mojang_minecraftpe_MainActivity_getUserInputString(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getUserInputString(env);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_checkLicense(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->checkLicense(env);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_hasBuyButtonWhenInvalidLicense(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->hasBuyButtonWhenInvalidLicense(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_buyGame(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->buyGame(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_vibrate(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->vibrate(env, (jint&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setIsPowerVR(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->setIsPowerVR(env, (jboolean&)values[0]);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_isNetworkEnabled(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->isNetworkEnabled(env, (jboolean&)values[0]);
}
extern "C" jfloat com_mojang_minecraftpe_MainActivity_getPixelsPerMillimeter(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getPixelsPerMillimeter(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_MainActivity_getPlatformStringVar(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getPlatformStringVar(env, (jint&)values[0]);
}
extern "C" jnivm::java::lang::Object* com_mojang_minecraftpe_MainActivity_getSystemService(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getSystemService(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" jnivm::android::view::Window* com_mojang_minecraftpe_MainActivity_getWindow(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getWindow(env);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getKeyFromKeyCode(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getKeyFromKeyCode(env, (jint&)values[0], (jint&)values[1], (jint&)values[2]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_updateLocalization(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->updateLocalization(env, (jnivm::java::lang::String*&)values[0], (jnivm::java::lang::String*&)values[1]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_showKeyboard(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->showKeyboard(env, (jnivm::java::lang::String*&)values[0], (jint&)values[1], (jboolean&)values[2], (jboolean&)values[3], (jboolean&)values[4]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_hideKeyboard(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->hideKeyboard(env);
}
extern "C" jfloat com_mojang_minecraftpe_MainActivity_getKeyboardHeight(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getKeyboardHeight(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_updateTextboxText(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->updateTextboxText(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getCursorPosition(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getCursorPosition(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_MainActivity_getAccessToken(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getAccessToken(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_MainActivity_getClientId(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getClientId(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_MainActivity_getProfileId(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getProfileId(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_MainActivity_getProfileName(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getProfileName(env);
}
extern "C" jnivm::Array<jnivm::java::lang::String*>* com_mojang_minecraftpe_MainActivity_getBroadcastAddresses(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getBroadcastAddresses(env);
}
extern "C" jnivm::Array<jnivm::java::lang::String*>* com_mojang_minecraftpe_MainActivity_getIPAddresses(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getIPAddresses(env);
}
extern "C" jlong com_mojang_minecraftpe_MainActivity_getTotalMemory(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getTotalMemory(env);
}
extern "C" jlong com_mojang_minecraftpe_MainActivity_getMemoryLimit(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getMemoryLimit(env);
}
extern "C" jlong com_mojang_minecraftpe_MainActivity_getUsedMemory(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getUsedMemory(env);
}
extern "C" jlong com_mojang_minecraftpe_MainActivity_getFreeMemory(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getFreeMemory(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_launchUri(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->launchUri(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setClipboard(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->setClipboard(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_share(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->share(env, (jnivm::java::lang::String*&)values[0], (jnivm::java::lang::String*&)values[1], (jnivm::java::lang::String*&)values[2]);
}
extern "C" jnivm::android::content::Intent* com_mojang_minecraftpe_MainActivity_createAndroidLaunchIntent(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->createAndroidLaunchIntent(env);
}
extern "C" jlong com_mojang_minecraftpe_MainActivity_calculateAvailableDiskFreeSpace(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->calculateAvailableDiskFreeSpace(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_MainActivity_getExternalStoragePath(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getExternalStoragePath(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_requestStoragePermission(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->requestStoragePermission(env, (jint&)values[0]);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_hasWriteExternalStoragePermission(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->hasWriteExternalStoragePermission(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_deviceIdCorrelationStart(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->deviceIdCorrelationStart(env);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_isMixerCreateInstalled(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->isMixerCreateInstalled(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_navigateToPlaystoreForMixerCreate(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->navigateToPlaystoreForMixerCreate(env);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_launchMixerCreateForBroadcast(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->launchMixerCreateForBroadcast(env);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_isTTSEnabled(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->isTTSEnabled(env);
}
extern "C" jnivm::com::mojang::minecraftpe::HardwareInformation* com_mojang_minecraftpe_MainActivity_getHardwareInfo(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getHardwareInfo(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setCachedDeviceId(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->setCachedDeviceId(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setLastDeviceSessionId(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->setLastDeviceSessionId(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_MainActivity_getLastDeviceSessionId(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getLastDeviceSessionId(env);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getAPIVersion(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getAPIVersion(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_MainActivity_getSecureStorageKey(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getSecureStorageKey(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setSecureStorageKey(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->setSecureStorageKey(env, (jnivm::java::lang::String*&)values[0], (jnivm::java::lang::String*&)values[1]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_trackPurchaseEvent(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->trackPurchaseEvent(env, (jnivm::java::lang::String*&)values[0], (jnivm::java::lang::String*&)values[1], (jnivm::java::lang::String*&)values[2], (jnivm::java::lang::String*&)values[3], (jnivm::java::lang::String*&)values[4], (jnivm::java::lang::String*&)values[5], (jnivm::java::lang::String*&)values[6], (jnivm::java::lang::String*&)values[7]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeEvent(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->sendBrazeEvent(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeEventWithProperty(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->sendBrazeEventWithProperty(env, (jnivm::java::lang::String*&)values[0], (jnivm::java::lang::String*&)values[1], (jint&)values[2]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeEventWithStringProperty(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->sendBrazeEventWithStringProperty(env, (jnivm::java::lang::String*&)values[0], (jnivm::java::lang::String*&)values[1], (jnivm::java::lang::String*&)values[2]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeToastClick(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->sendBrazeToastClick(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_sendBrazeDialogButtonClick(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->sendBrazeDialogButtonClick(env, (jint&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_pickImage(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->pickImage(env, (jlong&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setFileDialogCallback(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->setFileDialogCallback(env, (jlong&)values[0]);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_MainActivity_getLegacyDeviceID(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getLegacyDeviceID(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_MainActivity_createUUID(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->createUUID(env);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_hasHardwareKeyboard(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->hasHardwareKeyboard(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_startTextToSpeech(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->startTextToSpeech(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_MainActivity_stopTextToSpeech(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->stopTextToSpeech(env);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_isTextToSpeechInProgress(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->isTextToSpeechInProgress(env);
}
extern "C" void com_mojang_minecraftpe_MainActivity_setTextToSpeechEnabled(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->setTextToSpeechEnabled(env, (jboolean&)values[0]);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getScreenWidth(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getScreenWidth(env);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getScreenHeight(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getScreenHeight(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_MainActivity_getDeviceModel(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getDeviceModel(env);
}
extern "C" jint com_mojang_minecraftpe_MainActivity_getAndroidVersion(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getAndroidVersion(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_MainActivity_getLocale(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getLocale(env);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_isFirstSnooperStart(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->isFirstSnooperStart(env);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_hasHardwareChanged(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->hasHardwareChanged(env);
}
extern "C" jboolean com_mojang_minecraftpe_MainActivity_isTablet(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->isTablet(env);
}
extern "C" jnivm::java::lang::ClassLoader* com_mojang_minecraftpe_MainActivity_getClassLoader(JNIEnv *env, jnivm::com::mojang::minecraftpe::MainActivity* obj, jvalue* values) {
    return obj->getClassLoader(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_HardwareInformation_getDeviceModelName(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getDeviceModelName(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_HardwareInformation_getAndroidVersion(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getAndroidVersion(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_HardwareInformation_getCPUType(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getCPUType(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_HardwareInformation_getCPUName(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getCPUName(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_HardwareInformation_getCPUFeatures(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getCPUFeatures(env);
}
extern "C" jint com_mojang_minecraftpe_HardwareInformation_getNumCores(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getNumCores(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_HardwareInformation_getSecureId(JNIEnv *env, jnivm::com::mojang::minecraftpe::HardwareInformation* obj, jvalue* values) {
    return obj->getSecureId(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_HardwareInformation_getSerialNumber(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getSerialNumber(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_HardwareInformation_getBoard(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getBoard(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_HardwareInformation_getInstallerPackageName(JNIEnv *env, jnivm::com::mojang::minecraftpe::HardwareInformation* obj, jvalue* values) {
    return obj->getInstallerPackageName(env);
}
extern "C" jint com_mojang_minecraftpe_HardwareInformation_getSignaturesHashCode(JNIEnv *env, jnivm::com::mojang::minecraftpe::HardwareInformation* obj, jvalue* values) {
    return obj->getSignaturesHashCode(env);
}
extern "C" jboolean com_mojang_minecraftpe_HardwareInformation_getIsRooted(JNIEnv *env, jnivm::com::mojang::minecraftpe::HardwareInformation* obj, jvalue* values) {
    return obj->getIsRooted(env);
}
extern "C" void com_mojang_minecraftpe_store_NativeStoreListener_NativeStoreListener(JNIEnv *env, jnivm::com::mojang::minecraftpe::store::NativeStoreListener* obj, jvalue* values) {
    new obj com::mojang::minecraftpe::store::NativeStoreListener(env, (jlong&)values[0]);
}
extern "C" jnivm::java::lang::String* get_com_mojang_minecraftpe_store_Product_mId(jnivm::com::mojang::minecraftpe::store::Product* obj) {
    return obj->mId;
}

extern "C" void set_com_mojang_minecraftpe_store_Product_mId(jnivm::com::mojang::minecraftpe::store::Product* obj, jnivm::java::lang::String* value) {
    obj->mId = value;
}

extern "C" jnivm::java::lang::String* get_com_mojang_minecraftpe_store_Product_mPrice(jnivm::com::mojang::minecraftpe::store::Product* obj) {
    return obj->mPrice;
}

extern "C" void set_com_mojang_minecraftpe_store_Product_mPrice(jnivm::com::mojang::minecraftpe::store::Product* obj, jnivm::java::lang::String* value) {
    obj->mPrice = value;
}

extern "C" jnivm::java::lang::String* get_com_mojang_minecraftpe_store_Product_mCurrencyCode(jnivm::com::mojang::minecraftpe::store::Product* obj) {
    return obj->mCurrencyCode;
}

extern "C" void set_com_mojang_minecraftpe_store_Product_mCurrencyCode(jnivm::com::mojang::minecraftpe::store::Product* obj, jnivm::java::lang::String* value) {
    obj->mCurrencyCode = value;
}

extern "C" jnivm::java::lang::String* get_com_mojang_minecraftpe_store_Product_mUnformattedPrice(jnivm::com::mojang::minecraftpe::store::Product* obj) {
    return obj->mUnformattedPrice;
}

extern "C" void set_com_mojang_minecraftpe_store_Product_mUnformattedPrice(jnivm::com::mojang::minecraftpe::store::Product* obj, jnivm::java::lang::String* value) {
    obj->mUnformattedPrice = value;
}

extern "C" jnivm::java::lang::String* get_com_mojang_minecraftpe_store_Purchase_mProductId(jnivm::com::mojang::minecraftpe::store::Purchase* obj) {
    return obj->mProductId;
}

extern "C" void set_com_mojang_minecraftpe_store_Purchase_mProductId(jnivm::com::mojang::minecraftpe::store::Purchase* obj, jnivm::java::lang::String* value) {
    obj->mProductId = value;
}

extern "C" jnivm::java::lang::String* get_com_mojang_minecraftpe_store_Purchase_mReceipt(jnivm::com::mojang::minecraftpe::store::Purchase* obj) {
    return obj->mReceipt;
}

extern "C" void set_com_mojang_minecraftpe_store_Purchase_mReceipt(jnivm::com::mojang::minecraftpe::store::Purchase* obj, jnivm::java::lang::String* value) {
    obj->mReceipt = value;
}

extern "C" jboolean get_com_mojang_minecraftpe_store_Purchase_mPurchaseActive(jnivm::com::mojang::minecraftpe::store::Purchase* obj) {
    return obj->mPurchaseActive;
}

extern "C" void set_com_mojang_minecraftpe_store_Purchase_mPurchaseActive(jnivm::com::mojang::minecraftpe::store::Purchase* obj, jboolean value) {
    obj->mPurchaseActive = value;
}

extern "C" jnivm::com::mojang::minecraftpe::store::Store* com_mojang_minecraftpe_store_StoreFactory_createGooglePlayStore(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::store::StoreFactory::createGooglePlayStore(env, (jnivm::java::lang::String*&)values[0], (jnivm::com::mojang::minecraftpe::store::StoreListener*&)values[1]);
}
extern "C" jnivm::com::mojang::minecraftpe::store::Store* com_mojang_minecraftpe_store_StoreFactory_createAmazonAppStore(JNIEnv *env, jvalue* values) {
    return com::mojang::minecraftpe::store::StoreFactory::createAmazonAppStore(env, (jnivm::com::mojang::minecraftpe::store::StoreListener*&)values[0], (jboolean&)values[1]);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_store_Store_getStoreId(JNIEnv *env, jnivm::com::mojang::minecraftpe::store::Store* obj, jvalue* values) {
    return obj->getStoreId(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_store_Store_getProductSkuPrefix(JNIEnv *env, jnivm::com::mojang::minecraftpe::store::Store* obj, jvalue* values) {
    return obj->getProductSkuPrefix(env);
}
extern "C" jnivm::java::lang::String* com_mojang_minecraftpe_store_Store_getRealmsSkuPrefix(JNIEnv *env, jnivm::com::mojang::minecraftpe::store::Store* obj, jvalue* values) {
    return obj->getRealmsSkuPrefix(env);
}
extern "C" jboolean com_mojang_minecraftpe_store_Store_hasVerifiedLicense(JNIEnv *env, jnivm::com::mojang::minecraftpe::store::Store* obj, jvalue* values) {
    return obj->hasVerifiedLicense(env);
}
extern "C" jnivm::com::mojang::minecraftpe::store::ExtraLicenseResponseData* com_mojang_minecraftpe_store_Store_getExtraLicenseData(JNIEnv *env, jnivm::com::mojang::minecraftpe::store::Store* obj, jvalue* values) {
    return obj->getExtraLicenseData(env);
}
extern "C" jboolean com_mojang_minecraftpe_store_Store_receivedLicenseResponse(JNIEnv *env, jnivm::com::mojang::minecraftpe::store::Store* obj, jvalue* values) {
    return obj->receivedLicenseResponse(env);
}
extern "C" void com_mojang_minecraftpe_store_Store_queryProducts(JNIEnv *env, jnivm::com::mojang::minecraftpe::store::Store* obj, jvalue* values) {
    return obj->queryProducts(env, (jnivm::Array<jnivm::java::lang::String*>*&)values[0]);
}
extern "C" void com_mojang_minecraftpe_store_Store_purchase(JNIEnv *env, jnivm::com::mojang::minecraftpe::store::Store* obj, jvalue* values) {
    return obj->purchase(env, (jnivm::java::lang::String*&)values[0], (jboolean&)values[1], (jnivm::java::lang::String*&)values[2]);
}
extern "C" void com_mojang_minecraftpe_store_Store_acknowledgePurchase(JNIEnv *env, jnivm::com::mojang::minecraftpe::store::Store* obj, jvalue* values) {
    return obj->acknowledgePurchase(env, (jnivm::java::lang::String*&)values[0], (jnivm::java::lang::String*&)values[1]);
}
extern "C" void com_mojang_minecraftpe_store_Store_queryPurchases(JNIEnv *env, jnivm::com::mojang::minecraftpe::store::Store* obj, jvalue* values) {
    return obj->queryPurchases(env);
}
extern "C" void com_mojang_minecraftpe_store_Store_destructor(JNIEnv *env, jnivm::com::mojang::minecraftpe::store::Store* obj, jvalue* values) {
    return obj->destructor(env);
}
extern "C" jlong com_mojang_minecraftpe_store_ExtraLicenseResponseData_getValidationTime(JNIEnv *env, jnivm::com::mojang::minecraftpe::store::ExtraLicenseResponseData* obj, jvalue* values) {
    return obj->getValidationTime(env);
}
extern "C" jlong com_mojang_minecraftpe_store_ExtraLicenseResponseData_getRetryUntilTime(JNIEnv *env, jnivm::com::mojang::minecraftpe::store::ExtraLicenseResponseData* obj, jvalue* values) {
    return obj->getRetryUntilTime(env);
}
extern "C" jlong com_mojang_minecraftpe_store_ExtraLicenseResponseData_getRetryAttempts(JNIEnv *env, jnivm::com::mojang::minecraftpe::store::ExtraLicenseResponseData* obj, jvalue* values) {
    return obj->getRetryAttempts(env);
}
extern "C" jint com_mojang_android_net_HTTPResponse_getStatus(JNIEnv *env, jnivm::com::mojang::android::net::HTTPResponse* obj, jvalue* values) {
    return obj->getStatus(env);
}
extern "C" jnivm::java::lang::String* com_mojang_android_net_HTTPResponse_getBody(JNIEnv *env, jnivm::com::mojang::android::net::HTTPResponse* obj, jvalue* values) {
    return obj->getBody(env);
}
extern "C" jint com_mojang_android_net_HTTPResponse_getResponseCode(JNIEnv *env, jnivm::com::mojang::android::net::HTTPResponse* obj, jvalue* values) {
    return obj->getResponseCode(env);
}
extern "C" jnivm::Array<jnivm::org::apache::http::Header*>* com_mojang_android_net_HTTPResponse_getHeaders(JNIEnv *env, jnivm::com::mojang::android::net::HTTPResponse* obj, jvalue* values) {
    return obj->getHeaders(env);
}
extern "C" void com_mojang_android_net_HTTPRequest_HTTPRequest(JNIEnv *env, jnivm::com::mojang::android::net::HTTPRequest* obj, jvalue* values) {
    new obj com::mojang::android::net::HTTPRequest(env);
}
extern "C" void com_mojang_android_net_HTTPRequest_setURL(JNIEnv *env, jnivm::com::mojang::android::net::HTTPRequest* obj, jvalue* values) {
    return obj->setURL(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" void com_mojang_android_net_HTTPRequest_setRequestBody(JNIEnv *env, jnivm::com::mojang::android::net::HTTPRequest* obj, jvalue* values) {
    return obj->setRequestBody(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" void com_mojang_android_net_HTTPRequest_setCookieData(JNIEnv *env, jnivm::com::mojang::android::net::HTTPRequest* obj, jvalue* values) {
    return obj->setCookieData(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" void com_mojang_android_net_HTTPRequest_setContentType(JNIEnv *env, jnivm::com::mojang::android::net::HTTPRequest* obj, jvalue* values) {
    return obj->setContentType(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" jnivm::com::mojang::android::net::HTTPResponse* com_mojang_android_net_HTTPRequest_send(JNIEnv *env, jnivm::com::mojang::android::net::HTTPRequest* obj, jvalue* values) {
    return obj->send(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" void com_mojang_android_net_HTTPRequest_abort(JNIEnv *env, jnivm::com::mojang::android::net::HTTPRequest* obj, jvalue* values) {
    return obj->abort(env);
}
extern "C" jnivm::java::lang::String* com_microsoft_xbox_idp_interop_Interop_GetLocalStoragePath(JNIEnv *env, jvalue* values) {
    return com::microsoft::xbox::idp::interop::Interop::GetLocalStoragePath(env, (jnivm::android::content::Context*&)values[0]);
}
extern "C" jnivm::java::lang::String* com_microsoft_xbox_idp_interop_Interop_ReadConfigFile(JNIEnv *env, jvalue* values) {
    return com::microsoft::xbox::idp::interop::Interop::ReadConfigFile(env, (jnivm::android::content::Context*&)values[0]);
}
extern "C" jnivm::java::lang::String* com_microsoft_xbox_idp_interop_Interop_getSystemProxy(JNIEnv *env, jvalue* values) {
    return com::microsoft::xbox::idp::interop::Interop::getSystemProxy(env);
}
extern "C" void com_microsoft_xbox_idp_interop_Interop_InitCLL(JNIEnv *env, jvalue* values) {
    return com::microsoft::xbox::idp::interop::Interop::InitCLL(env, (jnivm::android::content::Context*&)values[0], (jnivm::java::lang::String*&)values[1]);
}
extern "C" void com_microsoft_xbox_idp_interop_Interop_LogTelemetrySignIn(JNIEnv *env, jvalue* values) {
    return com::microsoft::xbox::idp::interop::Interop::LogTelemetrySignIn(env, (jnivm::java::lang::String*&)values[0], (jnivm::java::lang::String*&)values[1]);
}
extern "C" void com_microsoft_xbox_idp_interop_Interop_InvokeMSA(JNIEnv *env, jvalue* values) {
    return com::microsoft::xbox::idp::interop::Interop::InvokeMSA(env, (jnivm::android::content::Context*&)values[0], (jint&)values[1], (jboolean&)values[2], (jnivm::java::lang::String*&)values[3]);
}
extern "C" void com_microsoft_xbox_idp_interop_Interop_InvokeAuthFlow(JNIEnv *env, jvalue* values) {
    return com::microsoft::xbox::idp::interop::Interop::InvokeAuthFlow(env, (jlong&)values[0], (jnivm::android::app::Activity*&)values[1], (jboolean&)values[2], (jnivm::java::lang::String*&)values[3]);
}
extern "C" jnivm::java::lang::String* com_microsoft_xbox_idp_interop_Interop_getLocale(JNIEnv *env, jvalue* values) {
    return com::microsoft::xbox::idp::interop::Interop::getLocale(env);
}
extern "C" void com_microsoft_xbox_idp_interop_Interop_RegisterWithGNS(JNIEnv *env, jvalue* values) {
    return com::microsoft::xbox::idp::interop::Interop::RegisterWithGNS(env, (jnivm::android::content::Context*&)values[0]);
}
extern "C" void com_microsoft_xbox_idp_interop_Interop_LogCLL(JNIEnv *env, jvalue* values) {
    return com::microsoft::xbox::idp::interop::Interop::LogCLL(env, (jnivm::java::lang::String*&)values[0], (jnivm::java::lang::String*&)values[1], (jnivm::java::lang::String*&)values[2]);
}
extern "C" jint get_android_os_Build_VERSION_SDK_INT() {
    return android::os::Build::VERSION::SDK_INT;
}

extern "C" void set_android_os_Build_VERSION_SDK_INT(jint value) {
    android::os::Build::VERSION::SDK_INT = value;
}

extern "C" jnivm::android::view::View* android_view_Window_getDecorView(JNIEnv *env, jnivm::android::view::Window* obj, jvalue* values) {
    return obj->getDecorView(env);
}
extern "C" jnivm::android::os::IBinder* android_view_View_getWindowToken(JNIEnv *env, jnivm::android::view::View* obj, jvalue* values) {
    return obj->getWindowToken(env);
}
extern "C" jboolean android_view_inputmethod_InputMethodManager_showSoftInput(JNIEnv *env, jnivm::android::view::inputmethod::InputMethodManager* obj, jvalue* values) {
    return obj->showSoftInput(env, (jnivm::android::view::View*&)values[0], (jint&)values[1]);
}
extern "C" jboolean android_view_inputmethod_InputMethodManager_hideSoftInputFromWindow(JNIEnv *env, jnivm::android::view::inputmethod::InputMethodManager* obj, jvalue* values) {
    return obj->hideSoftInputFromWindow(env, (jnivm::android::os::IBinder*&)values[0], (jint&)values[1]);
}
extern "C" jnivm::java::lang::String* get_android_content_Context_INPUT_METHOD_SERVICE() {
    return android::content::Context::INPUT_METHOD_SERVICE;
}

extern "C" void set_android_content_Context_INPUT_METHOD_SERVICE(jnivm::java::lang::String* value) {
    android::content::Context::INPUT_METHOD_SERVICE = value;
}

extern "C" void android_content_Context_startActivity(JNIEnv *env, jnivm::android::content::Context* obj, jvalue* values) {
    return obj->startActivity(env, (jnivm::android::content::Intent*&)values[0]);
}
extern "C" jnivm::java::lang::String* android_content_Context_getPackageName(JNIEnv *env, jnivm::android::content::Context* obj, jvalue* values) {
    return obj->getPackageName(env);
}
extern "C" jnivm::java::io::File* android_content_ContextWrapper_getFilesDir(JNIEnv *env, jnivm::android::content::ContextWrapper* obj, jvalue* values) {
    return obj->getFilesDir(env);
}
extern "C" jnivm::java::io::File* android_content_ContextWrapper_getCacheDir(JNIEnv *env, jnivm::android::content::ContextWrapper* obj, jvalue* values) {
    return obj->getCacheDir(env);
}
extern "C" jnivm::android::content::Context* android_app_NativeActivity_getApplicationContext(JNIEnv *env, jnivm::android::app::NativeActivity* obj, jvalue* values) {
    return obj->getApplicationContext(env);
}
extern "C" jnivm::java::lang::Class* java_lang_ClassLoader_loadClass(JNIEnv *env, jnivm::java::lang::ClassLoader* obj, jvalue* values) {
    return obj->loadClass(env, (jnivm::java::lang::String*&)values[0]);
}
extern "C" jnivm::java::lang::String* java_io_File_getPath(JNIEnv *env, jnivm::java::io::File* obj, jvalue* values) {
    return obj->getPath(env);
}