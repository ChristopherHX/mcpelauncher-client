#include "tts_patch.h"

#include <mcpelauncher/patch_utils.h>
#include <hybris/dlfcn.h>
#include <mcpelauncher/minecraft_version.h>

void TTSPatch::install(void* handle) {
    if (!MinecraftVersion::isAtLeast(1, 8))
        return;
    void* sym = (void*)((intptr_t)hybris_dlsym(handle, "_ZN18TextToSpeechSystem15createTTSClientEb") | (intptr_t)hybris_dlsym(handle, "_ZN26TextToSpeechSystem_android16_createTTSClientEv"));
    PatchUtils::patchCallInstruction(sym, (void*) &TTSPatch::createTTSClient, true);
}

mcpe::shared_ptr<NullTextToSpeechClient> TTSPatch::createTTSClient() {
    auto ret = new NullTextToSpeechClient;
    ret->vtable = &NullTextToSpeechClient::myVtable[2];
    return mcpe::shared_ptr<NullTextToSpeechClient>(ret);
}