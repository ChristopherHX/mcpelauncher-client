#include "../JNIBinding.h"
#include <log.h>

void XBLoginCallback::onLogin(ENV *env, jlong arg0, jboolean arg1) {
    auto invoke_event_initialization = (void (*)(JNIEnv *env, jnivm::java::lang::Class*, jlong var0, jstring var2, XBLoginCallback* var3))cl->natives["invoke_event_initialization"];
    auto XBLoginCallbackcl = env->env.FindClass("XBLoginCallback");
    auto sh = shared_from_this();
    invoke_event_initialization(&env->env, (jnivm::java::lang::Class*)XBLoginCallbackcl, userptr, env->env.NewStringUTF(token.data()), this);
}

void XBLoginCallback::onSuccess(ENV *env) {
    auth_flow_callback(&env->env, cl.get(), userptr, /* No Error */0, env->env.NewStringUTF(cid.data()));    
}

void XBLoginCallback::onError(ENV *env, jint arg0, jint arg1, std::shared_ptr<jnivm::java::lang::String> arg2) {
    Log::error("XboxLive", "Sign in error: %s", arg2->data());
    auth_flow_callback(&env->env, cl.get(), userptr, /* Failed */2, nullptr);        
}

std::shared_ptr<jnivm::java::lang::String> com::microsoft::xbox::idp::interop::Interop::GetLocalStoragePath(ENV *env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::android::content::Context> arg0) {
    return std::make_shared<jnivm::java::lang::String>(PathHelper::getPrimaryDataDirectory().data());
}

std::shared_ptr<jnivm::java::lang::String> com::microsoft::xbox::idp::interop::Interop::ReadConfigFile(ENV *env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::android::content::Context> arg0) {
    Log::trace("XBOXLive", "Reading xbox config file");
    std::ifstream f("xboxservices.config");
    std::stringstream s;
    s << f.rdbuf();
    return std::make_shared<jnivm::java::lang::String>(s.str().data());
}

// Sets proxy for Xboxlive, "" for no proxy server
std::shared_ptr<jnivm::java::lang::String> com::microsoft::xbox::idp::interop::Interop::getSystemProxy(ENV *env, jnivm::java::lang::Class* clazz) {
    return std::make_shared<jnivm::java::lang::String>("");
}

void * get_uploader_x_token_callback = 0;
void * get_supporting_x_token_callback = 0;

void com::microsoft::xbox::idp::interop::Interop::InitCLL(ENV *env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::android::content::Context> arg0, std::shared_ptr<jnivm::java::lang::String> arg1) {
    get_uploader_x_token_callback = ((jnivm::java::lang::Class*)clazz)->natives["get_uploader_x_token_callback"];
    get_supporting_x_token_callback = ((jnivm::java::lang::Class*)clazz)->natives["get_supporting_x_token_callback"];
    XboxLiveHelper::getInstance().initCll();
}

void com::microsoft::xbox::idp::interop::Interop::LogTelemetrySignIn(ENV *env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::java::lang::String> arg1) {
    Log::info("com::microsoft::xbox::idp::interop::Interop::LogTelemetrySignIn", "%s:%s", arg0->data(), arg1->data());    
}

void com::microsoft::xbox::idp::interop::Interop::InvokeMSA(ENV *env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::android::content::Context> arg0, jint requestCode, jboolean arg2, std::shared_ptr<jnivm::java::lang::String> cid) {
    auto cl = (jnivm::java::lang::Class*)clazz;
    auto ticket_callback = ((void(*)(JNIEnv *env, void*, jstring paramString1, jint paramInt1, jint paramInt2, jstring paramString2))cl->natives["ticket_callback"]);
    if (requestCode == 1) { // silent signin
        if (!cid->empty()) {
            try {
                XboxLiveHelper::getInstance().requestXblToken(*cid, true,
                    [env,ticket_callback](std::string const& cid, std::string const& token) {
                        XboxLiveHelper::getInstance().initCll(cid);
                        ticket_callback(&env->env, nullptr, env->env.NewStringUTF(token.data()), 0, /* Error None */ 0, env->env.NewStringUTF("Got ticket"));
                    }, [=](simpleipc::rpc_error_code err, std::string const& msg) {
                        Log::error("XboxLive", "Auto Sign in failed (RPC): %s", msg.c_str());
                        if (err == -100) { // No such account
                            ticket_callback(&env->env, nullptr, env->env.NewStringUTF(""), 0, /* Error No such account */ 1, env->env.NewStringUTF("Must show UI to acquire an account."));
                        } else if (err == -102) { // Must show UI
                            ticket_callback(&env->env, nullptr, env->env.NewStringUTF(""), 0, /* Error Must show UI */ 1, env->env.NewStringUTF("Must show UI to update account information."));
                        } else {
                            ticket_callback(&env->env, nullptr, env->env.NewStringUTF(""), 0, /* Error */ 1, env->env.NewStringUTF(msg.c_str()));
                        }
                    });
        } catch(const std::exception& ex) {
            Log::error("XboxLive", "Auto Sign in error (exception): %s", ex.what());
            ticket_callback(&env->env, nullptr, env->env.NewStringUTF(""), 0, /* Error */ 1, nullptr);
        }
    } else {
            ticket_callback(&env->env, nullptr, env->env.NewStringUTF(""), requestCode, /* Error No such account */ 1, env->env.NewStringUTF("Must show UI to acquire an account."));
        }
    } else if (requestCode == 6) { // sign out
        ((void(*)(JNIEnv*, void*))cl->natives["sign_out_callback"])(&env->env, nullptr);
    }
}

void com::microsoft::xbox::idp::interop::Interop::InvokeAuthFlow(ENV *env, jnivm::java::lang::Class* clazz, jlong userptr, std::shared_ptr<jnivm::android::app::Activity> arg1, jboolean arg2/* , std::shared_ptr<jnivm::java::lang::String> arg3 */) {
    auto cl = (jnivm::java::lang::Class*) clazz;
    auto auth_flow_callback = (void(*)(JNIEnv *env, void*, jlong paramLong, jint paramInt, jstring paramString))cl->natives["auth_flow_callback"];
    auto invoke_xb_login = (void(*)(JNIEnv*, void*, jlong paramLong, jstring paramString, jobject))cl->natives["invoke_xb_login"];
    auto onsuccess = [env, auth_flow_callback, userptr, invoke_xb_login,cl](std::string const& cid, std::string const& token) {
        auto XBLoginCallbackcl = env->env.FindClass("XBLoginCallback");
        auto xblc = std::make_shared<XBLoginCallback>();
        auto cl2 = (jnivm::java::lang::Class*)XBLoginCallbackcl;
        xblc->clazz = { cl2->shared_from_this(), cl2 };
        xblc->userptr = userptr;
        xblc->cid = cid;
        xblc->token = token;
        xblc->cl = { cl->shared_from_this(), cl };
        xblc->auth_flow_callback = auth_flow_callback;
        invoke_xb_login(&env->env, cl, userptr, env->env.NewStringUTF(token.data()), (jobject)xblc.get());
    };
    auto onfail = [=](simpleipc::rpc_error_code rpc, std::string const& msg) {
        Log::error("XboxLive", "Sign in error (RPC): %s", msg.c_str());
        auth_flow_callback(&env->env, cl, userptr, /* Failed */2, nullptr);
    };

    try {
        XboxLiveHelper::getInstance().invokeMsaAuthFlow(onsuccess, onfail);
    } catch(const std::exception& ex) {
        Log::error("XboxLive", "Sign in error (exception): %s", ex.what());
        auth_flow_callback(&env->env, cl, userptr, /* Failed */2, nullptr);
    }
    
}

std::shared_ptr<jnivm::java::lang::String> com::microsoft::xbox::idp::interop::Interop::getLocale(ENV *env, jnivm::java::lang::Class* clazz) {
    return std::make_shared<jnivm::java::lang::String>("en");
}

void com::microsoft::xbox::idp::interop::Interop::RegisterWithGNS(ENV *env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::android::content::Context> arg0) {
    
}

void com::microsoft::xbox::idp::interop::Interop::LogCLL(ENV *env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::java::lang::String> ticket, std::shared_ptr<jnivm::java::lang::String> name, std::shared_ptr<jnivm::java::lang::String> data) {
    Log::trace("com::microsoft::xbox::idp::interop::Interop::LogCLL", "log_cll %s %s %s", ticket->c_str(), name->c_str(), data->c_str());
    cll::Event event(*name, nlohmann::json::parse(*data),
                     cll::EventFlags::PersistenceCritical | cll::EventFlags::LatencyRealtime, {*ticket});
    XboxLiveHelper::getInstance().logCll(event);
}

#ifdef __APPLE__
#define OPENBROWSER "open"
#elif defined(_WIN32)
#define OPENBROWSER "start"
#else
#define OPENBROWSER "xdg-open"
#endif
void com::microsoft::xboxtcui::Interop::ShowFriendFinder(ENV *env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::android::app::Activity> arg0, std::shared_ptr<jnivm::java::lang::String> arg1, std::shared_ptr<jnivm::java::lang::String> arg2) {
    system(OPENBROWSER" https://account.xbox.com/en-us/Friends");
    ((void(*)(JNIEnv *env, jnivm::java::lang::Class* clazz, jint))((jnivm::java::lang::Class*)clazz)->natives["tcui_completed_callback"])(&env->env, clazz, 0);
}

void jnivm::com::microsoft::xboxtcui::Interop::ShowUserSettings(ENV *env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::android::content::Context> arg0) {
    system(OPENBROWSER" https://account.xbox.com/en-us/Settings");
    ((void(*)(JNIEnv *env, jnivm::java::lang::Class* clazz, jint))((jnivm::java::lang::Class*)clazz)->natives["tcui_completed_callback"])(&env->env, clazz, 0);
}

void jnivm::com::microsoft::xboxtcui::Interop::ShowUserProfile(ENV *env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::android::content::Context> arg0, std::shared_ptr<jnivm::java::lang::String> arg1) {
    system(OPENBROWSER" https://account.xbox.com/en-us/Profile");
    ((void(*)(JNIEnv *env, jnivm::java::lang::Class* clazz, jint))((jnivm::java::lang::Class*)clazz)->natives["tcui_completed_callback"])(&env->env, clazz, 0);
}
#undef OPENBROWSER