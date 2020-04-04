// #include "../JNIBinding.h"
// #include <log.h>

// void XBLoginCallback::onLogin(jnivm::ENV* env, jlong arg0, jboolean arg1) {
//     auto invoke_event_initialization = (void (*)(jnivm::ENV* env, jnivm::java::lang::Class*, jlong var0, jstring var2, XBLoginCallback* var3))cl->natives["invoke_event_initialization"];
//     auto XBLoginCallbackcl = env->FindClass("XBLoginCallback");
//     invoke_event_initialization(env, nullptr, userptr, env->NewStringUTF(token.data()), this);
// }

// void XBLoginCallback::onSuccess(jnivm::ENV* env) {
//     auth_flow_callback(env, nullptr, userptr, /* No Error */0, env->NewStringUTF(cid.data()));    
// }

// void XBLoginCallback::onError(jnivm::ENV* env, jint arg0, jint arg1, std::shared_ptr<jnivm::java::lang::String> arg2) {
//     Log::error("XboxLive", "Sign in error: %s", arg2->data());
//     auth_flow_callback(env, nullptr, userptr, /* Failed */2, nullptr);        
// }

// std::shared_ptr<jnivm::java::lang::String> com::microsoft::xbox::idp::interop::Interop::GetLocalStoragePath(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jnivm::android::content::Context* arg0) {
//     return std::make_shared<jnivm::java::lang::String>(PathHelper::getPrimaryDataDirectory().data());
// }

// std::shared_ptr<jnivm::java::lang::String> com::microsoft::xbox::idp::interop::Interop::ReadConfigFile(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jnivm::android::content::Context* arg0) {
//     Log::trace("XBOXLive", "Reading xbox config file");
//     std::ifstream f("xboxservices.config");
//     std::stringstream s;
//     s << f.rdbuf();
//     return std::make_shared<jnivm::java::lang::String>(s.str().data());
// }

// // Sets proxy for Xboxlive, "" for no proxy server
// std::shared_ptr<jnivm::java::lang::String> com::microsoft::xbox::idp::interop::Interop::getSystemProxy(jnivm::ENV* env, jnivm::java::lang::Class* clazz) {
//     return std::make_shared<jnivm::java::lang::String>("");
// }

// #ifdef ENABLE_CLL
// void * get_uploader_x_token_callback = 0;
// void * get_supporting_x_token_callback = 0;
// #endif

// void com::microsoft::xbox::idp::interop::Interop::InitCLL(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jnivm::android::content::Context* arg0, std::shared_ptr<jnivm::java::lang::String> arg1) {
// #ifdef ENABLE_CLL
//     get_uploader_x_token_callback = clazz->natives["get_uploader_x_token_callback"];
//     get_supporting_x_token_callback = clazz->natives["get_supporting_x_token_callback"];
//     XboxLiveHelper::getInstance().initCll();
// #endif
// }

// void com::microsoft::xbox::idp::interop::Interop::LogTelemetrySignIn(jnivm::ENV* env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::java::lang::String> arg0, std::shared_ptr<jnivm::java::lang::String> arg1) {
//     Log::info("com::microsoft::xbox::idp::interop::Interop::LogTelemetrySignIn", "%s:%s", arg0->data(), arg1->data());    
// }

// void com::microsoft::xbox::idp::interop::Interop::InvokeMSA(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jnivm::android::content::Context* arg0, jint requestCode, jboolean arg2, std::shared_ptr<jnivm::java::lang::String> cid) {
//     auto cl = (std::shared_ptr<jnivm::java::lang::Class>)clazz;
//     // auto appconfig = env->GetClass("com/microsoft/xbox/idp/interop/XboxLiveAppConfig");
//     // auto id = ((jlong(*)(jnivm::ENV * env, void*))appconfig->natives["create"])(env, nullptr);
//     // auto titleid = ((jint(*)(jnivm::ENV * env, void*, jlong))appconfig->natives["getTitleId"])(env, nullptr, id);
//     // auto scid = ((std::shared_ptr<jnivm::java::lang::String>(*)(jnivm::ENV * env, void*, jlong))appconfig->natives["getScid"])(env, nullptr, id);
//     // auto sandbox = ((std::shared_ptr<jnivm::java::lang::String>(*)(jnivm::ENV * env, void*, jlong))appconfig->natives["getSandbox"])(env, nullptr, id);
//     // auto proxy = ((std::shared_ptr<jnivm::java::lang::String>(*)(jnivm::ENV * env, void*, jlong))appconfig->natives["getProxy"])(env, nullptr, id);
//     // auto overrideTitleId = ((jint(*)(jnivm::ENV * env, void*, jlong))appconfig->natives["getOverrideTitleId"])(env, nullptr, id);
//     // auto environment = ((std::shared_ptr<jnivm::java::lang::String>(*)(jnivm::ENV * env, void*, jlong))appconfig->natives["getEnvironment"])(env, nullptr, id);
//     // ((void(*)(jnivm::ENV * env, void*, jlong))appconfig->natives["delete"])(env, nullptr, id);
//     auto ticket_callback = ((void(*)(jnivm::ENV* env, void*, jstring paramString1, jint paramInt1, jint paramInt2, jstring paramString2))cl->natives["ticket_callback"]);
//     if (requestCode == 1) { // silent signin
//         if (!cid->empty()) {
//             try {
//                 XboxLiveHelper::getInstance().requestXblToken(*cid, true,
//                     [env,ticket_callback](std::string const& cid, std::string const& token) {
// #ifdef ENABLE_CLL
//                         XboxLiveHelper::getInstance().initCll(cid);
// #endif
//                         ticket_callback(env, nullptr, env->NewStringUTF(token.data()), 0, /* Error None */ 0, env->NewStringUTF("Got ticket"));
//                     }, [=](simpleipc::rpc_error_code err, std::string const& msg) {
//                         Log::error("XboxLive", "Auto Sign in failed (RPC): %s", msg.c_str());
//                         if (err == -100) { // No such account
//                             ticket_callback(env, nullptr, env->NewStringUTF(""), 0, /* Error No such account */ 1, env->NewStringUTF("Must show UI to acquire an account."));
//                         } else if (err == -102) { // Must show UI
//                             ticket_callback(env, nullptr, env->NewStringUTF(""), 0, /* Error Must show UI */ 1, env->NewStringUTF("Must show UI to update account information."));
//                         } else {
//                             ticket_callback(env, nullptr, env->NewStringUTF(""), 0, /* Error */ 1, env->NewStringUTF(msg.c_str()));
//                         }
//                     });
//         } catch(const std::exception& ex) {
//             Log::error("XboxLive", "Auto Sign in error (exception): %s", ex.what());
//             ticket_callback(env, nullptr, env->NewStringUTF(""), 0, /* Error */ 1, nullptr);
//         }
//     } else {
//             ticket_callback(env, nullptr, env->NewStringUTF(""), requestCode, /* Error No such account */ 1, env->NewStringUTF("Must show UI to acquire an account."));
//         }
//     } else if (requestCode == 6) { // sign out
//         ((void(*)(jnivm::ENV*, void*))cl->natives["sign_out_callback"])(env, nullptr);
//     }
// }

// void com::microsoft::xbox::idp::interop::Interop::InvokeAuthFlow(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jlong userptr, jnivm::android::app::Activity* arg1, jboolean arg2, std::shared_ptr<jnivm::java::lang::String> arg3) {
//     auto cl = (std::shared_ptr<jnivm::java::lang::Class>) clazz;
//     auto auth_flow_callback = (void(*)(jnivm::ENV* env, void*, jlong paramLong, jint paramInt, jstring paramString))cl->natives["auth_flow_callback"];
//     auto invoke_xb_login = (void(*)(jnivm::ENV*, void*, jlong paramLong, jstring paramString, jobject))cl->natives["invoke_xb_login"];
//     auto onsuccess = [env, auth_flow_callback, userptr, invoke_xb_login,cl](std::string const& cid, std::string const& token) {
//         auto XBLoginCallbackcl = env->FindClass("XBLoginCallback");
//         auto xblc = new XBLoginCallback();
//         xblc->clazz = (std::shared_ptr<jnivm::java::lang::Class>)XBLoginCallbackcl;
//         xblc->userptr = userptr;
//         xblc->cid = cid;
//         xblc->token = token;
//         xblc->cl = cl;
//         xblc->auth_flow_callback = auth_flow_callback;
//         invoke_xb_login(env, nullptr, userptr, env->NewStringUTF(token.data()), (jobject)xblc);
//     };
//     auto onfail = [=](simpleipc::rpc_error_code rpc, std::string const& msg) {
//         Log::error("XboxLive", "Sign in error (RPC): %s", msg.c_str());
//         auth_flow_callback(env, nullptr, userptr, /* Failed */2, nullptr);
//     };

//     try {
//         XboxLiveHelper::getInstance().invokeMsaAuthFlow(onsuccess, onfail);
//     } catch(const std::exception& ex) {
//         Log::error("XboxLive", "Sign in error (exception): %s", ex.what());
//         auth_flow_callback(env, nullptr, userptr, /* Failed */2, nullptr);
//     }
    
// }

// std::shared_ptr<jnivm::java::lang::String> com::microsoft::xbox::idp::interop::Interop::getLocale(jnivm::ENV* env, jnivm::java::lang::Class* clazz) {
//     return std::make_shared<jnivm::java::lang::String>("en");
// }

// void com::microsoft::xbox::idp::interop::Interop::RegisterWithGNS(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jnivm::android::content::Context* arg0) {
    
// }

// void com::microsoft::xbox::idp::interop::Interop::LogCLL(jnivm::ENV* env, jnivm::java::lang::Class* clazz, std::shared_ptr<jnivm::java::lang::String> ticket, std::shared_ptr<jnivm::java::lang::String> name, std::shared_ptr<jnivm::java::lang::String> data) {
// #ifdef ENABLE_CLL
//     Log::trace("com::microsoft::xbox::idp::interop::Interop::LogCLL", "log_cll %s %s %s", ticket->c_str(), name->c_str(), data->c_str());
//     cll::Event event(*name, nlohmann::json::parse(*data),
//                      cll::EventFlags::PersistenceCritical | cll::EventFlags::LatencyRealtime, {*ticket});
//     XboxLiveHelper::getInstance().logCll(event);
// #endif
// }

// #ifdef __APPLE__
// #define OPENBROWSER "open"
// #elif defined(_WIN32)
// #define OPENBROWSER "start"
// #else
// #define OPENBROWSER "xdg-open"
// #endif
// void com::microsoft::xboxtcui::Interop::ShowFriendFinder(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jnivm::android::app::Activity* arg0, std::shared_ptr<jnivm::java::lang::String> arg1, std::shared_ptr<jnivm::java::lang::String> arg2) {
//     system(OPENBROWSER" https://account.xbox.com/en-us/Friends");
//     ((void(*)(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jint))clazz->natives["tcui_completed_callback"])(env, clazz, 0);
// }

// void jnivm::com::microsoft::xboxtcui::Interop::ShowUserSettings(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jnivm::android::content::Context* arg0) {
//     system(OPENBROWSER" https://account.xbox.com/en-us/Settings");
//     ((void(*)(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jint))clazz->natives["tcui_completed_callback"])(env, clazz, 0);
// }

// void jnivm::com::microsoft::xboxtcui::Interop::ShowUserProfile(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jnivm::android::content::Context* arg0, std::shared_ptr<jnivm::java::lang::String> arg1) {
//     system(OPENBROWSER" https://account.xbox.com/en-us/Profile");
//     ((void(*)(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jint))clazz->natives["tcui_completed_callback"])(env, clazz, 0);
// }
// #undef OPENBROWSER