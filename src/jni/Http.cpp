#include "../JNIBinding.h"
// Never called since Minecraft 1.13
// Pre 1.13 compatibility

jint com::mojang::android::net::HTTPResponse::getStatus(jnivm::ENV* env) {
    return 1;
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::android::net::HTTPResponse::getBody(jnivm::ENV* env) {
    return 0;
}

jint com::mojang::android::net::HTTPResponse::getResponseCode(jnivm::ENV* env) {
    return 200;
}

jnivm::Array<jnivm::org::apache::http::Header*>* com::mojang::android::net::HTTPResponse::getHeaders(jnivm::ENV* env) {
    return 0;
}

com::mojang::android::net::HTTPRequest::HTTPRequest(jnivm::ENV* env, jnivm::java::lang::Class* clazz) {
    
}

void com::mojang::android::net::HTTPRequest::setURL(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

void com::mojang::android::net::HTTPRequest::setRequestBody(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

void com::mojang::android::net::HTTPRequest::setCookieData(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

void com::mojang::android::net::HTTPRequest::setContentType(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

jnivm::com::mojang::android::net::HTTPResponse* com::mojang::android::net::HTTPRequest::send(jnivm::ENV* env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    return 0;
}

void com::mojang::android::net::HTTPRequest::abort(jnivm::ENV* env) {
    
}

// Entry points for jnivm

extern "C" jint jnivm_com_mojang_android_net_HTTPResponse_getStatus(jnivm::ENV* env, jnivm::com::mojang::android::net::HTTPResponse* obj, jvalue* values) {
    return obj->getStatus(env);
}
extern "C" std::shared_ptr<jnivm::java::lang::String> jnivm_com_mojang_android_net_HTTPResponse_getBody(jnivm::ENV* env, jnivm::com::mojang::android::net::HTTPResponse* obj, jvalue* values) {
    return obj->getBody(env);
}
extern "C" jint jnivm_com_mojang_android_net_HTTPResponse_getResponseCode(jnivm::ENV* env, jnivm::com::mojang::android::net::HTTPResponse* obj, jvalue* values) {
    return obj->getResponseCode(env);
}
extern "C" jnivm::Array<jnivm::org::apache::http::Header*>* jnivm_com_mojang_android_net_HTTPResponse_getHeaders(jnivm::ENV* env, jnivm::com::mojang::android::net::HTTPResponse* obj, jvalue* values) {
    return obj->getHeaders(env);
}
extern "C" jobject jnivm_com_mojang_android_net_HTTPRequest_HTTPRequest(jnivm::ENV* env, jnivm::java::lang::Class* clazz, jvalue* values) {
    return (jobject)new com::mojang::android::net::HTTPRequest(env, clazz);
}
extern "C" void jnivm_com_mojang_android_net_HTTPRequest_setURL(jnivm::ENV* env, jnivm::com::mojang::android::net::HTTPRequest* obj, jvalue* values) {
    return obj->setURL(env, (std::shared_ptr<jnivm::java::lang::String>&)values[0]);
}
extern "C" void jnivm_com_mojang_android_net_HTTPRequest_setRequestBody(jnivm::ENV* env, jnivm::com::mojang::android::net::HTTPRequest* obj, jvalue* values) {
    return obj->setRequestBody(env, (std::shared_ptr<jnivm::java::lang::String>&)values[0]);
}
extern "C" void jnivm_com_mojang_android_net_HTTPRequest_setCookieData(jnivm::ENV* env, jnivm::com::mojang::android::net::HTTPRequest* obj, jvalue* values) {
    return obj->setCookieData(env, (std::shared_ptr<jnivm::java::lang::String>&)values[0]);
}
extern "C" void jnivm_com_mojang_android_net_HTTPRequest_setContentType(jnivm::ENV* env, jnivm::com::mojang::android::net::HTTPRequest* obj, jvalue* values) {
    return obj->setContentType(env, (std::shared_ptr<jnivm::java::lang::String>&)values[0]);
}
extern "C" jnivm::com::mojang::android::net::HTTPResponse* jnivm_com_mojang_android_net_HTTPRequest_send(jnivm::ENV* env, jnivm::com::mojang::android::net::HTTPRequest* obj, jvalue* values) {
    return obj->send(env, (std::shared_ptr<jnivm::java::lang::String>&)values[0]);
}
extern "C" void jnivm_com_mojang_android_net_HTTPRequest_abort(jnivm::ENV* env, jnivm::com::mojang::android::net::HTTPRequest* obj, jvalue* values) {
    return obj->abort(env);
}