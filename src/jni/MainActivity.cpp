#include "../JNIBinding.h"
#include "../utf8_util.h"
#include <mcpelauncher/linker.h>
// #include "minecraft/Keyboard.h"
#include <log.h>

jnivm::com::mojang::minecraftpe::MainActivity::MainActivity(void * handle) {
    nativeOnPickImageSuccess = (decltype(nativeOnPickImageSuccess))linker::dlsym(handle, "Java_com_mojang_minecraftpe_MainActivity_nativeOnPickImageSuccess");
    nativeOnPickImageCanceled = (decltype(nativeOnPickImageCanceled))linker::dlsym(handle, "Java_com_mojang_minecraftpe_MainActivity_nativeOnPickImageCanceled");
    nativeSetTextboxText = (decltype(nativeSetTextboxText))linker::dlsym(handle, "Java_com_mojang_minecraftpe_MainActivity_nativeSetTextboxText");
    stbi_load_from_memory = (decltype(stbi_load_from_memory))linker::dlsym(handle, "stbi_load_from_memory");
    stbi_image_free = (decltype(stbi_image_free))linker::dlsym(handle, "stbi_image_free");
    nativeWebRequestCompleted = (decltype(nativeWebRequestCompleted))linker::dlsym(handle, "Java_com_mojang_minecraftpe_MainActivity_nativeWebRequestCompleted");
    nativeInitializeXboxLive = (decltype(nativeInitializeXboxLive))linker::dlsym(handle, "Java_com_mojang_minecraftpe_MainActivity_nativeInitializeXboxLive");
    XalInitialize = (decltype(XalInitialize))linker::dlsym(handle, "XalInitialize");
    XblInitialize = (decltype(XblInitialize))linker::dlsym(handle, "XblInitialize");
}

void jnivm::com::mojang::minecraftpe::MainActivity::onKeyboardText(ENV *env, std::string const &text) {
    if (text.size() == 1 && text[0] == 8) { // backspace
        if (currentTextPositionUTF <= 0)
            return;
        currentTextPositionUTF--;
        auto deleteStart = currentTextPosition - 1;
        while (deleteStart > 0 && (currentText[deleteStart] & 0b11000000) == 0b10000000)
            deleteStart--;
        currentText.erase(currentText.begin() + deleteStart, currentText.begin() + currentTextPosition);
        currentTextPosition = deleteStart;
    } else if (text.size() == 1 && text[0] == 127) { // delete key
        if (currentTextPosition >= currentText.size())
            return;
        auto deleteEnd = currentTextPosition + 1;
        while (deleteEnd < currentText.size() && (currentText[deleteEnd] & 0b11000000) == 0b10000000)
            deleteEnd++;
        currentText.erase(currentText.begin() + currentTextPosition, currentText.begin() + deleteEnd);
    } else {
        size_t utf8length = 0;
        size_t length = 0;
        while (length < text.size() && utf8length < maxcurrentTextLength) {
            char c = text[length];
            length += UTF8Util::getCharByteSize(c);
            utf8length++;
        }
        currentText.insert(currentText.begin() + currentTextPosition, text.begin(), text.begin() + length);
        currentTextPosition += length;
        currentTextPositionUTF += utf8length;
    }
    if(nativeSetTextboxText) {
        nativeSetTextboxText(&env->env, this, env->env.NewStringUTF(currentText.data()));
    } else {
        Log::error("MainActivity", "Cannot set text with nativeSetTextboxText");
    }
    currentTextCopyPosition = currentTextPosition;
}

void jnivm::com::mojang::minecraftpe::MainActivity::onKeyboardDirectionKey(DirectionKey key) {
    if (key == DirectionKey::RightKey) {
        if (currentTextPosition >= currentText.size())
            return;
        currentTextPosition++;
        while (currentTextPosition < currentText.size() &&
               (currentText[currentTextPosition] & 0b11000000) == 0b10000000)
            currentTextPosition++;
        currentTextPositionUTF++;
    } else if (key == DirectionKey::LeftKey) {
        if (currentTextPosition <= 0)
            return;
        currentTextPosition--;
        while (currentTextPosition > 0 && (currentText[currentTextPosition] & 0b11000000) == 0b10000000)
            currentTextPosition--;
        currentTextPositionUTF--;
    } else if (key == DirectionKey::HomeKey) {
        currentTextPosition = 0;
        currentTextPositionUTF = 0;
    } else if (key == DirectionKey::EndKey) {
        currentTextPosition = currentText.size();
        currentTextPositionUTF = UTF8Util::getLength(currentText.c_str(), currentTextPosition);
    }
    if (!isShiftPressed)
        currentTextCopyPosition = currentTextPosition;
}

void jnivm::com::mojang::minecraftpe::MainActivity::onKeyboardShiftKey(bool shiftPressed) {
    isShiftPressed = shiftPressed;
}

void jnivm::com::mojang::minecraftpe::MainActivity::copyCurrentText() {
    if (currentTextCopyPosition != currentTextPosition) {
        size_t start = std::min(currentTextPosition, currentTextCopyPosition);
        size_t end = std::max(currentTextPosition, currentTextCopyPosition);
        window->setClipboardText(currentText.substr(start, end - start));
    } else {
        window->setClipboardText(currentText);
    }
}

void com::mojang::minecraftpe::MainActivity::saveScreenshot(ENV *env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::java::lang::String> arg0, jint arg1, jint arg2, std::shared_ptr<jnivm::Array<jint>> arg3) {
    
}

void com::mojang::minecraftpe::MainActivity::postScreenshotToFacebook(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0, jint arg1, jint arg2, std::shared_ptr<jnivm::Array<jint>> arg3) {
    
}

std::shared_ptr<jnivm::Array<jint>> com::mojang::minecraftpe::MainActivity::getImageData(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    if(!stbi_load_from_memory || !stbi_image_free) return 0;
    int width, height, channels;
    std::ifstream f(arg0->data());
    if(!f.is_open()) return 0;
    std::stringstream s;
    s << f.rdbuf();
    auto buf = s.str();
    auto image = stbi_load_from_memory((unsigned char*)buf.data(), buf.length(), &width, &height, &channels, 4);
    if(!image) return 0;
    auto ret = std::make_shared<jnivm::Array<jint>>(new jint[2 + width * height] { 0 }, 2 + width * height);
    ret->data[0] = width;
    ret->data[1] = height;
    
    for(int x = 0; x < width * height; x++) {
        ret->data[2 + x] = (image[x * 4 + 2]) | (image[x * 4 + 1] << 8) | (image[x * 4 + 0] << 16) | (image[x * 4 + 3] << 24);
    }
    stbi_image_free(image);
    return ret;
}

// Implementation needed for Minecraft < 1.7
std::shared_ptr<jnivm::Array<jbyte>> com::mojang::minecraftpe::MainActivity::getFileDataBytes(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    std::ifstream file(*arg0, std::ios::binary | std::ios::ate);
    if(file.is_open()) {
        auto length = file.tellg();
        auto value = new jbyte[(size_t)length + 1];
        file.seekg(0, std::ios::beg);
        file.read((char*)value, length);
        value[length] = 0;
        return std::make_shared<jnivm::Array<jbyte>>(value, (size_t)length);
    } else {
        if(!arg0->compare(0, 20, "file:/android_asset/")) {
            return getFileDataBytes(env, std::make_shared<jnivm::java::lang::String>(arg0->data() + 20));
        }
        return nullptr;
    }
}

void com::mojang::minecraftpe::MainActivity::displayDialog(ENV *env, jint arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::tick(ENV *env) {

}

void com::mojang::minecraftpe::MainActivity::quit(ENV *env) {
    
}

void com::mojang::minecraftpe::MainActivity::initiateUserInput(ENV *env, jint arg0) {
    
}

jint com::mojang::minecraftpe::MainActivity::getUserInputStatus(ENV *env) {
    return 0;
}

std::shared_ptr<jnivm::Array<jnivm::java::lang::String>> com::mojang::minecraftpe::MainActivity::getUserInputString(ENV *env) {
    return 0;
}

jint com::mojang::minecraftpe::MainActivity::checkLicense(ENV *env) {
    return 1;
}

jboolean com::mojang::minecraftpe::MainActivity::hasBuyButtonWhenInvalidLicense(ENV *env) {
    return false;
}

void com::mojang::minecraftpe::MainActivity::buyGame(ENV *env) {
    
}

void com::mojang::minecraftpe::MainActivity::vibrate(ENV *env, jint arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setIsPowerVR(ENV *env, jboolean arg0) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isNetworkEnabled(ENV *env, jboolean arg0) {
    return true;
}

jfloat com::mojang::minecraftpe::MainActivity::getPixelsPerMillimeter(ENV *env) {
    return 80;
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getPlatformStringVar(ENV *env, jint arg0) {
    return std::make_shared<jnivm::java::lang::String>("Android");
}

std::shared_ptr<jnivm::java::lang::Object> com::mojang::minecraftpe::MainActivity::getSystemService(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    auto sc = std::make_shared<jnivm::java::lang::Object>();
    auto cl = (jnivm::java::lang::Class*)env->env.FindClass("android/lang/Object");
    sc->clazz = { cl->shared_from_this(), cl };
    return sc;
}

std::shared_ptr<jnivm::android::view::Window> com::mojang::minecraftpe::MainActivity::getWindow(ENV *env) {
    auto w = std::make_shared<jnivm::android::view::Window>();
    auto cl = (jnivm::java::lang::Class*)env->env.FindClass("android/view/Window");
    w->clazz =  { cl->shared_from_this(), cl };
    return w;
}

jint com::mojang::minecraftpe::MainActivity::getKeyFromKeyCode(ENV *env, jint arg0, jint arg1, jint arg2) {
    return arg0;
}

void com::mojang::minecraftpe::MainActivity::updateLocalization(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::java::lang::String> arg1) {
    
}

void com::mojang::minecraftpe::MainActivity::showKeyboard(ENV *env, std::shared_ptr<jnivm::java::lang::String> text, jint arg1, jboolean arg2, jboolean arg3, jboolean multiline) {
    currentTextMutliline = multiline;
    maxcurrentTextLength = arg1;
    updateTextboxText(env, text);
}

void com::mojang::minecraftpe::MainActivity::hideKeyboard(ENV *env) {
    --iskeyboardvisible;
    Log::debug("Keyboard", "hide %d", iskeyboardvisible);
    if(!iskeyboardvisible) {
        window->setKeyboardState(iskeyboardvisible);
    }
}

jfloat com::mojang::minecraftpe::MainActivity::getKeyboardHeight(ENV *env) {
    return 0;
}

void com::mojang::minecraftpe::MainActivity::updateTextboxText(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    if(!iskeyboardvisible) {
        window->setKeyboardState(1);
    }
    ++iskeyboardvisible;
    Log::debug("Keyboard", "show %d", iskeyboardvisible);
    currentText = *arg0;
    currentTextPosition = currentText.size();
    currentTextPositionUTF = UTF8Util::getLength(currentText.c_str(), currentTextPosition);
    currentTextCopyPosition = currentTextPosition;
}

jint com::mojang::minecraftpe::MainActivity::getCursorPosition(ENV *env) {
    return currentTextPositionUTF;
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getAccessToken(ENV *env) {
    return std::make_shared<jnivm::java::lang::String>("Android");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getClientId(ENV *env) {
    return std::make_shared<jnivm::java::lang::String>("Android");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getProfileId(ENV *env) {
    return std::make_shared<jnivm::java::lang::String>("Android");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getProfileName(ENV *env) {
    return std::make_shared<jnivm::java::lang::String>("Android");
}

std::shared_ptr<jnivm::Array<jnivm::java::lang::String>> com::mojang::minecraftpe::MainActivity::getBroadcastAddresses(ENV *env) {
    return nullptr;
}

std::shared_ptr<jnivm::Array<jnivm::java::lang::String>> com::mojang::minecraftpe::MainActivity::getIPAddresses(ENV *env) {
    return nullptr;
}

jlong com::mojang::minecraftpe::MainActivity::getTotalMemory(ENV *env) {
    return std::numeric_limits<uint32_t>::max();
}

jlong com::mojang::minecraftpe::MainActivity::getMemoryLimit(ENV *env) {
    return std::numeric_limits<uint32_t>::max();
}

jlong com::mojang::minecraftpe::MainActivity::getUsedMemory(ENV *env) {
    return 0;
}

jlong com::mojang::minecraftpe::MainActivity::getFreeMemory(ENV *env) {
    return std::numeric_limits<uint32_t>::max();      
}

void com::mojang::minecraftpe::MainActivity::launchUri(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setClipboard(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    window->setClipboardText(*arg0);
}

void com::mojang::minecraftpe::MainActivity::share(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::java::lang::String> arg1, std::shared_ptr<jnivm::java::lang::String> arg2) {
    
}

std::shared_ptr<jnivm::android::content::Intent> com::mojang::minecraftpe::MainActivity::createAndroidLaunchIntent(ENV *env) {
    return 0;
}

jlong com::mojang::minecraftpe::MainActivity::calculateAvailableDiskFreeSpace(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    return -1;
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getExternalStoragePath(ENV *env) {
    return std::make_shared<jnivm::java::lang::String>(PathHelper::getPrimaryDataDirectory().data());
}

void com::mojang::minecraftpe::MainActivity::requestStoragePermission(ENV *env, jint arg0) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::hasWriteExternalStoragePermission(ENV *env) {
    return true;
}

void com::mojang::minecraftpe::MainActivity::deviceIdCorrelationStart(ENV *env) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isMixerCreateInstalled(ENV *env) {
    return false;
}

void com::mojang::minecraftpe::MainActivity::navigateToPlaystoreForMixerCreate(ENV *env) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::launchMixerCreateForBroadcast(ENV *env) {
    return false;
}

jboolean com::mojang::minecraftpe::MainActivity::isTTSEnabled(ENV *env) {
    return true;
}

std::shared_ptr<jnivm::com::mojang::minecraftpe::HardwareInformation> com::mojang::minecraftpe::MainActivity::getHardwareInfo(ENV *env) {
    auto hw = std::make_shared<jnivm::com::mojang::minecraftpe::HardwareInformation>();
    auto cl = (jnivm::java::lang::Class*)env->env.FindClass("com/mojang/minecraftpe/HardwareInformation");
    hw->clazz = { cl->shared_from_this(), cl };
    return hw;
}

void com::mojang::minecraftpe::MainActivity::setCachedDeviceId(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setLastDeviceSessionId(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getLastDeviceSessionId(ENV *env) {
    return std::make_shared<jnivm::java::lang::String>("");
}

jint com::mojang::minecraftpe::MainActivity::getAPIVersion(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    return 27;
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getSecureStorageKey(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    return std::make_shared<jnivm::java::lang::String>("Unknown");
}

void com::mojang::minecraftpe::MainActivity::setSecureStorageKey(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::java::lang::String> arg1) {
    
}

void com::mojang::minecraftpe::MainActivity::trackPurchaseEvent(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::java::lang::String> arg1, std::shared_ptr<jnivm::java::lang::String> arg2, std::shared_ptr<jnivm::java::lang::String> arg3, std::shared_ptr<jnivm::java::lang::String> arg4, std::shared_ptr<jnivm::java::lang::String> arg5, std::shared_ptr<jnivm::java::lang::String> arg6, std::shared_ptr<jnivm::java::lang::String> arg7) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeEvent(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeEventWithProperty(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::java::lang::String> arg1, jint arg2) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeEventWithStringProperty(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::java::lang::String> arg1, std::shared_ptr<jnivm::java::lang::String> arg2) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeToastClick(ENV *env) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeDialogButtonClick(ENV *env, jint arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::pickImage(ENV *env, jlong arg0) {
    Log::trace("MainActivity", "pickImage");
    auto picker = FilePickerFactory::createFilePicker();
    picker->setTitle("Select image");
    picker->setFileNameFilters({ "*.png" });
    if (picker->show()) {
        nativeOnPickImageSuccess(&env->env, nullptr, arg0, env->env.NewStringUTF(picker->getPickedFile().data()));
    } else {
        nativeOnPickImageCanceled(&env->env, nullptr, arg0);
    }
}

void com::mojang::minecraftpe::MainActivity::setFileDialogCallback(ENV *env, jlong arg0) {
    
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getLegacyDeviceID(ENV *env) {
    return std::make_shared<jnivm::java::lang::String>("19af3ae9-b15a-44b0-a3c2-aa2c66df489e");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::createUUID(ENV *env) {
    return std::make_shared<jnivm::java::lang::String>("daa78df1-373a-444d-9b1d-4c71a14bb559");
}

jboolean com::mojang::minecraftpe::MainActivity::hasHardwareKeyboard(ENV *env) {
    return false;
}

void com::mojang::minecraftpe::MainActivity::startTextToSpeech(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::stopTextToSpeech(ENV *env) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isTextToSpeechInProgress(ENV *env) {
    // return false;
    return false;
}

void com::mojang::minecraftpe::MainActivity::setTextToSpeechEnabled(ENV *env, jboolean arg0) {
    
}

jint com::mojang::minecraftpe::MainActivity::getScreenWidth(ENV *env) {
    return 0;
}

jint com::mojang::minecraftpe::MainActivity::getScreenHeight(ENV *env) {
    return 0;    
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getDeviceModel(ENV *env) {
    return std::make_shared<jnivm::java::lang::String>("Android");
}

// Needed for showing gamepad settings
jint com::mojang::minecraftpe::MainActivity::getAndroidVersion(ENV *env) {
    return 28;
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getLocale(ENV *env) {
    return std::make_shared<jnivm::java::lang::String>("en");
}

jboolean com::mojang::minecraftpe::MainActivity::isFirstSnooperStart(ENV *env) {
    return false;
}

jboolean com::mojang::minecraftpe::MainActivity::hasHardwareChanged(ENV *env) {
    return false;
}

jboolean com::mojang::minecraftpe::MainActivity::isTablet(ENV *env) {
    return false;
}

std::shared_ptr<jnivm::java::lang::ClassLoader> com::mojang::minecraftpe::MainActivity::getClassLoader(ENV *env) {
    auto hw = std::make_shared<jnivm::java::lang::ClassLoader>();
    auto cl = (jnivm::java::lang::Class*)env->env.FindClass("java/lang/ClassLoader");
    hw->clazz = { cl->shared_from_this(), cl };
    return hw;
}

struct xalinit {
    char* titleid;
    void* filler;
    char * sandboxid;
    void* filler2[3];
    JavaVM * vm;
    /*??*/std::shared_ptr<jnivm::java::lang::Object> obj;
    void* filler3[2];
    char* redirectUri;
};

struct xblinit {
    void* filler;
    char* id;
    JavaVM * vm;
    /*??*/std::shared_ptr<jnivm::java::lang::Object> obj;
};

void jnivm::com::mojang::minecraftpe::MainActivity::initializeXboxLive(ENV *env, jlong a, jlong b) {
    // std::thread([=] () {
        // std::this_thread::sleep_for(std::chrono::seconds(10));
        // auto xal = (xalinit*)a;
        // xal->obj = std::make_shared<jnivm::java::lang::Object>();
        // xal->obj->clazz = (jnivm::java::lang::Class *)env->env.FindClass("Xboxhardlive");
        // auto xbl = (xblinit*)b;
        // int res = XalInitialize(xal, nullptr);
        // res = XblInitialize(xbl);
        nativeInitializeXboxLive(&env->env, this, a, b);
        // std::abort();
    // }).detach();
}