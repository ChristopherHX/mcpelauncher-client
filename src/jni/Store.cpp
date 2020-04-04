#include "../JNIBinding.h"

// com::mojang::minecraftpe::store::NativeStoreListener::NativeStoreListener(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jlong arg0) {
//     nativestore = arg0;
// }

std::shared_ptr<jnivm::com::mojang::minecraftpe::store::Store> com::mojang::minecraftpe::store::StoreFactory::createGooglePlayStore(jnivm::ENV* env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::com::mojang::minecraftpe::store::NativeStoreListener> arg1) {
    auto store = std::make_shared<jnivm::com::mojang::minecraftpe::store::Store>();
    store->clazz = env->GetClass("com/mojang/minecraftpe/store/Store");
    // auto callback = (void(*)(jnivm::ENV*,jnivm::com::mojang::minecraftpe::store::StoreListener*, jlong, jboolean)) hybris_dlsym(env->functions->reserved3, "Java_com_mojang_minecraftpe_store_NativeStoreListener_onStoreInitialized");
    // callback(env, arg1, nativestore, true);
    return store;
}

std::shared_ptr<jnivm::com::mojang::minecraftpe::store::Store> com::mojang::minecraftpe::store::StoreFactory::createAmazonAppStore(jnivm::ENV* env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::com::mojang::minecraftpe::store::NativeStoreListener> arg0, jboolean arg1) {
    auto store = std::make_shared<jnivm::com::mojang::minecraftpe::store::Store>();
    store->clazz = env->GetClass("com/mojang/minecraftpe/store/Store");
    // auto callback = (void(*)(jnivm::ENV*,jnivm::com::mojang::minecraftpe::store::StoreListener*, jlong, jboolean)) hybris_dlsym(env->functions->reserved3, "Java_com_mojang_minecraftpe_store_NativeStoreListener_onStoreInitialized");
    // callback(env, arg0, nativestore, true);
    return store;
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::store::Store::getStoreId(jnivm::ENV* env) {
    return std::make_shared<jnivm::java::lang::String>("android.googleplay");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::store::Store::getProductSkuPrefix(jnivm::ENV* env) {
    return std::make_shared<jnivm::java::lang::String>("com.linux");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::store::Store::getRealmsSkuPrefix(jnivm::ENV* env) {
    return std::make_shared<jnivm::java::lang::String>("com.linux");
}

jboolean com::mojang::minecraftpe::store::Store::hasVerifiedLicense(jnivm::ENV* env) {
    return true;
}

std::shared_ptr<jnivm::com::mojang::minecraftpe::store::ExtraLicenseResponseData> com::mojang::minecraftpe::store::Store::getExtraLicenseData(jnivm::ENV* env) {
    return std::make_shared<jnivm::com::mojang::minecraftpe::store::ExtraLicenseResponseData>();
}

jboolean com::mojang::minecraftpe::store::Store::receivedLicenseResponse(jnivm::ENV* env) {
    return true;
}

void com::mojang::minecraftpe::store::Store::queryProducts(jnivm::ENV* env, jnivm::Array<std::shared_ptr<jnivm::java::lang::String>>* arg0) {
    
}

void com::mojang::minecraftpe::store::Store::purchase(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0, jboolean arg1, std::shared_ptr<jnivm::java::lang::String> arg2) {
    
}

void com::mojang::minecraftpe::store::Store::acknowledgePurchase(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::java::lang::String> arg1) {
    
}

void com::mojang::minecraftpe::store::Store::queryPurchases(jnivm::ENV* env) {
    
}

void com::mojang::minecraftpe::store::Store::destructor(jnivm::ENV* env) {
    
}

jlong com::mojang::minecraftpe::store::ExtraLicenseResponseData::getValidationTime(jnivm::ENV* env) {
    return 0;
}

jlong com::mojang::minecraftpe::store::ExtraLicenseResponseData::getRetryUntilTime(jnivm::ENV* env) {
    return 0;    
}

jlong com::mojang::minecraftpe::store::ExtraLicenseResponseData::getRetryAttempts(jnivm::ENV* env) {
    return 0;    
}