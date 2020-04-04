#include "../JNIBinding.h"
#include "../utf8_util.h"
#include "minecraft/Keyboard.h"

jnivm::com::mojang::minecraftpe::MainActivity::MainActivity(void * handle) {
    nativeOnPickImageSuccess = (decltype(nativeOnPickImageSuccess))hybris_dlsym(handle, "Java_com_mojang_minecraftpe_MainActivity_nativeOnPickImageSuccess");
    nativeOnPickImageCanceled = (decltype(nativeOnPickImageCanceled))hybris_dlsym(handle, "Java_com_mojang_minecraftpe_MainActivity_nativeOnPickImageCanceled");
    nativeSetTextboxText = (decltype(nativeSetTextboxText))hybris_dlsym(handle, "Java_com_mojang_minecraftpe_MainActivity_nativeSetTextboxText");
    stbi_load_from_memory = (decltype(stbi_load_from_memory))hybris_dlsym(handle, "stbi_load_from_memory");
    stbi_image_free = (decltype(stbi_image_free))hybris_dlsym(handle, "stbi_image_free");
}

void jnivm::com::mojang::minecraftpe::MainActivity::onKeyboardText(jnivm::ENV* env, std::string const &text) {
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
        // nativeSetTextboxText(env, this, env->NewStringUTF(currentText.data()));
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

void com::mojang::minecraftpe::MainActivity::saveScreenshot(jnivm::ENV* env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::java::lang::String> arg0, jint arg1, jint arg2, std::shared_ptr<jnivm::Array<jint>> arg3) {
    
}

void com::mojang::minecraftpe::MainActivity::postScreenshotToFacebook(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0, jint arg1, jint arg2, std::shared_ptr<jnivm::Array<jint>> arg3) {
    
}

std::shared_ptr<jnivm::Array<jint>> com::mojang::minecraftpe::MainActivity::getImageData(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
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
jnivm::Array<jbyte>* com::mojang::minecraftpe::MainActivity::getFileDataBytes(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    std::ifstream file(*arg0, std::ios::binary | std::ios::ate);
    if(file.is_open()) {
        auto length = file.tellg();
        auto value = new jbyte[(size_t)length + 1];
        file.seekg(0, std::ios::beg);
        file.read((char*)value, length);
        value[length] = 0;
        return new jnivm::Array<jbyte>(value, (size_t)length);
    } else {
        if(!arg0->compare(0, 20, "file:/android_asset/")) {
            return getFileDataBytes(env, std::make_shared<jnivm::java::lang::String>(arg0->data() + 20));
        }
        return nullptr;
    }
}

void com::mojang::minecraftpe::MainActivity::displayDialog(jnivm::ENV* env, jint arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::tick(jnivm::ENV* env) {

}

void com::mojang::minecraftpe::MainActivity::quit(jnivm::ENV* env) {
    
}

void com::mojang::minecraftpe::MainActivity::initiateUserInput(jnivm::ENV* env, jint arg0) {
    
}

jint com::mojang::minecraftpe::MainActivity::getUserInputStatus(jnivm::ENV* env) {
    return 0;
}

jnivm::Array<std::shared_ptr<jnivm::java::lang::String>>* com::mojang::minecraftpe::MainActivity::getUserInputString(jnivm::ENV* env) {
    return 0;
}

jint com::mojang::minecraftpe::MainActivity::checkLicense(jnivm::ENV* env) {
    return 1;
}

jboolean com::mojang::minecraftpe::MainActivity::hasBuyButtonWhenInvalidLicense(jnivm::ENV* env) {
    return false;
}

void com::mojang::minecraftpe::MainActivity::buyGame(jnivm::ENV* env) {
    
}

void com::mojang::minecraftpe::MainActivity::vibrate(jnivm::ENV* env, jint arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setIsPowerVR(jnivm::ENV* env, jboolean arg0) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isNetworkEnabled(jnivm::ENV* env, jboolean arg0) {
    return true;
}

jfloat com::mojang::minecraftpe::MainActivity::getPixelsPerMillimeter(jnivm::ENV* env) {
    return 80;
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getPlatformStringVar(jnivm::ENV* env, jint arg0) {
    return std::make_shared<jnivm::java::lang::String>("Android");
}

jnivm::java::lang::Object* com::mojang::minecraftpe::MainActivity::getSystemService(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    auto sc = new jnivm::java::lang::Object();
    sc->clazz = env->GetClass("android/lang/Object");
    return sc;
}

jnivm::android::view::Window* com::mojang::minecraftpe::MainActivity::getWindow(jnivm::ENV* env) {
    auto w = new jnivm::android::view::Window();
    w->clazz = env->GetClass("android/view/Window");
    return w;
}

jint com::mojang::minecraftpe::MainActivity::getKeyFromKeyCode(jnivm::ENV* env, jint arg0, jint arg1, jint arg2) {
    return arg0;
}

void com::mojang::minecraftpe::MainActivity::updateLocalization(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::java::lang::String> arg1) {
    
}

void com::mojang::minecraftpe::MainActivity::showKeyboard(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> text, jint arg1, jboolean arg2, jboolean arg3, jboolean multiline) {
    currentTextMutliline = multiline;
    maxcurrentTextLength = arg1;
    updateTextboxText(env, text);
}

void com::mojang::minecraftpe::MainActivity::hideKeyboard(jnivm::ENV* env) {
    --iskeyboardvisible;
    Log::debug("Keyboard", "hide %d", iskeyboardvisible);
    if(!iskeyboardvisible) {
        window->setKeyboardState(iskeyboardvisible);
    }
}

jfloat com::mojang::minecraftpe::MainActivity::getKeyboardHeight(jnivm::ENV* env) {
    return 0;
}

void com::mojang::minecraftpe::MainActivity::updateTextboxText(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
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

jint com::mojang::minecraftpe::MainActivity::getCursorPosition(jnivm::ENV* env) {
    return currentTextPositionUTF;
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getAccessToken(jnivm::ENV* env) {
    return std::make_shared<jnivm::java::lang::String>("Android");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getClientId(jnivm::ENV* env) {
    return std::make_shared<jnivm::java::lang::String>("Android");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getProfileId(jnivm::ENV* env) {
    return std::make_shared<jnivm::java::lang::String>("Android");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getProfileName(jnivm::ENV* env) {
    return std::make_shared<jnivm::java::lang::String>("Android");
}

jnivm::Array<std::shared_ptr<jnivm::java::lang::String>>* com::mojang::minecraftpe::MainActivity::getBroadcastAddresses(jnivm::ENV* env) {
    return nullptr;
}

jnivm::Array<std::shared_ptr<jnivm::java::lang::String>>* com::mojang::minecraftpe::MainActivity::getIPAddresses(jnivm::ENV* env) {
    return nullptr;
}

jlong com::mojang::minecraftpe::MainActivity::getTotalMemory(jnivm::ENV* env) {
    return std::numeric_limits<uint32_t>::max();
}

jlong com::mojang::minecraftpe::MainActivity::getMemoryLimit(jnivm::ENV* env) {
    return std::numeric_limits<uint32_t>::max();
}

jlong com::mojang::minecraftpe::MainActivity::getUsedMemory(jnivm::ENV* env) {
    return 0;
}

jlong com::mojang::minecraftpe::MainActivity::getFreeMemory(jnivm::ENV* env) {
    return std::numeric_limits<uint32_t>::max();      
}

void com::mojang::minecraftpe::MainActivity::launchUri(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setClipboard(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    window->setClipboardText(*arg0);
}

void com::mojang::minecraftpe::MainActivity::share(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::java::lang::String> arg1, std::shared_ptr<jnivm::java::lang::String> arg2) {
    
}

std::shared_ptr<jnivm::android::content::Intent> com::mojang::minecraftpe::MainActivity::createAndroidLaunchIntent(jnivm::ENV* env) {
    return 0;
}

jlong com::mojang::minecraftpe::MainActivity::calculateAvailableDiskFreeSpace(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    return -1;
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getExternalStoragePath(jnivm::ENV* env) {
    return std::make_shared<jnivm::java::lang::String>(PathHelper::getPrimaryDataDirectory());
}

void com::mojang::minecraftpe::MainActivity::requestStoragePermission(jnivm::ENV* env, jint arg0) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::hasWriteExternalStoragePermission(jnivm::ENV* env) {
    return true;
}

void com::mojang::minecraftpe::MainActivity::deviceIdCorrelationStart(jnivm::ENV* env) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isMixerCreateInstalled(jnivm::ENV* env) {
    return false;
}

void com::mojang::minecraftpe::MainActivity::navigateToPlaystoreForMixerCreate(jnivm::ENV* env) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::launchMixerCreateForBroadcast(jnivm::ENV* env) {
    return false;
}

jboolean com::mojang::minecraftpe::MainActivity::isTTSEnabled(jnivm::ENV* env) {
    return true;
}

std::shared_ptr<jnivm::com::mojang::minecraftpe::HardwareInformation> com::mojang::minecraftpe::MainActivity::getHardwareInfo(jnivm::ENV* env) {
    auto hw = std::make_shared<jnivm::com::mojang::minecraftpe::HardwareInformation>();
    hw->clazz = env->GetClass("com/mojang/minecraftpe/HardwareInformation");
    return hw;
}

void com::mojang::minecraftpe::MainActivity::setCachedDeviceId(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::setLastDeviceSessionId(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getLastDeviceSessionId(jnivm::ENV* env) {
    return std::make_shared<jnivm::java::lang::String>("");
}

jint com::mojang::minecraftpe::MainActivity::getAPIVersion(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    return 27;
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getSecureStorageKey(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    return std::make_shared<jnivm::java::lang::String>("Unknown");
}

void com::mojang::minecraftpe::MainActivity::setSecureStorageKey(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::java::lang::String> arg1) {
    
}

void com::mojang::minecraftpe::MainActivity::trackPurchaseEvent(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::java::lang::String> arg1, std::shared_ptr<jnivm::java::lang::String> arg2, std::shared_ptr<jnivm::java::lang::String> arg3, std::shared_ptr<jnivm::java::lang::String> arg4, std::shared_ptr<jnivm::java::lang::String> arg5, std::shared_ptr<jnivm::java::lang::String> arg6, std::shared_ptr<jnivm::java::lang::String> arg7) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeEvent(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeEventWithProperty(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::java::lang::String> arg1, jint arg2) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeEventWithStringProperty(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::java::lang::String> arg1, std::shared_ptr<jnivm::java::lang::String> arg2) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeToastClick(jnivm::ENV* env) {
    
}

void com::mojang::minecraftpe::MainActivity::sendBrazeDialogButtonClick(jnivm::ENV* env, jint arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::pickImage(jnivm::ENV* env, jlong arg0) {
    Log::trace("MainActivity", "pickImage");
    auto picker = FilePickerFactory::createFilePicker();
    picker->setTitle("Select image");
    picker->setFileNameFilters({ "*.png" });
    if (picker->show()) {
        // nativeOnPickImageSuccess(env, nullptr, arg0, env->NewStringUTF(picker->getPickedFile().data()));
    } else {
        // nativeOnPickImageCanceled(env, nullptr, arg0);
    }
}

void com::mojang::minecraftpe::MainActivity::setFileDialogCallback(jnivm::ENV* env, jlong arg0) {
    
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getLegacyDeviceID(jnivm::ENV* env) {
    return std::make_shared<jnivm::java::lang::String>("19af3ae9-b15a-44b0-a3c2-aa2c66df489e");
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::createUUID(jnivm::ENV* env) {
    return std::make_shared<jnivm::java::lang::String>("daa78df1-373a-444d-9b1d-4c71a14bb559");
}

jboolean com::mojang::minecraftpe::MainActivity::hasHardwareKeyboard(jnivm::ENV* env) {
    return false;
}

void com::mojang::minecraftpe::MainActivity::startTextToSpeech(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

void com::mojang::minecraftpe::MainActivity::stopTextToSpeech(jnivm::ENV* env) {
    
}

jboolean com::mojang::minecraftpe::MainActivity::isTextToSpeechInProgress(jnivm::ENV* env) {
    // return false;
    return false;
}

void com::mojang::minecraftpe::MainActivity::setTextToSpeechEnabled(jnivm::ENV* env, jboolean arg0) {
    
}

jint com::mojang::minecraftpe::MainActivity::getScreenWidth(jnivm::ENV* env) {
    return 0;
}

jint com::mojang::minecraftpe::MainActivity::getScreenHeight(jnivm::ENV* env) {
    return 0;    
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getDeviceModel(jnivm::ENV* env) {
    return std::make_shared<jnivm::java::lang::String>("Android");
}

// Needed for showing gamepad settings
jint com::mojang::minecraftpe::MainActivity::getAndroidVersion(jnivm::ENV* env) {
    return 28;
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::minecraftpe::MainActivity::getLocale(jnivm::ENV* env) {
    return std::make_shared<jnivm::java::lang::String>("en");
}

jboolean com::mojang::minecraftpe::MainActivity::isFirstSnooperStart(jnivm::ENV* env) {
    return false;
}

jboolean com::mojang::minecraftpe::MainActivity::hasHardwareChanged(jnivm::ENV* env) {
    return false;
}

jboolean com::mojang::minecraftpe::MainActivity::isTablet(jnivm::ENV* env) {
    return false;
}

jnivm::java::lang::ClassLoader* com::mojang::minecraftpe::MainActivity::getClassLoader(jnivm::ENV* env) {
    auto hw = new jnivm::java::lang::ClassLoader();
    hw->clazz = env->GetClass("java/lang/ClassLoader");
    return hw;
}