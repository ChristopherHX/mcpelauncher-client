#include <log.h>
#include <dlfcn.h>
#include <game_window_manager.h>
#include <argparser.h>
#include <mcpelauncher/linker.h>
#include <mcpelauncher/minecraft_utils.h>
#include <mcpelauncher/minecraft_version.h>
#include <mcpelauncher/crash_handler.h>
#include <mcpelauncher/path_helper.h>
#include <mcpelauncher/mod_loader.h>
#include <mcpelauncher/patch_utils.h>
#include "window_callbacks.h"
#include "xbox_live_helper.h"
#include "hbui_patch.h"
#ifdef USE_ARMHF_SUPPORT
#include "armhf_support.h"
#endif
#ifdef __i386__
#include "cpuid.h"
#endif
#include <build_info.h>
#include "native_activity.h"
#include <jnivm.h>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <unistd.h>
#include "JNIBinding.h"
#include <sys/timeb.h>
#include "OpenSLESPatch.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <climits>
#include <map>
#include <libc_shim.h>
#include <minecraft/imported/android_symbols.h>
#include <minecraft/symbols.h>
#include <minecraft/SharedConstants.h>
#define EGL_NONE 0x3038
#define EGL_TRUE 1
#define EGL_FALSE 0
#define EGL_WIDTH 0x3057
#define EGL_HEIGHT 0x3056
using EGLint = int;
using EGLDisplay = void*;
using EGLSurface = void*;
using EGLContext = void*;
using EGLConfig = void*;
using NativeWindowType = void*;
using NativeDisplayType = void*;

JNIEnv * jnienv = 0;

void printVersionInfo();

std::map<std::string, void*> eglfuncs = {{ "glInvalidateFramebuffer", (void*)+[]() {}}};

#define hybris_hook(a, b) syms[(a)] = (void*)(b);

#ifdef __arm__
namespace FMOD {
  struct ChannelControl {
    int setVolume(float);
    int setPitch(float);
    int addFadePoint(unsigned long long, float);
  };
  struct Sound {
    int set3DMinMaxDistance(float, float);
  };
  struct System {
    int set3DSettings(float, float, float);
  };
}

// Translate arm softfp to armhf
int32_t __attribute__((pcs("aapcs"))) FMOD_ChannelControl_setVolume(FMOD::ChannelControl *ch, float f) {
  return ch->setVolume(f);
}

int32_t __attribute__((pcs("aapcs"))) FMOD_ChannelControl_setPitch(FMOD::ChannelControl *ch, float p) {
  return ch->setPitch(p);
}

int32_t __attribute__((pcs("aapcs"))) FMOD_System_set3DSettings(FMOD::System *sys, float x, float y, float z) {
  return sys->set3DSettings(x, y, z);
}

int32_t __attribute__((pcs("aapcs"))) FMOD_Sound_set3DMinMaxDistance(FMOD::Sound *s, float m, float M) {
  return s->set3DMinMaxDistance(m, M);
}

int32_t __attribute__((pcs("aapcs"))) FMOD_ChannelControl_addFadePoint(FMOD::ChannelControl *ch, unsigned long long i, float f) {
  return ch->addFadePoint(i, f);
}
#endif

#include <cinttypes>

void InitJNIBinding(jnivm::ENV* env) {
env->GetClass<jnivm::java::lang::Object>("java/lang/Object");
env->GetClass<jnivm::java::lang::Class>("java/lang/Class");
env->GetClass<jnivm::java::lang::String>("java/lang/String");
env->GetClass<jnivm::java::lang::ClassLoader>("java/lang/ClassLoader");
env->GetClass<jnivm::java::nio::ByteBuffer>("java/nio/ByteBuffer");
env->GetClass<jnivm::java::io::File>("java/io/File");
env->GetClass<jnivm::com::mojang::minecraftpe::MainActivity>("com/mojang/minecraftpe/MainActivity");
env->GetClass<jnivm::com::mojang::minecraftpe::HardwareInformation>("com/mojang/minecraftpe/HardwareInformation");
env->GetClass<jnivm::com::mojang::minecraftpe::store::NativeStoreListener>("com/mojang/minecraftpe/store/NativeStoreListener");
env->GetClass<jnivm::com::mojang::minecraftpe::store::Product>("com/mojang/minecraftpe/store/Product");
env->GetClass<jnivm::com::mojang::minecraftpe::store::Purchase>("com/mojang/minecraftpe/store/Purchase");
env->GetClass<jnivm::com::mojang::minecraftpe::store::StoreFactory>("com/mojang/minecraftpe/store/StoreFactory");
env->GetClass<jnivm::com::mojang::minecraftpe::store::StoreListener>("com/mojang/minecraftpe/store/StoreListener");
env->GetClass<jnivm::com::mojang::minecraftpe::store::Store>("com/mojang/minecraftpe/store/Store");
env->GetClass<jnivm::com::mojang::minecraftpe::store::ExtraLicenseResponseData>("com/mojang/minecraftpe/store/ExtraLicenseResponseData");
env->GetClass<jnivm::com::mojang::android::net::HTTPResponse>("com/mojang/android/net/HTTPResponse");
env->GetClass<jnivm::com::mojang::android::net::HTTPRequest>("com/mojang/android/net/HTTPRequest");
env->GetClass<jnivm::android::os::Build>("android/os/Build");
env->GetClass<jnivm::android::os::IBinder>("android/os/IBinder");
env->GetClass<jnivm::android::view::Window>("android/view/Window");
env->GetClass<jnivm::android::view::View>("android/view/View");
env->GetClass<jnivm::android::view::inputmethod::InputMethodManager>("android/view/inputmethod/InputMethodManager");
env->GetClass<jnivm::android::content::Context>("android/content/Context");
env->GetClass<jnivm::android::content::Intent>("android/content/Intent");
env->GetClass<jnivm::android::content::ContextWrapper>("android/content/ContextWrapper");
env->GetClass<jnivm::android::app::NativeActivity>("android/app/NativeActivity");
// env->GetClass<jnivm::org::apache::http::Header>("org/apache/http/Header");
env->GetClass<jnivm::android::app::Activity>("android/app/Activity");
env->GetClass<jnivm::XBLoginCallback>("XBLoginCallback");
{
auto c = env->GetClass("java/lang/ClassLoader");
c->Hook(env, "loadClass", &::jnivm::java::lang::ClassLoader::loadClass);
}
{
auto c = env->GetClass("java/io/File");
c->Hook(env, "getPath", &::jnivm::java::io::File::getPath);
}
{
auto c = env->GetClass("com/mojang/minecraftpe/MainActivity");
c->Hook(env, "saveScreenshot", &::jnivm::com::mojang::minecraftpe::MainActivity::saveScreenshot);
c->Hook(env, "postScreenshotToFacebook", &::jnivm::com::mojang::minecraftpe::MainActivity::postScreenshotToFacebook);
c->Hook(env, "getImageData", &::jnivm::com::mojang::minecraftpe::MainActivity::getImageData);
c->Hook(env, "getFileDataBytes", &::jnivm::com::mojang::minecraftpe::MainActivity::getFileDataBytes);
c->Hook(env, "displayDialog", &::jnivm::com::mojang::minecraftpe::MainActivity::displayDialog);
c->Hook(env, "tick", &::jnivm::com::mojang::minecraftpe::MainActivity::tick);
c->Hook(env, "quit", &::jnivm::com::mojang::minecraftpe::MainActivity::quit);
c->Hook(env, "initiateUserInput", &::jnivm::com::mojang::minecraftpe::MainActivity::initiateUserInput);
c->Hook(env, "getUserInputStatus", &::jnivm::com::mojang::minecraftpe::MainActivity::getUserInputStatus);
c->Hook(env, "getUserInputString", &::jnivm::com::mojang::minecraftpe::MainActivity::getUserInputString);
// c->Hook(env, "getDateString", &::jnivm::com::mojang::minecraftpe::MainActivity::getDateString);
c->Hook(env, "checkLicense", &::jnivm::com::mojang::minecraftpe::MainActivity::checkLicense);
c->Hook(env, "hasBuyButtonWhenInvalidLicense", &::jnivm::com::mojang::minecraftpe::MainActivity::hasBuyButtonWhenInvalidLicense);
c->Hook(env, "buyGame", &::jnivm::com::mojang::minecraftpe::MainActivity::buyGame);
c->Hook(env, "vibrate", &::jnivm::com::mojang::minecraftpe::MainActivity::vibrate);
c->Hook(env, "setIsPowerVR", &::jnivm::com::mojang::minecraftpe::MainActivity::setIsPowerVR);
c->Hook(env, "isNetworkEnabled", &::jnivm::com::mojang::minecraftpe::MainActivity::isNetworkEnabled);
c->Hook(env, "getPixelsPerMillimeter", &::jnivm::com::mojang::minecraftpe::MainActivity::getPixelsPerMillimeter);
c->Hook(env, "getPlatformStringVar", &::jnivm::com::mojang::minecraftpe::MainActivity::getPlatformStringVar);
c->Hook(env, "getSystemService", &::jnivm::com::mojang::minecraftpe::MainActivity::getSystemService);
c->Hook(env, "getWindow", &::jnivm::com::mojang::minecraftpe::MainActivity::getWindow);
c->Hook(env, "getKeyFromKeyCode", &::jnivm::com::mojang::minecraftpe::MainActivity::getKeyFromKeyCode);
c->Hook(env, "updateLocalization", &::jnivm::com::mojang::minecraftpe::MainActivity::updateLocalization);
c->Hook(env, "showKeyboard", &::jnivm::com::mojang::minecraftpe::MainActivity::showKeyboard);
c->Hook(env, "hideKeyboard", &::jnivm::com::mojang::minecraftpe::MainActivity::hideKeyboard);
c->Hook(env, "getKeyboardHeight", &::jnivm::com::mojang::minecraftpe::MainActivity::getKeyboardHeight);
c->Hook(env, "updateTextboxText", &::jnivm::com::mojang::minecraftpe::MainActivity::updateTextboxText);
c->Hook(env, "getAccessToken", &::jnivm::com::mojang::minecraftpe::MainActivity::getAccessToken);
c->Hook(env, "getClientId", &::jnivm::com::mojang::minecraftpe::MainActivity::getClientId);
c->Hook(env, "getProfileId", &::jnivm::com::mojang::minecraftpe::MainActivity::getProfileId);
c->Hook(env, "getProfileName", &::jnivm::com::mojang::minecraftpe::MainActivity::getProfileName);
c->Hook(env, "getBroadcastAddresses", &::jnivm::com::mojang::minecraftpe::MainActivity::getBroadcastAddresses);
c->Hook(env, "getIPAddresses", &::jnivm::com::mojang::minecraftpe::MainActivity::getIPAddresses);
c->Hook(env, "getTotalMemory", &::jnivm::com::mojang::minecraftpe::MainActivity::getTotalMemory);
c->Hook(env, "launchUri", &::jnivm::com::mojang::minecraftpe::MainActivity::launchUri);
c->Hook(env, "createAndroidLaunchIntent", &::jnivm::com::mojang::minecraftpe::MainActivity::createAndroidLaunchIntent);
c->Hook(env, "pickImage", &::jnivm::com::mojang::minecraftpe::MainActivity::pickImage);
c->Hook(env, "setFileDialogCallback", &::jnivm::com::mojang::minecraftpe::MainActivity::setFileDialogCallback);
// c->Hook(env, "getDeviceId", &::jnivm::com::mojang::minecraftpe::MainActivity::getDeviceId);
c->Hook(env, "createUUID", &::jnivm::com::mojang::minecraftpe::MainActivity::createUUID);
c->Hook(env, "showKeyboard", &::jnivm::com::mojang::minecraftpe::MainActivity::showKeyboard);
c->Hook(env, "getCursorPosition", &::jnivm::com::mojang::minecraftpe::MainActivity::getCursorPosition);
c->Hook(env, "getMemoryLimit", &::jnivm::com::mojang::minecraftpe::MainActivity::getMemoryLimit);
c->Hook(env, "getUsedMemory", &::jnivm::com::mojang::minecraftpe::MainActivity::getUsedMemory);
c->Hook(env, "getFreeMemory", &::jnivm::com::mojang::minecraftpe::MainActivity::getFreeMemory);
c->Hook(env, "setClipboard", &::jnivm::com::mojang::minecraftpe::MainActivity::setClipboard);
c->Hook(env, "share", &::jnivm::com::mojang::minecraftpe::MainActivity::share);
c->Hook(env, "calculateAvailableDiskFreeSpace", &::jnivm::com::mojang::minecraftpe::MainActivity::calculateAvailableDiskFreeSpace);
c->Hook(env, "getExternalStoragePath", &::jnivm::com::mojang::minecraftpe::MainActivity::getExternalStoragePath);
c->Hook(env, "requestStoragePermission", &::jnivm::com::mojang::minecraftpe::MainActivity::requestStoragePermission);
c->Hook(env, "hasWriteExternalStoragePermission", &::jnivm::com::mojang::minecraftpe::MainActivity::hasWriteExternalStoragePermission);
c->Hook(env, "deviceIdCorrelationStart", &::jnivm::com::mojang::minecraftpe::MainActivity::deviceIdCorrelationStart);
c->Hook(env, "isMixerCreateInstalled", &::jnivm::com::mojang::minecraftpe::MainActivity::isMixerCreateInstalled);
c->Hook(env, "navigateToPlaystoreForMixerCreate", &::jnivm::com::mojang::minecraftpe::MainActivity::navigateToPlaystoreForMixerCreate);
c->Hook(env, "launchMixerCreateForBroadcast", &::jnivm::com::mojang::minecraftpe::MainActivity::launchMixerCreateForBroadcast);
c->Hook(env, "isTTSEnabled", &::jnivm::com::mojang::minecraftpe::MainActivity::isTTSEnabled);
c->Hook(env, "initializeXboxLive", &::jnivm::com::mojang::minecraftpe::MainActivity::initializeXboxLive);
c->Hook(env, "getHardwareInfo", &::jnivm::com::mojang::minecraftpe::MainActivity::getHardwareInfo);
c->Hook(env, "setCachedDeviceId", &::jnivm::com::mojang::minecraftpe::MainActivity::setCachedDeviceId);
c->Hook(env, "getLastDeviceSessionId", &::jnivm::com::mojang::minecraftpe::MainActivity::getLastDeviceSessionId);
c->Hook(env, "getAPIVersion", &::jnivm::com::mojang::minecraftpe::MainActivity::getAPIVersion);
c->Hook(env, "getSecureStorageKey", &::jnivm::com::mojang::minecraftpe::MainActivity::getSecureStorageKey);
c->Hook(env, "setSecureStorageKey", &::jnivm::com::mojang::minecraftpe::MainActivity::setSecureStorageKey);
c->Hook(env, "trackPurchaseEvent", &::jnivm::com::mojang::minecraftpe::MainActivity::trackPurchaseEvent);
c->Hook(env, "sendBrazeEvent", &::jnivm::com::mojang::minecraftpe::MainActivity::sendBrazeEvent);
c->Hook(env, "sendBrazeEventWithProperty", &::jnivm::com::mojang::minecraftpe::MainActivity::sendBrazeEventWithProperty);
c->Hook(env, "sendBrazeEventWithStringProperty", &::jnivm::com::mojang::minecraftpe::MainActivity::sendBrazeEventWithStringProperty);
c->Hook(env, "sendBrazeToastClick", &::jnivm::com::mojang::minecraftpe::MainActivity::sendBrazeToastClick);
c->Hook(env, "sendBrazeDialogButtonClick", &::jnivm::com::mojang::minecraftpe::MainActivity::sendBrazeDialogButtonClick);
c->Hook(env, "getLegacyDeviceID", &::jnivm::com::mojang::minecraftpe::MainActivity::getLegacyDeviceID);
c->Hook(env, "hasHardwareKeyboard", &::jnivm::com::mojang::minecraftpe::MainActivity::hasHardwareKeyboard);
c->Hook(env, "startTextToSpeech", &::jnivm::com::mojang::minecraftpe::MainActivity::startTextToSpeech);
c->Hook(env, "stopTextToSpeech", &::jnivm::com::mojang::minecraftpe::MainActivity::stopTextToSpeech);
c->Hook(env, "isTextToSpeechInProgress", &::jnivm::com::mojang::minecraftpe::MainActivity::isTextToSpeechInProgress);
c->Hook(env, "setTextToSpeechEnabled", &::jnivm::com::mojang::minecraftpe::MainActivity::setTextToSpeechEnabled);
c->Hook(env, "getScreenWidth", &::jnivm::com::mojang::minecraftpe::MainActivity::getScreenWidth);
c->Hook(env, "getScreenHeight", &::jnivm::com::mojang::minecraftpe::MainActivity::getScreenHeight);
c->Hook(env, "getDeviceModel", &::jnivm::com::mojang::minecraftpe::MainActivity::getDeviceModel);
c->Hook(env, "getAndroidVersion", &::jnivm::com::mojang::minecraftpe::MainActivity::getAndroidVersion);
c->Hook(env, "getLocale", &::jnivm::com::mojang::minecraftpe::MainActivity::getLocale);
c->Hook(env, "isTablet", &::jnivm::com::mojang::minecraftpe::MainActivity::isTablet);
c->Hook(env, "isFirstSnooperStart", &::jnivm::com::mojang::minecraftpe::MainActivity::isFirstSnooperStart);
c->Hook(env, "hasHardwareChanged", &::jnivm::com::mojang::minecraftpe::MainActivity::hasHardwareChanged);
c->Hook(env, "getClassLoader", &::jnivm::com::mojang::minecraftpe::MainActivity::getClassLoader);
c->Hook(env, "initializeXboxLive", &::jnivm::com::mojang::minecraftpe::MainActivity::initializeXboxLive);
}
{
auto c = env->GetClass("com/mojang/minecraftpe/HardwareInformation");
c->Hook(env, "getDeviceModelName", &::jnivm::com::mojang::minecraftpe::HardwareInformation::getDeviceModelName);
c->Hook(env, "getAndroidVersion", &::jnivm::com::mojang::minecraftpe::HardwareInformation::getAndroidVersion);
c->Hook(env, "getCPUType", &::jnivm::com::mojang::minecraftpe::HardwareInformation::getCPUType);
c->Hook(env, "getCPUName", &::jnivm::com::mojang::minecraftpe::HardwareInformation::getCPUName);
c->Hook(env, "getCPUFeatures", &::jnivm::com::mojang::minecraftpe::HardwareInformation::getCPUFeatures);
c->Hook(env, "getNumCores", &::jnivm::com::mojang::minecraftpe::HardwareInformation::getNumCores);
c->Hook(env, "getSecureId", &::jnivm::com::mojang::minecraftpe::HardwareInformation::getSecureId);
c->Hook(env, "getSerialNumber", &::jnivm::com::mojang::minecraftpe::HardwareInformation::getSerialNumber);
c->Hook(env, "getBoard", &::jnivm::com::mojang::minecraftpe::HardwareInformation::getBoard);
c->Hook(env, "getInstallerPackageName", &::jnivm::com::mojang::minecraftpe::HardwareInformation::getInstallerPackageName);
c->Hook(env, "getSignaturesHashCode", &::jnivm::com::mojang::minecraftpe::HardwareInformation::getSignaturesHashCode);
c->Hook(env, "getIsRooted", &::jnivm::com::mojang::minecraftpe::HardwareInformation::getIsRooted);
}
{
auto c = env->GetClass("com/mojang/minecraftpe/store/NativeStoreListener");
// c->Hook(env, "<init>", [](jnivm::ENV *env, jnivm::java::lang::Class* cl, jlong arg0) {   return std::make_shared<::jnivm::com::mojang::minecraftpe::store::NativeStoreListener::NativeStoreListener>(env, cl, arg0);});
c->Hook(env, "<init>", [](jnivm::ENV *env, jnivm::java::lang::Class* cl, jlong arg0) {   return std::make_shared<::jnivm::com::mojang::minecraftpe::store::NativeStoreListener>(env, cl, arg0);});
}
{
auto c = env->GetClass("com/mojang/minecraftpe/store/Product");
c->Hook(env, "mId", &::jnivm::com::mojang::minecraftpe::store::Product::mId);
c->Hook(env, "mPrice", &::jnivm::com::mojang::minecraftpe::store::Product::mPrice);
c->Hook(env, "mCurrencyCode", &::jnivm::com::mojang::minecraftpe::store::Product::mCurrencyCode);
c->Hook(env, "mUnformattedPrice", &::jnivm::com::mojang::minecraftpe::store::Product::mUnformattedPrice);
}
{
auto c = env->GetClass("com/mojang/minecraftpe/store/Purchase");
c->Hook(env, "mProductId", &::jnivm::com::mojang::minecraftpe::store::Purchase::mProductId);
c->Hook(env, "mReceipt", &::jnivm::com::mojang::minecraftpe::store::Purchase::mReceipt);
c->Hook(env, "mPurchaseActive", &::jnivm::com::mojang::minecraftpe::store::Purchase::mPurchaseActive);
}
{
auto c = env->GetClass("com/mojang/minecraftpe/store/StoreFactory");
c->Hook(env, "createGooglePlayStore", &::jnivm::com::mojang::minecraftpe::store::StoreFactory::createGooglePlayStore);
c->Hook(env, "createAmazonAppStore", &::jnivm::com::mojang::minecraftpe::store::StoreFactory::createAmazonAppStore);
c->Hook(env, "createAmazonAppStore", &::jnivm::com::mojang::minecraftpe::store::StoreFactory::createAmazonAppStore);
}
{
auto c = env->GetClass("com/mojang/minecraftpe/store/StoreListener");
}
{
auto c = env->GetClass("com/mojang/minecraftpe/store/Store");
c->Hook(env, "getStoreId", &::jnivm::com::mojang::minecraftpe::store::Store::getStoreId);
c->Hook(env, "queryProducts", &::jnivm::com::mojang::minecraftpe::store::Store::queryProducts);
c->Hook(env, "purchase", &::jnivm::com::mojang::minecraftpe::store::Store::purchase);
c->Hook(env, "acknowledgePurchase", &::jnivm::com::mojang::minecraftpe::store::Store::acknowledgePurchase);
c->Hook(env, "queryPurchases", &::jnivm::com::mojang::minecraftpe::store::Store::queryPurchases);
c->Hook(env, "destructor", &::jnivm::com::mojang::minecraftpe::store::Store::destructor);
c->Hook(env, "getProductSkuPrefix", &::jnivm::com::mojang::minecraftpe::store::Store::getProductSkuPrefix);
c->Hook(env, "getRealmsSkuPrefix", &::jnivm::com::mojang::minecraftpe::store::Store::getRealmsSkuPrefix);
c->Hook(env, "hasVerifiedLicense", &::jnivm::com::mojang::minecraftpe::store::Store::hasVerifiedLicense);
c->Hook(env, "getExtraLicenseData", &::jnivm::com::mojang::minecraftpe::store::Store::getExtraLicenseData);
c->Hook(env, "receivedLicenseResponse", &::jnivm::com::mojang::minecraftpe::store::Store::receivedLicenseResponse);
}
{
auto c = env->GetClass("com/mojang/minecraftpe/store/ExtraLicenseResponseData");
}
// {
// auto c = env->GetClass("com/mojang/android/net/HTTPResponse");
// c->Hook(env, "getStatus", &::jnivm::com::mojang::android::net::HTTPResponse::getStatus);
// c->Hook(env, "getBody", &::jnivm::com::mojang::android::net::HTTPResponse::getBody);
// c->Hook(env, "getResponseCode", &::jnivm::com::mojang::android::net::HTTPResponse::getResponseCode);
// c->Hook(env, "getHeaders", &::jnivm::com::mojang::android::net::HTTPResponse::getHeaders);
// }
// {
// auto c = env->GetClass("com/mojang/android/net/HTTPRequest");
// // c->Hook(env, "<init>", [](jnivm::ENV *env, jnivm::java::lang::Class* cl) {   return std::make_shared<::jnivm::com::mojang::android::net::HTTPRequest::HTTPRequest>(env, cl);});
// c->Hook(env, "setURL", &::jnivm::com::mojang::android::net::HTTPRequest::setURL);
// c->Hook(env, "setRequestBody", &::jnivm::com::mojang::android::net::HTTPRequest::setRequestBody);
// c->Hook(env, "setCookieData", &::jnivm::com::mojang::android::net::HTTPRequest::setCookieData);
// c->Hook(env, "setContentType", &::jnivm::com::mojang::android::net::HTTPRequest::setContentType);
// c->Hook(env, "send", &::jnivm::com::mojang::android::net::HTTPRequest::send);
// c->Hook(env, "abort", &::jnivm::com::mojang::android::net::HTTPRequest::abort);
// }
{
auto c = env->GetClass("android/os/Build");
{
auto c = env->GetClass("android/os/Build$VERSION");
c->Hook(env, "SDK_INT", &::jnivm::android::os::Build::VERSION::SDK_INT);
}
// c->Hook(env, "MANUFACTURER", &::jnivm::android::os::Build::MANUFACTURER);
// c->Hook(env, "MODEL", &::jnivm::android::os::Build::MODEL);
}
{
auto c = env->GetClass("android/os/IBinder");
}
{
auto c = env->GetClass("android/view/Window");
c->Hook(env, "getDecorView", &::jnivm::android::view::Window::getDecorView);
}
{
auto c = env->GetClass("android/view/View");
c->Hook(env, "getWindowToken", &::jnivm::android::view::View::getWindowToken);
}
{
auto c = env->GetClass("android/view/inputmethod/InputMethodManager");
c->Hook(env, "showSoftInput", &::jnivm::android::view::inputmethod::InputMethodManager::showSoftInput);
c->Hook(env, "hideSoftInputFromWindow", &::jnivm::android::view::inputmethod::InputMethodManager::hideSoftInputFromWindow);
}
{
auto c = env->GetClass("android/content/Context");
c->Hook(env, "INPUT_METHOD_SERVICE", &::jnivm::android::content::Context::INPUT_METHOD_SERVICE);
}
{
auto c = env->GetClass("android/content/Intent");
}
{
auto c = env->GetClass("android/content/ContextWrapper");
c->Hook(env, "getFilesDir", &::jnivm::android::content::ContextWrapper::getFilesDir);
c->Hook(env, "getCacheDir", &::jnivm::android::content::ContextWrapper::getCacheDir);
}
{
auto c = env->GetClass("android/app/NativeActivity");
c->Hook(env, "getApplicationContext", &::jnivm::android::app::NativeActivity::getApplicationContext);
}
{
// auto c = env->GetClass("org/apache/http/Header");
// c->Hook(env, "getName", &::jnivm::org::apache::http::Header::getName);
// c->Hook(env, "getValue", &::jnivm::org::apache::http::Header::getValue);
}
{
auto c = env->GetClass("com/microsoft/xbox/idp/interop/Interop");
c->Hook(env, "ReadConfigFile", &::jnivm::com::microsoft::xbox::idp::interop::Interop::ReadConfigFile);
c->Hook(env, "getSystemProxy", &::jnivm::com::microsoft::xbox::idp::interop::Interop::getSystemProxy);
c->Hook(env, "InvokeMSA", &::jnivm::com::microsoft::xbox::idp::interop::Interop::InvokeMSA);
c->Hook(env, "GetLocalStoragePath", &::jnivm::com::microsoft::xbox::idp::interop::Interop::GetLocalStoragePath);
c->Hook(env, "InvokeAuthFlow", &::jnivm::com::microsoft::xbox::idp::interop::Interop::InvokeAuthFlow);
}
{
  auto c = env->GetClass<jnivm::XBLoginCallback>("XBLoginCallback");
  c->Hook(env, "onLogin", &::jnivm::XBLoginCallback::onLogin);
  c->Hook(env, "onError", &::jnivm::XBLoginCallback::onError);
  c->Hook(env, "onSuccess", &::jnivm::XBLoginCallback::onSuccess);
}
}

int main(int argc, char *argv[]) {
    static auto windowManager = GameWindowManager::getManager();
    CrashHandler::registerCrashHandler();
    MinecraftUtils::workaroundLocaleBug();

    argparser::arg_parser p;
    argparser::arg<bool> printVersion (p, "--version", "-v", "Prints version info");
    argparser::arg<std::string> gameDir (p, "--game-dir", "-dg", "Directory with the game and assets");
    argparser::arg<std::string> dataDir (p, "--data-dir", "-dd", "Directory to use for the data");
    argparser::arg<std::string> cacheDir (p, "--cache-dir", "-dc", "Directory to use for cache");
    argparser::arg<int> windowWidth (p, "--width", "-ww", "Window width", 720);
    argparser::arg<int> windowHeight (p, "--height", "-wh", "Window height", 480);
    argparser::arg<float> pixelScale (p, "--scale", "-s", "Pixel Scale", 2.f);
    argparser::arg<bool> mallocZero (p, "--malloc-zero", "-mz", "Patch malloc to always zero initialize memory, this may help workaround MCPE bugs");
    argparser::arg<bool> disableFmod (p, "--disable-fmod", "-df", "Disables usage of the FMod audio library");
    if (!p.parse(argc, (const char**) argv))
        return 1;
    if (printVersion) {
        printVersionInfo();
        return 0;
    }
    if (!gameDir.get().empty())
        PathHelper::setGameDir(gameDir);
    if (!dataDir.get().empty())        PathHelper::setDataDir(dataDir);
    if (!cacheDir.get().empty())
        PathHelper::setCacheDir(cacheDir);

    Log::info("Launcher", "Version: client %s / manifest %s", CLIENT_GIT_COMMIT_HASH, MANIFEST_GIT_COMMIT_HASH);
#ifdef __i386__
    {
        CpuId cpuid;
        Log::info("Launcher", "CPU: %s %s", cpuid.getManufacturer(), cpuid.getBrandString());
        Log::info("Launcher", "CPU supports SSSE3: %s",
                cpuid.queryFeatureFlag(CpuId::FeatureFlag::SSSE3) ? "YES" : "NO");
    }
#endif

    GraphicsApi graphicsApi = GraphicsApi::OPENGL_ES2;

    
    std::unordered_map<std::string, void*> syms;

    for (size_t i = 0; android_symbols[i]; i++)
    {
      hybris_hook(android_symbols[i], (void*)+[]() {
        
      });
    }
    for(auto&&sym : shim::get_shimmed_symbols()) {
      // if(!strcmp(sym.name, "syscall")) {
      //   hybris_hook("syscall", sym.value);
      // }
      // if(!strcmp(sym.name, "ioctl")) {
      //   hybris_hook("ioctl", sym.value);
      // }
      hybris_hook(sym.name, sym.value);
    }
    // Get rid of defining OPENSSL_armcap
    hybris_hook("OPENSSL_cpuid_setup", (void*) + []() -> void {});

    MinecraftUtils::setupHybris();

    Log::info("Launcher", "Creating window");
    WindowCallbacks::loadGamepadMappings();
    static auto window = windowManager->createWindow("Minecraft", windowWidth, windowHeight, graphicsApi);
    window->setIcon(PathHelper::getIconPath());
    window->show();
    hybris_hook("ANativeActivity_finish", (void *)+[](ANativeActivity *activity) {
      Log::warn("Launcher", "Android stub %s called", "ANativeActivity_finish");
      std::thread([=]() {
        // Saves nothing (returns every time null)
        // size_t outSize;
        // void * data = activity->callbacks->onSaveInstanceState(activity, &outSize);
        // ((void(*)(ENV * env, void*))linker::dlsym(jnienv->functions->reserved3, "Java_com_mojang_minecraftpe_MainActivity_nativeUnregisterThis"))(jnienv, nullptr);
        // ((void(*)(ENV * env, void*))linker::dlsym(jnienv->functions->reserved3, "Java_com_mojang_minecraftpe_MainActivity_nativeSuspend"))(jnienv, nullptr);
        // ((void(*)(ENV * env, void*))linker::dlsym(jnienv->functions->reserved3, "Java_com_mojang_minecraftpe_MainActivity_nativeShutdown"))(jnienv, nullptr);
        activity->callbacks->onStop(activity);
      }).detach();
      // With Xboxlive it usually don't close the Game with the main function correctly
      // Force exit with code 0 (Maybe Android related)
      _Exit(0);
    });
    hybris_hook("eglChooseConfig", (void *)+[](EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config) {
      *num_config = 1;
      return EGL_TRUE;
    });
    hybris_hook("eglGetError", (void *)(void (*)())[]() {
    });
    hybris_hook("eglGetCurrentDisplay", (void *)+[]() -> EGLDisplay {
      return (EGLDisplay)1;
    });
    hybris_hook("eglCreateWindowSurface", (void *)+[](EGLDisplay display,
      EGLConfig config,
      NativeWindowType native_window,
      EGLint const * attrib_list) {
      return native_window;
    });
    hybris_hook("eglGetConfigAttrib", (void *)+[](EGLDisplay display,
      EGLConfig config,
      EGLint attribute,
      EGLint * value) {
      return EGL_TRUE;
    });
    hybris_hook("eglCreateContext", (void *)+[](EGLDisplay display,
      EGLConfig config,
      EGLContext share_context,
      EGLint const * attrib_list) {
      return 1;
    });
    hybris_hook("eglDestroySurface", (void *)(void (*)())[]() {
    });
    hybris_hook("eglSwapBuffers", (void *)+[](EGLDisplay *display,
      EGLSurface surface) {
        window->swapBuffers();
    });
    hybris_hook("eglMakeCurrent", (void *)+[](EGLDisplay display,
      EGLSurface draw,
      EGLSurface read,
      EGLContext context) {
      Log::warn("Launcher", "EGL stub %s called", "eglMakeCurrent");
      return EGL_TRUE;
    });
    hybris_hook("eglDestroyContext", (void *)(void (*)())[]() {
    });
    hybris_hook("eglTerminate", (void *)(void (*)())[]() {
    });
    hybris_hook("eglGetDisplay", (void *)+[](NativeDisplayType native_display) {
      return 1; 
    });
    hybris_hook("eglInitialize", (void *)+[](void* display, uint32_t * major, uint32_t * minor) {
      return EGL_TRUE;
    });
    hybris_hook("eglQuerySurface", (void *) + [](void* dpy, EGLSurface surface, EGLint attribute, EGLint *value) {
      int dummy;
      switch (attribute)
      {
      case EGL_WIDTH:
          window->getWindowSize(*value, dummy);
          break;
      case EGL_HEIGHT:
          window->getWindowSize(dummy, *value);
          break;
      default:
          return EGL_FALSE;
      }
      return EGL_TRUE;
    });
    hybris_hook("eglSwapInterval", (void *)+[](EGLDisplay display, EGLint interval) {
        window->swapInterval(interval);
      return EGL_TRUE;
    });
    hybris_hook("eglQueryString", (void *)+[](void* display, int32_t name) {
        return 0;
    });
    hybris_hook("eglGetProcAddress", ((void*)+[](char* ch)->void*{
      auto hook = eglfuncs[ch];
      return hook ? hook : ((void* (*)(const char*))windowManager->getProcAddrFunc())(ch);
    }));
    hybris_hook("eglGetCurrentContext", (void*) + []() -> int {
      return 0;
    });
    MinecraftUtils::setupGLES2Symbols((void* (*)(const char*)) windowManager->getProcAddrFunc());
#ifdef USE_ARMHF_SUPPORT
    ArmhfSupport::install();
#endif

    struct Looper {
      int fd;
      int indent;
      void * data;
      int indent2;
      void * data2;
    };
    static Looper looper;
    hybris_hook("ALooper_pollAll", (void *)+[](  int timeoutMillis,
    int *outFd,
    int *outEvents,
    void **outData) {
      fd_set rfds;
      struct timeval tv;
      int retval;

      /* Watch stdin (fd 0) to see when it has input. */

      FD_ZERO(&rfds);
      FD_SET(looper.fd, &rfds);

      tv.tv_sec = 0;
      tv.tv_usec = 0;

      retval = select(looper.fd + 1, &rfds, NULL, NULL, &tv);
      /* Don't rely on the value of tv now! */

      if (retval == -1)
          perror("select()");
      else if (retval) {
          // printf("Data is available now.\n");
          *outData = looper.data;
          return looper.indent;
          /* FD_ISSET(0, &rfds) will be true. */
      }

      window->pollEvents();

      return -3;
    });
    hybris_hook("ALooper_addFd", (void *)+[](  void *loopere ,
      int fd,
      int ident,
      int events,
      int(* callback)(int fd, int events, void *data),
      void *data) {
      looper.fd = fd;
      looper.indent = ident;
      looper.data = data;
      return 1;
    });
    hybris_hook("AInputQueue_attachLooper", (void *)+[](  void *queue,
    void *looper2,
    int ident,
    void* callback,
    void *data) {
      looper.indent2 = ident;
      looper.data2 = data;
    });

    // Hook AppPlatform function directly (functions are too small for a jump instruction)
    // static vtable replace isn't working
    auto hide = (void*) + [](void* t) {
        window->setCursorDisabled(true);
    };
    auto show = (void*) + [](void* t) {
        window->setCursorDisabled(false);
    };

    // hybris_hook("uncompress", (void *)(void (*)())[]() {
    // });

    // OpenSLESPatch::install();

    // Hack pthread to run mainthread on the main function #macoscacoa support
    static std::atomic_bool uithread_started;
    uithread_started = false;
    static void *(*main_routine)(void*) = nullptr;
    static void *main_arg = nullptr;
    static pthread_t mainthread = pthread_self();
    static int (*my_pthread_create)(pthread_t *thread, const pthread_attr_t *__attr,
                             void *(*start_routine)(void*), void *arg) = 0;
    my_pthread_create = (int (*)(pthread_t *thread, const pthread_attr_t *__attr,
                             void *(*start_routine)(void*), void *arg))syms["pthread_create"];
    hybris_hook("pthread_create", (void*) + [](pthread_t *thread, const pthread_attr_t *__attr,
        void *(*start_routine)(void*), void *arg) {
        if(uithread_started.load()) {
          return my_pthread_create(thread, __attr, start_routine, arg);
        } else {
          uithread_started = true;
          *thread = mainthread;
          main_routine = start_routine;
          main_arg = arg;
          return 0;
        }
      }
    );

    // static auto my_fopen = (void*(*)(const char *filename, const char *mode))get_hooked_symbol("fopen");
    // hybris_hook("fopen", (void*) + [](const char *filename, const char *mode) {
    //   if(!strcmp(filename, "/data/data/com.mojang.minecraftpe/games/com.mojang/minecraftpe/external_servers.txt")) {
    //       return my_fopen((PathHelper::getPrimaryDataDirectory() + (filename + 34)).data(), mode);
    //   } else {
    //     return my_fopen(filename, mode);
    //   }
    // });
    // For 0.11 or lower
    // hybris_hook("ftime", (void*)&ftime);
    // OpenSLESPatch::install();

    // hybris_hook("_Znwj", (void*)(void *(*)(size_t)) ::operator new);
    // hybris_hook("_ZdlPv", (void*)(void (*)(void *)) ::operator delete);
    // static int __page_size = 4096;
    // hybris_hook("__page_size", (void*)&__page_size);
    hybris_hook("fdatasync", (void*)&fdatasync);
    hybris_hook("pthread_setname_np", (void*)&pthread_setname_np);
  
    

    #ifdef __i386__
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_RESTART;
    act.sa_sigaction = [](int, siginfo_t *si, void *ptr) {
      *(char*)si->si_addr = 0x90;
      *((char*)si->si_addr + 1) = 0x90;
      Log::warn("Minecraft BUG", "SIGFPE Experimental patch applied, the Game will continue now");
    };
    sigaction(SIGFPE, &act, NULL);
    #endif

    Log::trace("Launcher", "Loading Minecraft library");
    // loadlegacyCompat();
    // linker::init();
    // linker::update_LD_LIBRARY_PATH((PathHelper::getGameDir() + "/lib/" + PathHelper::getAbiDir()).data());
    Log::trace("Launcher", "Loading hybris libraries");
    linker::init();
    linker::update_LD_LIBRARY_PATH((PathHelper::getGameDir() + "/lib/" + PathHelper::getAbiDir()).data());
    
#ifdef __arm__
    linker::load_library("ld-android.so", {});
    android_dlextinfo extinfo;
    std::vector<mcpelauncher_hook_t> hooks;
    // auto denylist = { "atof", "strtod", "strtof", "strtold", "strtold_l", "strtof_l", "ecvt", "fcvt", "gcvt" };
    for (auto && entry : syms) {
        // if (std::find(std::begin(denylist), std::end(denylist), entry.first) == std::end(denylist)) {
          hooks.emplace_back(mcpelauncher_hook_t{ entry.first.data(), entry.second });
        // }
    }
    hooks.emplace_back(mcpelauncher_hook_t{ nullptr, nullptr });
    extinfo.flags = ANDROID_DLEXT_MCPELAUNCHER_HOOKS;
    extinfo.mcpelauncher_hooks = hooks.data();
    auto libc = linker::dlopen_ext(PathHelper::findDataFile("libs/hybris/libc.so").c_str(), 0, &extinfo);
    // linker::load_library("libc.so", syms);
    // linker::dlopen("libm.so", 0);
    // auto libm = linker::dlopen_ext(PathHelper::findDataFile("libs/hybris/libm.so").c_str(), 0, &extinfo);
    auto libm = linker::dlopen(PathHelper::findDataFile("libs/hybris/libm.so").c_str(), 0);
#else
    linker::load_library("libc.so", syms);
    MinecraftUtils::loadLibM();
#endif
    auto libcxx = linker::dlopen("libc++_shared.so", 0);
    linker::load_library("libandroid.so", {});
    linker::load_library("libEGL.so", {});
    if (!disableFmod) {
      MinecraftUtils::loadFMod();
#ifdef __arm__
      hybris_hook("_ZN4FMOD14ChannelControl9setVolumeEf", (void*)&FMOD_ChannelControl_setVolume);
      hybris_hook("_ZN4FMOD14ChannelControl8setPitchEf", (void*)&FMOD_ChannelControl_setPitch); 
      hybris_hook("_ZN4FMOD6System13set3DSettingsEfff", (void*)&FMOD_System_set3DSettings); 
      hybris_hook("_ZN4FMOD5Sound19set3DMinMaxDistanceEff", (void*)&FMOD_Sound_set3DMinMaxDistance); 
      hybris_hook("_ZN4FMOD14ChannelControl12addFadePointEyf", (void*)&FMOD_ChannelControl_addFadePoint);
#endif
    }

    void * handle = MinecraftUtils::loadMinecraftLib();
    if (!handle) {
      Log::error("Launcher", "Failed to load Minecraft library, please reinstall");
      return 51;
    }
    minecraft_symbols_init(handle);
    MinecraftVersion::major = SharedConstants::MajorVersion ? *SharedConstants::MajorVersion : 1;
    MinecraftVersion::minor = SharedConstants::MinorVersion ? *SharedConstants::MinorVersion : 13;
    MinecraftVersion::patch = SharedConstants::PatchVersion ? *SharedConstants::PatchVersion : 0;
    MinecraftVersion::revision = SharedConstants::RevisionVersion ? *SharedConstants::RevisionVersion : 9;
    // minecraft_get_version(&major, &minor, &patch, &revision);
    Log::info("Launcher", "Loaded Minecraft library");
    Log::debug("Launcher", "Minecraft is at offset 0x%x", MinecraftUtils::getLibraryBase(handle));

    void** vt = &((void**) linker::dlsym(handle, "_ZTV21AppPlatform_android23"))[2];
    void** vta = &((void**) linker::dlsym(handle, "_ZTV19AppPlatform_android"))[2];
    auto myVtableSize = PatchUtils::getVtableSize(vta);
    Log::trace("AppPlatform", "Vtable size = %u", myVtableSize);

    PatchUtils::VtableReplaceHelper vtr (handle, vt, vta);
    vtr.replace("_ZN11AppPlatform16hideMousePointerEv", hide);
    vtr.replace("_ZN11AppPlatform16showMousePointerEv", show);
    auto client = linker::dlsym(handle, "_ZN3web4http6client7details35verify_cert_chain_platform_specificERN5boost4asio3ssl14verify_contextERKSs");
    if(client) {
        PatchUtils::patchCallInstruction(client, (void*) + []() {
            // Log::trace("web::http::client", "verify_cert_chain_platform_specific stub called");
            return true;
        }, true);
    }
    ModLoader modLoader;
    modLoader.loadModsFromDirectory(PathHelper::getPrimaryDataDirectory() + "mods/");
    // MinecraftUtils::initSymbolBindings(handle);
    HbuiPatch::install(handle);
    ANativeActivity activity;
    memset(&activity, 0, sizeof(ANativeActivity));
    activity.internalDataPath = "./idata/";
    activity.externalDataPath = "./edata/";
    activity.obbPath = "./oob/";
    activity.sdkVersion = 28;
    jnivm::VM vm;
    activity.vm = vm.GetJavaVM();
    // activity.assetManager = (struct AAssetManager*)23;
    ANativeActivityCallbacks callbacks;
    memset(&callbacks, 0, sizeof(ANativeActivityCallbacks));
    activity.callbacks = &callbacks;
    activity.vm->GetEnv(&(void*&)activity.env, 0);
    jnienv = activity.env;
    // vm.SetReserved3(handle);
    // Avoid using cd by hand
    chdir((PathHelper::getGameDir() + "/assets").data());
    // Initialize fake java interop
    auto JNI_OnLoad = (jint (*)(JavaVM* vm, void* reserved))linker::dlsym(handle, "JNI_OnLoad");
    if (JNI_OnLoad) JNI_OnLoad(activity.vm, 0);
    auto mainactivity = std::make_shared<com::mojang::minecraftpe::MainActivity>(handle);
    auto cl = (java::lang::Class*)activity.env->FindClass("com/mojang/minecraftpe/MainActivity");
    mainactivity->clazz = { cl->shared_from_this(), cl };//std::make_shared<jnivm::Object><void> { .cl = activity.env->FindClass("com/mojang/minecraftpe/MainActivity"), .value = new int() };
    mainactivity->window = window;
    activity.clazz = mainactivity.get();
    WindowCallbacks windowCallbacks (*window, activity);
    windowCallbacks.handle = handle;
    windowCallbacks.vm = &vm;
    windowCallbacks.registerCallbacks();
    std::thread([&,ANativeActivity_onCreate = (ANativeActivity_createFunc*)linker::dlsym(handle, "ANativeActivity_onCreate"), registerthis = (void(*)(JNIEnv * env, void*))linker::dlsym(handle, "Java_com_mojang_minecraftpe_MainActivity_nativeRegisterThis")]() {
      ANativeActivity_onCreate(&activity, 0, 0);
      if (registerthis) registerthis(jnienv, activity.clazz);
      activity.callbacks->onInputQueueCreated(&activity, (AInputQueue*)2);
      activity.callbacks->onNativeWindowCreated(&activity, (ANativeWindow*)window.get());
      activity.callbacks->onStart(&activity);
      // For 0.14 or lower
      activity.callbacks->onResume(&activity);
    }).detach();
    while (!uithread_started.load()) std::this_thread::sleep_for(std::chrono::milliseconds(100));
    window->prepareRunLoop();
  #ifndef PROTOTYPE_JNI_BINDING
    InitJNIBinding(vm.GetEnv().get());
    auto env = vm.GetEnv();
    auto StoreFactory_ = env->GetClass("com/mojang/minecraftpe/store/StoreFactory");
    StoreFactory_->Hook(env.get(), "createGooglePlayStore", [callback = (void(*)(JNIEnv*,jnivm::com::mojang::minecraftpe::store::NativeStoreListener*, jlong, jboolean)) linker::dlsym(handle, "Java_com_mojang_minecraftpe_store_NativeStoreListener_onStoreInitialized")](jnivm::ENV* env, jnivm::Class* clazz, std::shared_ptr<jnivm::String> arg0, std::shared_ptr<jnivm::com::mojang::minecraftpe::store::StoreListener> arg1) -> std::shared_ptr<jnivm::com::mojang::minecraftpe::store::Store> {
      auto store = std::make_shared<jnivm::com::mojang::minecraftpe::store::Store>();
      callback(&env->env, (jnivm::com::mojang::minecraftpe::store::NativeStoreListener*)arg1.get(), ((jnivm::com::mojang::minecraftpe::store::NativeStoreListener*)arg1.get())->nativestore, true);
      return store;
    });
  #else
    auto vm2_ = &vm;
    {
      auto vm = vm2_;
      auto MainActivity_ = vm->GetEnv()->GetClass("com/mojang/minecraftpe/MainActivity");
    
    // mainActivity->clazz = MainActivity_;


    MainActivity_->HookInstanceFunction(vm->GetEnv().get(), "initializeXboxLive", [handle](jnivm::ENV*env, jnivm::Object*obj, jlong a, jlong b) -> void {
      
        ((void(*)(JNIEnv*, jnivm::Object*obj, jlong, jlong))linker::dlsym(handle, "Java_com_mojang_minecraftpe_MainActivity_nativeInitializeXboxLive"))(&env->env, obj, a, b);
    });

    MainActivity_->HookInstanceFunction(vm->GetEnv().get(), "createUUID", [](jnivm::ENV*env, jnivm::Object*obj) -> std::shared_ptr<jnivm::String> {
        return std::make_shared<jnivm::String>("daa78df1-373a-444d-9b1d-4c71a14bb559");
    });
    struct ClassLoader : jnivm::Object { };
    auto ClassLoader_ = vm->GetEnv()->GetClass<ClassLoader>("java/lang/ClassLoader");
    MainActivity_->HookInstanceFunction(vm->GetEnv().get(), "getClassLoader", [](jnivm::ENV*env, jnivm::Object*obj) -> std::shared_ptr<ClassLoader> {
        return std::make_shared<ClassLoader>();
    });
// OLD BEGIN
    auto env = vm->GetEnv();
    MainActivity_->Hook(env.get(), "hasWriteExternalStoragePermission", [](jnivm::ENV*env, jnivm::Object*obj) -> jboolean {
      return 1;
    });
    MainActivity_->Hook(env.get(), "isNetworkEnabled", [](jnivm::ENV*env, jnivm::Object*obj, jboolean b) -> jboolean {
      printf("isNetworkEnabled %d\n", (int)b);
      return 1;
    });

    MainActivity_->HookInstanceFunction(env.get(), "launchUri", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<jnivm::String> uri) {
      Log::trace("Launch URI", "%s", uri->data());
    });
    // MainActivity_->HookInstanceFunction(env.get(), "tick", [](jnivm::ENV*env, jnivm::Object*obj) {
    //   if(window)
    //   window->swapBuffers();
    // });
    struct StoreListener : jnivm::Object {
        jlong nstorelisterner;
    };
    struct NativeStoreListener : StoreListener {
    };
    auto NativeStoreListener_ = env->GetClass<NativeStoreListener>("com/mojang/minecraftpe/store/NativeStoreListener");
    NativeStoreListener_->Hook(env.get(), "<init>", [](jnivm::ENV*env, jnivm::Class*cl, jlong arg0) -> std::shared_ptr<NativeStoreListener> {
      auto storel = std::make_shared<NativeStoreListener>();
      storel->nstorelisterner = arg0;
      return storel;
    });
    // Show Gamepad Options
	  auto Build = env->GetClass("android/os/Build$VERSION");
    Build->HookGetterFunction(env.get(), "SDK_INT", [](jnivm::ENV*env, jnivm::Class*cl) -> jint {
      return 28;
    });
    // Make pictures loading, advance apilevel
    MainActivity_->HookInstanceFunction(env.get(), "getAndroidVersion", [](jnivm::ENV*env, jnivm::Object*obj) -> jint {
      return 28;
    });
    auto StoreListener_ = env->GetClass<StoreListener>("com/mojang/minecraftpe/store/StoreListener");
    struct Store : jnivm::Object {
    };
    auto Store_ = env->GetClass<Store>("com/mojang/minecraftpe/store/Store");
    Store_->HookInstanceFunction(env.get(), "receivedLicenseResponse", [](jnivm::ENV* env, jnivm::Object* store) -> jboolean {
      return true;
    });
    Store_->HookInstanceFunction(env.get(), "hasVerifiedLicense", [](jnivm::ENV* env, jnivm::Object* store) -> jboolean {
      return true;
    });
    struct StoreFactory : jnivm::Object {
    };
    auto StoreFactory_ = env->GetClass<StoreFactory>("com/mojang/minecraftpe/store/StoreFactory");
    StoreFactory_->Hook(env.get(), "createGooglePlayStore", [callback = (void(*)(JNIEnv*,StoreListener*, jlong, jboolean)) linker::dlsym(handle, "Java_com_mojang_minecraftpe_store_NativeStoreListener_onStoreInitialized")](jnivm::ENV* env, jnivm::Class* clazz, std::shared_ptr<jnivm::String> arg0, std::shared_ptr<StoreListener> arg1) -> std::shared_ptr<Store> {
      auto store = std::make_shared<Store>();
      callback(&env->env, arg1.get(), arg1->nstorelisterner, true);
      return store;
    });
// OLD END
    ClassLoader_->HookInstanceFunction(vm->GetEnv().get(), "loadClass", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<jnivm::String> str) {
        return env->GetClass(str->data());
    });
    struct Context : jnivm::Object { };
    auto Context_ = vm->GetEnv()->GetClass<Context>("android/content/Context");
    struct Intent : jnivm::Object { };
    auto Intent_ = vm->GetEnv()->GetClass<Intent>("android/content/Intent");
    Context_->HookInstanceFunction(vm->GetEnv().get(), "startActivity", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<Intent> in) {

    });
    struct NativeActivity : jnivm::Object { };
    auto NativeActivity_ = vm->GetEnv()->GetClass<NativeActivity>("android/app/NativeActivity");
    NativeActivity_->HookInstanceFunction(vm->GetEnv().get(), "getApplicationContext", [](jnivm::ENV*env, jnivm::Object*obj) {
        return std::make_shared<Context>();
    });

    struct Interop : jnivm::Object {};
    auto Interop_ = vm->GetEnv()->GetClass<Interop>("com/microsoft/xbox/idp/interop/Interop");
    Interop_->HookInstanceFunction(vm->GetEnv().get(), "GetLocalStoragePath", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<Context> ctx) {
        return std::make_shared<jnivm::String>("../data");
    });
    Interop_->HookInstanceFunction(vm->GetEnv().get(), "ReadConfigFile", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<Context> ctx) {
        return std::make_shared<jnivm::String>("{}");
        //return std::make_shared<jnivm::String>("");
    });

    // Ignore Certificate Validation jni api
    struct ByteArrayInputStream : jnivm::Object {
        std::shared_ptr<jnivm::Array<jbyte>> s;
    };
    auto ByteArrayInputStream_ = vm->GetEnv()->GetClass<ByteArrayInputStream>("java/io/ByteArrayInputStream");
    ByteArrayInputStream_->Hook(vm->GetEnv().get(), "<init>", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<jnivm::Array<jbyte>> s) {
        auto factory = std::make_shared<ByteArrayInputStream>();
        factory->s = s;
        return factory;
    });

    struct CertificateFactory : jnivm::Object {
        std::shared_ptr<jnivm::String> s;
    };
    auto CertificateFactory_ = vm->GetEnv()->GetClass<CertificateFactory>("java/security/cert/CertificateFactory");
    CertificateFactory_->Hook(vm->GetEnv().get(), "getInstance", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<jnivm::String> s) {
        auto factory = std::make_shared<CertificateFactory>();
        factory->s = s;
        return factory;
    });
    struct InputStream : jnivm::Object {
    };
    auto InputStream_ = vm->GetEnv()->GetClass<InputStream>("java/io/InputStream");
    struct Certificate : jnivm::Object {
    };
    struct X509Certificate : Certificate {};
    auto Certificate_ = vm->GetEnv()->GetClass<Certificate>("java/security/cert/Certificate");
    CertificateFactory_->HookInstanceFunction(vm->GetEnv().get(), "generateCertificate", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<InputStream> s) -> std::shared_ptr<Certificate> {
        auto factory = std::make_shared<X509Certificate>();
        return factory;
    });

    struct TrustManagerFactory : jnivm::Object {
        std::shared_ptr<jnivm::String> s;
    };
    auto TrustManagerFactory_ = vm->GetEnv()->GetClass<TrustManagerFactory>("javax/net/ssl/TrustManagerFactory");
    TrustManagerFactory_->Hook(vm->GetEnv().get(), "getInstance", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<jnivm::String> s) {
        auto factory = std::make_shared<TrustManagerFactory>();
        factory->s = s;
        return factory;
    });
    struct TrustManager : jnivm::Object {};
    auto TrustManager_ = vm->GetEnv()->GetClass<TrustManager>("javax/net/ssl/TrustManager");
    TrustManagerFactory_->HookInstanceFunction(vm->GetEnv().get(), "getTrustManagers", [](jnivm::ENV*env, jnivm::Object*obj) {
        auto factory = std::make_shared<jnivm::Array<std::shared_ptr<TrustManager>>>(new std::shared_ptr<TrustManager>[1] { std::make_shared<TrustManager>() }, 1);
        return factory;
    });

    struct StrictHostnameVerifier : jnivm::Object {};
    auto StrictHostnameVerifier_ = vm->GetEnv()->GetClass<StrictHostnameVerifier>("org/apache/http/conn/ssl/StrictHostnameVerifier");
    StrictHostnameVerifier_->Hook(vm->GetEnv().get(), "<init>", [](jnivm::ENV*env, jnivm::Object*obj) {
        auto factory = std::make_shared<StrictHostnameVerifier>();
        return factory;
    });
    auto X509Certificate_ = vm->GetEnv()->GetClass<X509Certificate>("org/apache/http/conn/ssl/java/security/cert/X509Certificate");
    StrictHostnameVerifier_->HookInstanceFunction(vm->GetEnv().get(), "verify", [](jnivm::ENV*env, jnivm::Object*obj, std::shared_ptr<jnivm::String> s, std::shared_ptr<X509Certificate> cert) {

    });
    }
#endif
    auto res = main_routine(main_arg);
    vm.GenerateClassDump("/home/christopher/minecraft-linux/d.txt");
    _Exit(0);
}

void printVersionInfo() {
    printf("mcpelauncher-client %s / manifest %s\n", CLIENT_GIT_COMMIT_HASH, MANIFEST_GIT_COMMIT_HASH);
#ifdef __i386__
    CpuId cpuid;
    printf("CPU: %s %s\n", cpuid.getManufacturer(), cpuid.getBrandString());
    printf("SSSE3 support: %s\n", cpuid.queryFeatureFlag(CpuId::FeatureFlag::SSSE3) ? "YES" : "NO");
#endif
    auto windowManager = GameWindowManager::getManager();
    GraphicsApi graphicsApi = GraphicsApi::OPENGL;
    auto window = windowManager->createWindow("mcpelauncher", 32, 32, graphicsApi);
    auto glGetString = (const char* (*)(int)) windowManager->getProcAddrFunc()("glGetString");
    printf("GL Vendor: %s\n", glGetString(0x1F00 /* GL_VENDOR */));
    printf("GL Renderer: %s\n", glGetString(0x1F01 /* GL_RENDERER */));
    printf("GL Version: %s\n", glGetString(0x1F02 /* GL_VERSION */));
    printf("MSA daemon path: %s\n", XboxLiveHelper::findMsa().c_str());
}
