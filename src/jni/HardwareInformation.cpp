#include "../JNIBinding.h"

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getDeviceModelName(ENV *env, jnivm::java::lang::Class* clazz) {
    return std::make_shared<jnivm::java::lang::String>("Android");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getAndroidVersion(ENV *env, jnivm::java::lang::Class* clazz) {
    return std::make_shared<jnivm::java::lang::String>("");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getCPUType(ENV *env, jnivm::java::lang::Class* clazz) {
    return std::make_shared<jnivm::java::lang::String>("");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getCPUName(ENV *env, jnivm::java::lang::Class* clazz) {
    return std::make_shared<jnivm::java::lang::String>("");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getCPUFeatures(ENV *env, jnivm::java::lang::Class* clazz) {
    return std::make_shared<jnivm::java::lang::String>("");
}

jint com::mojang::minecraftpe::HardwareInformation::getNumCores(ENV *env, jnivm::java::lang::Class* clazz) {
    return 4;
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getSecureId(ENV *env) {
    return std::make_shared<jnivm::java::lang::String>("0000000000000000");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getSerialNumber(ENV *env, jnivm::java::lang::Class* clazz) {
    return std::make_shared<jnivm::java::lang::String>("");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getBoard(ENV *env, jnivm::java::lang::Class* clazz) {
    return std::make_shared<jnivm::java::lang::String>("Android");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::HardwareInformation::getInstallerPackageName(ENV *env) {
    return std::make_shared<jnivm::java::lang::String>("com.mojang.minecraftpe");
}

jint com::mojang::minecraftpe::HardwareInformation::getSignaturesHashCode(ENV *env) {
    return 0xccccccc;
}

jboolean com::mojang::minecraftpe::HardwareInformation::getIsRooted(ENV *env) {
    return false;
}