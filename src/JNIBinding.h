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
#include <hybris/dlfcn.h>
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
    void(*auth_flow_callback)(jnivm::ENV* env, void*, jlong paramLong, jint paramInt, jstring paramString);
    void onLogin(jnivm::ENV *, jlong, jboolean);
    void onError(jnivm::ENV *, jint, jint, std::shared_ptr<jnivm::java::lang::String>);
    void onSuccess(jnivm::ENV *);
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
    void(*nativeOnPickImageSuccess)(jnivm::ENV*, void*, jlong var1, jstring var3);
    void(*nativeOnPickImageCanceled)(jnivm::ENV*, void*, jlong var1);
    void(*nativeSetTextboxText)(jnivm::ENV*,void*, jstring);
    unsigned char* (*stbi_load_from_memory)(unsigned char const *buffer, int len, int *x, int *y, int *channels_in_file, int desired_channels);
    void (*stbi_image_free)(void *retval_from_stbi_load);
public:
    MainActivity(void * handle);
    std::shared_ptr<GameWindow> window;
    enum DirectionKey {
        LeftKey, RightKey, HomeKey, EndKey
    };
    void onKeyboardText(jnivm::ENV *,std::string const &text);
    void onKeyboardDirectionKey(DirectionKey key);
    void onKeyboardShiftKey(bool shiftPressed);
    void copyCurrentText();
    bool isKeyboardMultiline() const { return currentTextMutliline; }
    bool isKeyboardVisible() const { return iskeyboardvisible; }
    
    static void saveScreenshot(jnivm::ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::java::lang::String>, jint, jint, std::shared_ptr<jnivm::Array<jint>>);
    void postScreenshotToFacebook(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>, jint, jint, std::shared_ptr<jnivm::Array<jint>>);
    std::shared_ptr<jnivm::Array<jint>> getImageData(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    jnivm::Array<jbyte>* getFileDataBytes(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void displayDialog(jnivm::ENV *, jint);
    void tick(jnivm::ENV *);
    void quit(jnivm::ENV *);
    void initiateUserInput(jnivm::ENV *, jint);
    jint getUserInputStatus(jnivm::ENV *);
    jnivm::Array<std::shared_ptr<jnivm::java::lang::String>>* getUserInputString(jnivm::ENV *);
    jint checkLicense(jnivm::ENV *);
    jboolean hasBuyButtonWhenInvalidLicense(jnivm::ENV *);
    void buyGame(jnivm::ENV *);
    void vibrate(jnivm::ENV *, jint);
    void setIsPowerVR(jnivm::ENV *, jboolean);
    jboolean isNetworkEnabled(jnivm::ENV *, jboolean);
    jfloat getPixelsPerMillimeter(jnivm::ENV *);
    std::shared_ptr<jnivm::java::lang::String> getPlatformStringVar(jnivm::ENV *, jint);
    jnivm::java::lang::Object* getSystemService(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    jnivm::android::view::Window* getWindow(jnivm::ENV *);
    jint getKeyFromKeyCode(jnivm::ENV *, jint, jint, jint);
    void updateLocalization(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
    void showKeyboard(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>, jint, jboolean, jboolean, jboolean);
    void hideKeyboard(jnivm::ENV *);
    jfloat getKeyboardHeight(jnivm::ENV *);
    void updateTextboxText(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    jint getCursorPosition(jnivm::ENV *);
    std::shared_ptr<jnivm::java::lang::String> getAccessToken(jnivm::ENV *);
    std::shared_ptr<jnivm::java::lang::String> getClientId(jnivm::ENV *);
    std::shared_ptr<jnivm::java::lang::String> getProfileId(jnivm::ENV *);
    std::shared_ptr<jnivm::java::lang::String> getProfileName(jnivm::ENV *);
    jnivm::Array<std::shared_ptr<jnivm::java::lang::String>>* getBroadcastAddresses(jnivm::ENV *);
    jnivm::Array<std::shared_ptr<jnivm::java::lang::String>>* getIPAddresses(jnivm::ENV *);
    jlong getTotalMemory(jnivm::ENV *);
    jlong getMemoryLimit(jnivm::ENV *);
    jlong getUsedMemory(jnivm::ENV *);
    jlong getFreeMemory(jnivm::ENV *);
    void launchUri(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void setClipboard(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void share(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
    std::shared_ptr<jnivm::android::content::Intent> createAndroidLaunchIntent(jnivm::ENV *);
    jlong calculateAvailableDiskFreeSpace(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    std::shared_ptr<jnivm::java::lang::String> getExternalStoragePath(jnivm::ENV *);
    void requestStoragePermission(jnivm::ENV *, jint);
    jboolean hasWriteExternalStoragePermission(jnivm::ENV *);
    void deviceIdCorrelationStart(jnivm::ENV *);
    jboolean isMixerCreateInstalled(jnivm::ENV *);
    void navigateToPlaystoreForMixerCreate(jnivm::ENV *);
    jboolean launchMixerCreateForBroadcast(jnivm::ENV *);
    jboolean isTTSEnabled(jnivm::ENV *);
    std::shared_ptr<jnivm::com::mojang::minecraftpe::HardwareInformation> getHardwareInfo(jnivm::ENV *);
    void setCachedDeviceId(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void setLastDeviceSessionId(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    std::shared_ptr<jnivm::java::lang::String> getLastDeviceSessionId(jnivm::ENV *);
    jint getAPIVersion(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    std::shared_ptr<jnivm::java::lang::String> getSecureStorageKey(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void setSecureStorageKey(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
    void trackPurchaseEvent(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
    void sendBrazeEvent(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void sendBrazeEventWithProperty(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, jint);
    void sendBrazeEventWithStringProperty(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
    void sendBrazeToastClick(jnivm::ENV *);
    void sendBrazeDialogButtonClick(jnivm::ENV *, jint);
    void pickImage(jnivm::ENV *, jlong);
    void setFileDialogCallback(jnivm::ENV *, jlong);
    std::shared_ptr<jnivm::java::lang::String> getLegacyDeviceID(jnivm::ENV *);
    std::shared_ptr<jnivm::java::lang::String> createUUID(jnivm::ENV *);
    jboolean hasHardwareKeyboard(jnivm::ENV *);
    void startTextToSpeech(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void stopTextToSpeech(jnivm::ENV *);
    jboolean isTextToSpeechInProgress(jnivm::ENV *);
    void setTextToSpeechEnabled(jnivm::ENV *, jboolean);
    jint getScreenWidth(jnivm::ENV *);
    jint getScreenHeight(jnivm::ENV *);
    std::shared_ptr<jnivm::java::lang::String> getDeviceModel(jnivm::ENV *);
    jint getAndroidVersion(jnivm::ENV *);
    std::shared_ptr<jnivm::java::lang::String> getLocale(jnivm::ENV *);
    jboolean isFirstSnooperStart(jnivm::ENV *);
    jboolean hasHardwareChanged(jnivm::ENV *);
    jboolean isTablet(jnivm::ENV *);
    jnivm::java::lang::ClassLoader* getClassLoader(jnivm::ENV *);
};
class com::mojang::minecraftpe::HardwareInformation : public jnivm::java::lang::Object {
public:
    static std::shared_ptr<jnivm::java::lang::String> getDeviceModelName(jnivm::ENV *, jnivm::java::lang::Class*);
    static std::shared_ptr<jnivm::java::lang::String> getAndroidVersion(jnivm::ENV *, jnivm::java::lang::Class*);
    static std::shared_ptr<jnivm::java::lang::String> getCPUType(jnivm::ENV *, jnivm::java::lang::Class*);
    static std::shared_ptr<jnivm::java::lang::String> getCPUName(jnivm::ENV *, jnivm::java::lang::Class*);
    static std::shared_ptr<jnivm::java::lang::String> getCPUFeatures(jnivm::ENV *, jnivm::java::lang::Class*);
    static jint getNumCores(jnivm::ENV *, jnivm::java::lang::Class*);
    std::shared_ptr<jnivm::java::lang::String> getSecureId(jnivm::ENV *);
    static std::shared_ptr<jnivm::java::lang::String> getSerialNumber(jnivm::ENV *, jnivm::java::lang::Class*);
    static std::shared_ptr<jnivm::java::lang::String> getBoard(jnivm::ENV *, jnivm::java::lang::Class*);
    std::shared_ptr<jnivm::java::lang::String> getInstallerPackageName(jnivm::ENV *);
    jint getSignaturesHashCode(jnivm::ENV *);
    jboolean getIsRooted(jnivm::ENV *);
};
class com::mojang::minecraftpe::store::NativeStoreListener : public jnivm::java::lang::Object {
public:
    jlong nstorelisterner;
    // NativeStoreListener(jnivm::ENV *, jnivm::java::lang::Class*, jlong);
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
    static std::shared_ptr<jnivm::com::mojang::minecraftpe::store::Store> createGooglePlayStore(jnivm::ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::com::mojang::minecraftpe::store::NativeStoreListener>);
    static std::shared_ptr<jnivm::com::mojang::minecraftpe::store::Store> createAmazonAppStore(jnivm::ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::com::mojang::minecraftpe::store::NativeStoreListener>, jboolean);
};
class com::mojang::minecraftpe::store::StoreListener : public jnivm::java::lang::Object {
public:
};
class com::mojang::minecraftpe::store::Store : public jnivm::java::lang::Object {
public:
    std::shared_ptr<jnivm::java::lang::String> getStoreId(jnivm::ENV *);
    std::shared_ptr<jnivm::java::lang::String> getProductSkuPrefix(jnivm::ENV *);
    std::shared_ptr<jnivm::java::lang::String> getRealmsSkuPrefix(jnivm::ENV *);
    jboolean hasVerifiedLicense(jnivm::ENV *);
    std::shared_ptr<jnivm::com::mojang::minecraftpe::store::ExtraLicenseResponseData> getExtraLicenseData(jnivm::ENV *);
    jboolean receivedLicenseResponse(jnivm::ENV *);
    void queryProducts(jnivm::ENV *, jnivm::Array<std::shared_ptr<jnivm::java::lang::String>>*);
    void purchase(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>, jboolean, std::shared_ptr<jnivm::java::lang::String>);
    void acknowledgePurchase(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
    void queryPurchases(jnivm::ENV *);
    void destructor(jnivm::ENV *);
};
class com::mojang::minecraftpe::store::ExtraLicenseResponseData : public jnivm::java::lang::Object {
public:
    jlong getValidationTime(jnivm::ENV *);
    jlong getRetryUntilTime(jnivm::ENV *);
    jlong getRetryAttempts(jnivm::ENV *);
};

class com::mojang::android::net::HTTPResponse : public jnivm::java::lang::Object {
public:
    jint getStatus(jnivm::ENV *);
    std::shared_ptr<jnivm::java::lang::String> getBody(jnivm::ENV *);
    jint getResponseCode(jnivm::ENV *);
    jnivm::Array<jnivm::org::apache::http::Header*>* getHeaders(jnivm::ENV *);
};
class com::mojang::android::net::HTTPRequest : public jnivm::java::lang::Object {
public:
    HTTPRequest(jnivm::ENV *, jnivm::java::lang::Class*);
    void setURL(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void setRequestBody(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void setCookieData(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void setContentType(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    jnivm::com::mojang::android::net::HTTPResponse* send(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
    void abort(jnivm::ENV *);
};

class com::microsoft::xbox::idp::interop::Interop : public jnivm::java::lang::Object {
public:
    static std::shared_ptr<jnivm::java::lang::String> GetLocalStoragePath(jnivm::ENV *, jnivm::java::lang::Class*, jnivm::android::content::Context*);
    static std::shared_ptr<jnivm::java::lang::String> ReadConfigFile(jnivm::ENV *, jnivm::java::lang::Class*, jnivm::android::content::Context*);
    static std::shared_ptr<jnivm::java::lang::String> getSystemProxy(jnivm::ENV *, jnivm::java::lang::Class*);
    static void InitCLL(jnivm::ENV *, jnivm::java::lang::Class*, jnivm::android::content::Context*, std::shared_ptr<jnivm::java::lang::String>);
    static void LogTelemetrySignIn(jnivm::ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
    static void InvokeMSA(jnivm::ENV *, jnivm::java::lang::Class*, jnivm::android::content::Context*, jint, jboolean, std::shared_ptr<jnivm::java::lang::String>);
    static void InvokeAuthFlow(jnivm::ENV *, jnivm::java::lang::Class*, jlong, jnivm::android::app::Activity*, jboolean, std::shared_ptr<jnivm::java::lang::String>);
    static std::shared_ptr<jnivm::java::lang::String> getLocale(jnivm::ENV *, jnivm::java::lang::Class*);
    static void RegisterWithGNS(jnivm::ENV *, jnivm::java::lang::Class*, jnivm::android::content::Context*);
    static void LogCLL(jnivm::ENV *, jnivm::java::lang::Class*, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
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
    static void ShowFriendFinder(jnivm::ENV *, jnivm::java::lang::Class*, jnivm::android::app::Activity*, std::shared_ptr<jnivm::java::lang::String>, std::shared_ptr<jnivm::java::lang::String>);
    static void ShowUserSettings(jnivm::ENV *, jnivm::java::lang::Class*, jnivm::android::content::Context*);
    static void ShowUserProfile(jnivm::ENV *, jnivm::java::lang::Class*, jnivm::android::content::Context*, std::shared_ptr<jnivm::java::lang::String>);
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
    jnivm::android::view::View* getDecorView(jnivm::ENV *);
};
class android::view::View : public jnivm::java::lang::Object {
public:
    jnivm::android::os::IBinder* getWindowToken(jnivm::ENV *);
};
class android::view::inputmethod::InputMethodManager : public jnivm::java::lang::Object {
public:
    jboolean showSoftInput(jnivm::ENV *, jnivm::android::view::View*, jint);
    jboolean hideSoftInputFromWindow(jnivm::ENV *, jnivm::android::os::IBinder*, jint);
};


class android::content::Context : public jnivm::java::lang::Object {
public:
    static std::shared_ptr<jnivm::java::lang::String> INPUT_METHOD_SERVICE;
    void startActivity(jnivm::ENV *, std::shared_ptr<jnivm::android::content::Intent>);
    std::shared_ptr<jnivm::java::lang::String> getPackageName(jnivm::ENV *);
};
class android::content::Intent : public jnivm::java::lang::Object {
public:
};
class android::content::ContextWrapper : public jnivm::java::lang::Object {
public:
    jnivm::java::io::File* getFilesDir(jnivm::ENV *);
    jnivm::java::io::File* getCacheDir(jnivm::ENV *);
};

class android::app::NativeActivity : public jnivm::java::lang::Object {
public:
    jnivm::android::content::Context* getApplicationContext(jnivm::ENV *);
};
class android::app::Activity : public jnivm::java::lang::Object {
public:
};

class java::lang::ClassLoader : public jnivm::java::lang::Object {
public:
    std::shared_ptr<jnivm::java::lang::Class> loadClass(jnivm::ENV *, std::shared_ptr<jnivm::java::lang::String>);
};

class java::io::File : public jnivm::java::lang::String {
public:
    using jnivm::java::lang::String::String;
    std::shared_ptr<jnivm::java::lang::String> getPath(jnivm::ENV *);
};