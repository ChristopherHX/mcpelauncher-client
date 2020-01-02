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

extern JNIEnv * jnienv;
extern void * get_uploader_x_token_callback;
extern void * get_supporting_x_token_callback;

std::string XboxLiveDefaultGameInterface::getCllXToken(bool refresh) {
    return get_uploader_x_token_callback ? *((jnivm::java::lang::String*(*)(JNIEnv* env, jclass cl, jboolean)) get_uploader_x_token_callback)(jnienv, nullptr, refresh) : std::string();
}

std::string XboxLiveDefaultGameInterface::getCllXTicket(std::string const &xuid) {
    return get_supporting_x_token_callback ? *((jnivm::java::lang::String*(*)(JNIEnv* env, jclass cl, jstring))get_supporting_x_token_callback)(jnienv, nullptr, jnienv->NewStringUTF(xuid.data())) : std::string();
}