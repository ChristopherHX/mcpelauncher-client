#include "../JNIBinding.h"

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getDeviceModelName(jnivm::ENV* env, jnivm::java::lang::Class* clazz) {
    return std::make_shared<jnivm::java::lang::String>("Android");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getAndroidVersion(jnivm::ENV* env, jnivm::java::lang::Class* clazz) {
    return std::make_shared<jnivm::java::lang::String>("");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getCPUType(jnivm::ENV* env, jnivm::java::lang::Class* clazz) {
    return std::make_shared<jnivm::java::lang::String>("");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getCPUName(jnivm::ENV* env, jnivm::java::lang::Class* clazz) {
    return std::make_shared<jnivm::java::lang::String>("");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getCPUFeatures(jnivm::ENV* env, jnivm::java::lang::Class* clazz) {
    return std::make_shared<jnivm::java::lang::String>("");
}

jint com::mojang::minecraftpe::HardwareInformation::getNumCores(jnivm::ENV* env, jnivm::java::lang::Class* clazz) {
    return 4;
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getSecureId(jnivm::ENV* env) {
    return std::make_shared<jnivm::java::lang::String>("0000000000000000");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getSerialNumber(jnivm::ENV* env, jnivm::java::lang::Class* clazz) {
    return std::make_shared<jnivm::java::lang::String>("");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getBoard(jnivm::ENV* env, jnivm::java::lang::Class* clazz) {
    return std::make_shared<jnivm::java::lang::String>("Android");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getInstallerPackageName(jnivm::ENV* env) {
    return std::make_shared<jnivm::java::lang::String>("com.mojang.minecraftpe");
}

jint com::mojang::minecraftpe::HardwareInformation::getSignaturesHashCode(jnivm::ENV* env) {
    return 0xccccccc;
}

jboolean com::mojang::minecraftpe::HardwareInformation::getIsRooted(jnivm::ENV* env) {
    return false;
}

// Entry points for jnivm

extern "C" std::shared_ptr<jnivm::java::lang::String> jnivm_com_mojang_minecraftpe_HardwareInformation_getDeviceModelName(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getDeviceModelName(env, clazz);
}
extern "C" std::shared_ptr<jnivm::java::lang::String> jnivm_com_mojang_minecraftpe_HardwareInformation_getAndroidVersion(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getAndroidVersion(env, clazz);
}
extern "C" std::shared_ptr<jnivm::java::lang::String> jnivm_com_mojang_minecraftpe_HardwareInformation_getCPUType(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getCPUType(env, clazz);
}
extern "C" std::shared_ptr<jnivm::java::lang::String> jnivm_com_mojang_minecraftpe_HardwareInformation_getCPUName(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getCPUName(env, clazz);
}
extern "C" std::shared_ptr<jnivm::java::lang::String> jnivm_com_mojang_minecraftpe_HardwareInformation_getCPUFeatures(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getCPUFeatures(env, clazz);
}
extern "C" jint jnivm_com_mojang_minecraftpe_HardwareInformation_getNumCores(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getNumCores(env, clazz);
}
extern "C" std::shared_ptr<jnivm::java::lang::String> jnivm_com_mojang_minecraftpe_HardwareInformation_getSecureId(jnivm::ENV* env, std::shared_ptr<jnivm::com::mojang::minecraftpe::HardwareInformation> obj, jvalue* values) {
    return obj->getSecureId(env);
}
extern "C" std::shared_ptr<jnivm::java::lang::String> jnivm_com_mojang_minecraftpe_HardwareInformation_getSerialNumber(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getSerialNumber(env, clazz);
}
extern "C" std::shared_ptr<jnivm::java::lang::String> jnivm_com_mojang_minecraftpe_HardwareInformation_getBoard(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jvalue* values) {
    return com::mojang::minecraftpe::HardwareInformation::getBoard(env, clazz);
}
extern "C" std::shared_ptr<jnivm::java::lang::String> jnivm_com_mojang_minecraftpe_HardwareInformation_getInstallerPackageName(jnivm::ENV* env, std::shared_ptr<jnivm::com::mojang::minecraftpe::HardwareInformation> obj, jvalue* values) {
    return obj->getInstallerPackageName(env);
}
extern "C" jint jnivm_com_mojang_minecraftpe_HardwareInformation_getSignaturesHashCode(jnivm::ENV* env, std::shared_ptr<jnivm::com::mojang::minecraftpe::HardwareInformation> obj, jvalue* values) {
    return obj->getSignaturesHashCode(env);
}
extern "C" jboolean jnivm_com_mojang_minecraftpe_HardwareInformation_getIsRooted(jnivm::ENV* env, std::shared_ptr<jnivm::com::mojang::minecraftpe::HardwareInformation> obj, jvalue* values) {
    return obj->getIsRooted(env);
}