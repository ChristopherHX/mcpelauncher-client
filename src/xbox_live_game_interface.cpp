#include "xbox_live_game_interface.h"
#include "xbox_live_helper.h"
#include <mcpelauncher/minecraft_version.h>
#include <minecraft/legacy/Xbox.h>
#include "JNIBinding.h"

const char* const XboxLiveDefaultGameInterface::TAG = "XboxLiveGameInterface";

XboxLiveGameInterface& XboxLiveGameInterface::getInstance() {
    static XboxLiveDefaultGameInterface instance;
    return instance;
}

#ifdef ENABLE_CLL
extern jnivm::ENV * jnivm;
extern void * get_uploader_x_token_callback;
extern void * get_supporting_x_token_callback;

std::string XboxLiveDefaultGameInterface::getCllXToken(bool refresh) {
    if(!get_uploader_x_token_callback) 
        return std::string();
    auto val = ((std::shared_ptr<jnivm::java::lang::String>(*)(jnivm::ENV* env, jnivm::java::lang::Class* cl, jboolean)) get_uploader_x_token_callback)(jnivm, nullptr, refresh);
    return val ? *val : std::string();
}

std::string XboxLiveDefaultGameInterface::getCllXTicket(std::string const &xuid) {
    if(!get_supporting_x_token_callback)
        return std::string();
    auto val = ((std::shared_ptr<jnivm::java::lang::String>(*)(jnivm::ENV* env, jnivm::java::lang::Class* cl, jstring))get_supporting_x_token_callback)(jnivm, nullptr, jnivm->NewStringUTF(xuid.data()));
    return val ? *val : std::string();
}
#endif