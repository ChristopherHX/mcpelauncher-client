#include "../JNIBinding.h"

// jlong nativestore = 0;

com::mojang::minecraftpe::store::NativeStoreListener::NativeStoreListener(ENV *env, jnivm::java::lang::Class* clazz, jlong arg0) {
    nativestore = arg0;
}

std::shared_ptr<jnivm::com::mojang::minecraftpe::store::Store> com::mojang::minecraftpe::store::StoreFactory::createGooglePlayStore(ENV *env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::com::mojang::minecraftpe::store::StoreListener> arg1) {
    auto store = std::make_shared<jnivm::com::mojang::minecraftpe::store::Store>();
    auto cl = (jnivm::java::lang::Class*)env->env.FindClass("com/mojang/minecraftpe/store/Store");
    store->clazz = { cl->shared_from_this(), cl};
    // TODO
    // auto callback = (void(*)(JNIEnv*,std::shared_ptr<jnivm::com::mojang::minecraftpe::store::StoreListener>, jlong, jboolean)) hybris_dlsym(env->functions->reserved3, "Java_com_mojang_minecraftpe_store_NativeStoreListener_onStoreInitialized");
    // callback(&env->env, arg1, nativestore, true);
    return store;
}

std::shared_ptr<jnivm::com::mojang::minecraftpe::store::Store> com::mojang::minecraftpe::store::StoreFactory::createAmazonAppStore(ENV *env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::com::mojang::minecraftpe::store::StoreListener> arg0, jboolean arg1) {
    auto store = std::make_shared<jnivm::com::mojang::minecraftpe::store::Store>();
    auto cl = (jnivm::java::lang::Class*)env->env.FindClass("com/mojang/minecraftpe/store/Store");
    store->clazz = { cl->shared_from_this(), cl};
    // TODO
    // auto callback = (void(*)(JNIEnv*,std::shared_ptr<jnivm::com::mojang::minecraftpe::store::StoreListener>, jlong, jboolean)) hybris_dlsym(env->functions->reserved3, "Java_com_mojang_minecraftpe_store_NativeStoreListener_onStoreInitialized");
    // callback(&env->env, arg0, nativestore, true);
    return store;
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::store::Store::getStoreId(ENV *env) {
    return std::make_shared<jnivm::java::lang::String>("android.googleplay");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::store::Store::getProductSkuPrefix(ENV *env) {
    return std::make_shared<jnivm::java::lang::String>("com.linux");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::store::Store::getRealmsSkuPrefix(ENV *env) {
    return std::make_shared<jnivm::java::lang::String>("com.linux");
}

jboolean com::mojang::minecraftpe::store::Store::hasVerifiedLicense(ENV *env) {
    return true;
}

std::shared_ptr<jnivm::com::mojang::minecraftpe::store::ExtraLicenseResponseData> com::mojang::minecraftpe::store::Store::getExtraLicenseData(ENV *env) {
    return 0;
}

jboolean com::mojang::minecraftpe::store::Store::receivedLicenseResponse(ENV *env) {
    return true;
}

void com::mojang::minecraftpe::store::Store::queryProducts(ENV *env, std::shared_ptr<jnivm::Array<std::shared_ptr<jnivm::java::lang::String>>> arg0) {
    
}

void com::mojang::minecraftpe::store::Store::purchase(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0, jboolean arg1, std::shared_ptr<jnivm::java::lang::String> arg2) {
    
}

void com::mojang::minecraftpe::store::Store::acknowledgePurchase(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::java::lang::String> arg1) {
    
}

void com::mojang::minecraftpe::store::Store::queryPurchases(ENV *env) {
    
}

void com::mojang::minecraftpe::store::Store::destructor(ENV *env) {
    
}

jlong com::mojang::minecraftpe::store::ExtraLicenseResponseData::getValidationTime(ENV *env) {
    return 0;
}

jlong com::mojang::minecraftpe::store::ExtraLicenseResponseData::getRetryUntilTime(ENV *env) {
    return 0;    
}

jlong com::mojang::minecraftpe::store::ExtraLicenseResponseData::getRetryAttempts(ENV *env) {
    return 0;    
}