#pragma once

#include <jni.h>
#include <jnivm.h>
#include <tuple>
#include <vector>
#include <fstream>
#include <mcpelauncher/path_helper.h>
#include <sstream>
#include "xbox_live_game_interface.h"
#include "xbox_live_helper.h"
#include <file_picker_factory.h>
// #include <hybris/dlfcn.h>
#include <mcpelauncher/path_helper.h>
#include <game_window.h>

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
        class ClassLoader;
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
    std::shared_ptr<jnivm::java::lang::Class> cl;
    void(*auth_flow_callback)(JNIEnv *env, void*, jlong paramLong, jint paramInt, jstring paramString);
    void onLogin(ENV *, jlong, jboolean);
    void onError(ENV *, jint, jint, std::shared_ptr<jnivm::java::lang::String>);
    void onSuccess(ENV *);
};
class com::mojang::minecraftpe::MainActivity : public jnivm::java::lang::Object {
    bool currentTextMutliline = false;
    std::string currentText;
    size_t currentTextPosition = 0;
    size_t currentTextPositionUTF = 0;
    size_t currentTextCopyPosition = 0;
    bool isShiftPressed = false;
    int iskeyboardvisible = 0;
    size_t maxcurrentTextLength = 0;
    void(*nativeOnPickImageSuccess)(JNIEnv*, void*, jlong var1, jstring var3);
    void(*nativeOnPickImageCanceled)(JNIEnv*, void*, jlong var1);
    void(*nativeSetTextboxText)(JNIEnv*,void*, jstring);
    unsigned char* (*stbi_load_from_memory)(unsigned char const *buffer, int len, int *x, int *y, int *channels_in_file, int desired_channels);
    void (*stbi_image_free)(void *retval_from_stbi_load);
    void (*nativeWebRequestCompleted)(JNIEnv*,void*, jint paramInt1, jlong paramLong, jint paramInt2, jstring paramString);
    void (*nativeInitializeXboxLive)(JNIEnv*,void*, jlong a, jlong b);
    int (*XalInitialize)(void*, void*);
    int (*XblInitialize)(void*);

public:
    MainActivity(void * handle);
    std::shared_ptr<GameWindow> window;
    enum DirectionKey {
        LeftKey, RightKey, HomeKey, EndKey
    };
    void onKeyboardText(ENV *,std::string const &text);
    void onKeyboardDirectionKey(DirectionKey key);
    void onKeyboardShiftKey(bool shiftPressed);
    void copyCurrentText();
    bool isKeyboardMultiline() const { return currentTextMutliline; }
    bool isKeyboardVisible() const { return iskeyboardvisible; }
    
    static void saveScreenshot(ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::java::lang::String>, jint, jint, std::shared_ptr<jnivm::Array<jint>>);
    void postScreenshotToFacebook(ENV *, std::shared_ptr<jnivm::java::lang::String>, jint, jint, std::shared_ptr<jnivm::Array<jint>>);
    std::shared_ptr<jnivm::Array<jint>> getImageData(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    std::shared_ptr<jnivm::Array<jbyte>> getFileDataBytes(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void displayDialog(ENV *, jint);
    void tick(ENV *);
    void quit(ENV *);
    void initiateUserInput(ENV *, jint);
    jint getUserInputStatus(ENV *);
    std::shared_ptr<jnivm::Array<jnivm::java::lang::String>> getUserInputString(ENV *);
    jint checkLicense(ENV *);
    jboolean hasBuyButtonWhenInvalidLicense(ENV *);
    void buyGame(ENV *);
    void vibrate(ENV *, jint);
    void setIsPowerVR(ENV *, jboolean);
    jboolean isNetworkEnabled(ENV *, jboolean);
    jfloat getPixelsPerMillimeter(ENV *);
    std::shared_ptr<jnivm::java::lang::String> getPlatformStringVar(ENV *, jint);
    std::shared_ptr<jnivm::java::lang::Object> getSystemService(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    std::shared_ptr<jnivm::android::view::Window> getWindow(ENV *);
    jint getKeyFromKeyCode(ENV *, jint, jint, jint);
    void updateLocalization(ENV *, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
    void showKeyboard(ENV *, std::shared_ptr<jnivm::java::lang::String>, jint, jboolean, jboolean, jboolean);
    void hideKeyboard(ENV *);
    jfloat getKeyboardHeight(ENV *);
    void updateTextboxText(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    jint getCursorPosition(ENV *);
    std::shared_ptr<jnivm::java::lang::String> getAccessToken(ENV *);
    std::shared_ptr<jnivm::java::lang::String> getClientId(ENV *);
    std::shared_ptr<jnivm::java::lang::String> getProfileId(ENV *);
    std::shared_ptr<jnivm::java::lang::String> getProfileName(ENV *);
    std::shared_ptr<jnivm::Array<jnivm::java::lang::String>> getBroadcastAddresses(ENV *);
    std::shared_ptr<jnivm::Array<jnivm::java::lang::String>> getIPAddresses(ENV *);
    jlong getTotalMemory(ENV *);
    jlong getMemoryLimit(ENV *);
    jlong getUsedMemory(ENV *);
    jlong getFreeMemory(ENV *);
    void launchUri(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void setClipboard(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void share(ENV *, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
    std::shared_ptr<jnivm::android::content::Intent> createAndroidLaunchIntent(ENV *);
    jlong calculateAvailableDiskFreeSpace(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    std::shared_ptr<jnivm::java::lang::String> getExternalStoragePath(ENV *);
    void requestStoragePermission(ENV *, jint);
    jboolean hasWriteExternalStoragePermission(ENV *);
    void deviceIdCorrelationStart(ENV *);
    jboolean isMixerCreateInstalled(ENV *);
    void navigateToPlaystoreForMixerCreate(ENV *);
    jboolean launchMixerCreateForBroadcast(ENV *);
    jboolean isTTSEnabled(ENV *);
    std::shared_ptr<jnivm::com::mojang::minecraftpe::HardwareInformation> getHardwareInfo(ENV *);
    void setCachedDeviceId(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void setLastDeviceSessionId(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    std::shared_ptr<jnivm::java::lang::String> getLastDeviceSessionId(ENV *);
    jint getAPIVersion(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    std::shared_ptr<jnivm::java::lang::String> getSecureStorageKey(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void setSecureStorageKey(ENV *, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
    void trackPurchaseEvent(ENV *, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
    void sendBrazeEvent(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void sendBrazeEventWithProperty(ENV *, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, jint);
    void sendBrazeEventWithStringProperty(ENV *, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
    void sendBrazeToastClick(ENV *);
    void sendBrazeDialogButtonClick(ENV *, jint);
    void pickImage(ENV *, jlong);
    void setFileDialogCallback(ENV *, jlong);
    std::shared_ptr<jnivm::java::lang::String> getLegacyDeviceID(ENV *);
    std::shared_ptr<jnivm::java::lang::String> createUUID(ENV *);
    jboolean hasHardwareKeyboard(ENV *);
    void startTextToSpeech(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void stopTextToSpeech(ENV *);
    jboolean isTextToSpeechInProgress(ENV *);
    void setTextToSpeechEnabled(ENV *, jboolean);
    jint getScreenWidth(ENV *);
    jint getScreenHeight(ENV *);
    std::shared_ptr<jnivm::java::lang::String> getDeviceModel(ENV *);
    jint getAndroidVersion(ENV *);
    std::shared_ptr<jnivm::java::lang::String> getLocale(ENV *);
    jboolean isFirstSnooperStart(ENV *);
    jboolean hasHardwareChanged(ENV *);
    jboolean isTablet(ENV *);
    std::shared_ptr<jnivm::java::lang::ClassLoader> getClassLoader(ENV *);
    void webRequest(ENV * env, jint paramInt, jlong paramLong, std::shared_ptr<jnivm::java::lang::String> paramString1, std::shared_ptr<jnivm::java::lang::String> paramString2, std::shared_ptr<jnivm::java::lang::String> paramString3, std::shared_ptr<jnivm::java::lang::String> paramString4) {
        // std::thread([=]() {
        //     std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        //     nativeWebRequestCompleted(env, clazz, paramInt, paramLong, 2, env->NewStringUTF(""));
        // }).detach();
    }
    void initializeXboxLive(ENV * env, jlong a, jlong b);
};
class com::mojang::minecraftpe::HardwareInformation : public jnivm::java::lang::Object {
public:
    static std::shared_ptr<jnivm::java::lang::String> getDeviceModelName(ENV *, jnivm::java::lang::Class*);
    static std::shared_ptr<jnivm::java::lang::String> getAndroidVersion(ENV *, jnivm::java::lang::Class*);
    static std::shared_ptr<jnivm::java::lang::String> getCPUType(ENV *, jnivm::java::lang::Class*);
    static std::shared_ptr<jnivm::java::lang::String> getCPUName(ENV *, jnivm::java::lang::Class*);
    static std::shared_ptr<jnivm::java::lang::String> getCPUFeatures(ENV *, jnivm::java::lang::Class*);
    static jint getNumCores(ENV *, jnivm::java::lang::Class*);
    std::shared_ptr<jnivm::java::lang::String> getSecureId(ENV *);
    static std::shared_ptr<jnivm::java::lang::String> getSerialNumber(ENV *, jnivm::java::lang::Class*);
    static std::shared_ptr<jnivm::java::lang::String> getBoard(ENV *, jnivm::java::lang::Class*);
    std::shared_ptr<jnivm::java::lang::String> getInstallerPackageName(ENV *);
    jint getSignaturesHashCode(ENV *);
    jboolean getIsRooted(ENV *);
};
class com::mojang::minecraftpe::store::NativeStoreListener : public jnivm::java::lang::Object {
public:
jlong nativestore = 0;
    NativeStoreListener(ENV *, jnivm::java::lang::Class*, jlong);
};
class com::mojang::minecraftpe::store::Product : public jnivm::java::lang::Object {
public:
    std::shared_ptr<jnivm::java::lang::String> mId;
    std::shared_ptr<jnivm::java::lang::String> mPrice;
    std::shared_ptr<jnivm::java::lang::String> mCurrencyCode;
    std::shared_ptr<jnivm::java::lang::String> mUnformattedPrice;
};
class com::mojang::minecraftpe::store::Purchase : public jnivm::java::lang::Object {
public:
    std::shared_ptr<jnivm::java::lang::String> mProductId;
    std::shared_ptr<jnivm::java::lang::String> mReceipt;
    jboolean mPurchaseActive;
};
class com::mojang::minecraftpe::store::StoreFactory : public jnivm::java::lang::Object {
public:
    static std::shared_ptr<jnivm::com::mojang::minecraftpe::store::Store> createGooglePlayStore(ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::com::mojang::minecraftpe::store::StoreListener>);
    static std::shared_ptr<jnivm::com::mojang::minecraftpe::store::Store> createAmazonAppStore(ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::com::mojang::minecraftpe::store::StoreListener>, jboolean);
};
class com::mojang::minecraftpe::store::StoreListener : public jnivm::java::lang::Object {
public:
};
class com::mojang::minecraftpe::store::Store : public jnivm::java::lang::Object {
public:
    std::shared_ptr<jnivm::java::lang::String> getStoreId(ENV *);
    std::shared_ptr<jnivm::java::lang::String> getProductSkuPrefix(ENV *);
    std::shared_ptr<jnivm::java::lang::String> getRealmsSkuPrefix(ENV *);
    jboolean hasVerifiedLicense(ENV *);
    std::shared_ptr<jnivm::com::mojang::minecraftpe::store::ExtraLicenseResponseData> getExtraLicenseData(ENV *);
    jboolean receivedLicenseResponse(ENV *);
    void queryProducts(ENV *, std::shared_ptr<jnivm::Array<std::shared_ptr<jnivm::java::lang::String>>>);
    void purchase(ENV *, std::shared_ptr<jnivm::java::lang::String>, jboolean, std::shared_ptr<jnivm::java::lang::String>);
    void acknowledgePurchase(ENV *, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
    void queryPurchases(ENV *);
    void destructor(ENV *);
};
class com::mojang::minecraftpe::store::ExtraLicenseResponseData : public jnivm::java::lang::Object {
public:
    jlong getValidationTime(ENV *);
    jlong getRetryUntilTime(ENV *);
    jlong getRetryAttempts(ENV *);
};

class com::mojang::android::net::HTTPResponse : public jnivm::java::lang::Object {
public:
    jint getStatus(ENV *);
    std::shared_ptr<jnivm::java::lang::String> getBody(ENV *);
    jint getResponseCode(ENV *);
    std::shared_ptr<jnivm::Array<jnivm::org::apache::http::Header>> getHeaders(ENV *);
};
class com::mojang::android::net::HTTPRequest : public jnivm::java::lang::Object {
public:
    HTTPRequest(ENV *, jnivm::java::lang::Class*);
    void setURL(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void setRequestBody(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void setCookieData(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void setContentType(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    std::shared_ptr<jnivm::com::mojang::android::net::HTTPResponse> send(ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void abort(ENV *);
};

class com::microsoft::xbox::idp::interop::Interop : public jnivm::java::lang::Object {
public:
    static std::shared_ptr<jnivm::java::lang::String> GetLocalStoragePath(ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::android::content::Context>);
    static std::shared_ptr<jnivm::java::lang::String> ReadConfigFile(ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::android::content::Context>);
    static std::shared_ptr<jnivm::java::lang::String> getSystemProxy(ENV *, jnivm::java::lang::Class*);
    static void InitCLL(ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::android::content::Context>, std::shared_ptr<jnivm::java::lang::String>);
    static void LogTelemetrySignIn(ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
    static void InvokeMSA(ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::android::content::Context>, jint, jboolean, std::shared_ptr<jnivm::java::lang::String>);
    static void InvokeAuthFlow(ENV *, jnivm::java::lang::Class*, jlong, std::shared_ptr<jnivm::android::app::Activity>, jboolean/* , std::shared_ptr<jnivm::java::lang::String> */);
    static std::shared_ptr<jnivm::java::lang::String> getLocale(ENV *, jnivm::java::lang::Class*);
    static void RegisterWithGNS(ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::android::content::Context>);
    static void LogCLL(ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
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
    static void ShowFriendFinder(ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::android::app::Activity>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
    static void ShowUserSettings(ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::android::content::Context>);
    static void ShowUserProfile(ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::android::content::Context>, std::shared_ptr<jnivm::java::lang::String>);
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
    std::shared_ptr<jnivm::android::view::View> getDecorView(ENV *);
};
class android::view::View : public jnivm::java::lang::Object {
public:
    std::shared_ptr<jnivm::android::os::IBinder> getWindowToken(ENV *);
};
class android::view::inputmethod::InputMethodManager : public jnivm::java::lang::Object {
public:
    jboolean showSoftInput(ENV *, std::shared_ptr<jnivm::android::view::View>, jint);
    jboolean hideSoftInputFromWindow(ENV *, std::shared_ptr<jnivm::android::os::IBinder>, jint);
};


class android::content::Context : public jnivm::java::lang::Object {
public:
    static std::shared_ptr<jnivm::java::lang::String> INPUT_METHOD_SERVICE;
    void startActivity(ENV *, std::shared_ptr<jnivm::android::content::Intent>);
    std::shared_ptr<jnivm::java::lang::String> getPackageName(ENV *);
};
class android::content::Intent : public jnivm::java::lang::Object {
public:
};
class android::content::ContextWrapper : public jnivm::java::lang::Object {
public:
    std::shared_ptr<jnivm::java::io::File> getFilesDir(ENV *);
    std::shared_ptr<jnivm::java::io::File> getCacheDir(ENV *);
};

class android::app::NativeActivity : public jnivm::java::lang::Object {
public:
    std::shared_ptr<jnivm::android::content::Context> getApplicationContext(ENV *);
};
class android::app::Activity : public jnivm::java::lang::Object {
public:
};

class java::lang::ClassLoader : public jnivm::java::lang::Object {
public:
    std::shared_ptr<jnivm::java::lang::Class> loadClass(ENV *, std::shared_ptr<jnivm::java::lang::String>);
};

class java::io::File : public jnivm::java::lang::String {
public:
    using jnivm::java::lang::String::String;
    std::shared_ptr<jnivm::java::lang::String> getPath(ENV *);
};