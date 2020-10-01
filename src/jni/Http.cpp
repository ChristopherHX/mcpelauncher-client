#include "../JNIBinding.h"
using namespace jnivm;
// Never called since Minecraft 1.13
// Pre 1.13 compatibility

jint com::mojang::android::net::HTTPResponse::getStatus(ENV *env) {
    return 1;
}

std::shared_ptr<jnivm::java::lang::String> com::mojang::android::net::HTTPResponse::getBody(ENV *env) {
    return 0;
}

jint com::mojang::android::net::HTTPResponse::getResponseCode(ENV *env) {
    return 200;
}

std::shared_ptr<jnivm::Array<jnivm::org::apache::http::Header>> com::mojang::android::net::HTTPResponse::getHeaders(ENV *env) {
    return 0;
}

com::mojang::android::net::HTTPRequest::HTTPRequest(ENV *env, jnivm::java::lang::Class* clazz) {
    
}

void com::mojang::android::net::HTTPRequest::setURL(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

void com::mojang::android::net::HTTPRequest::setRequestBody(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

void com::mojang::android::net::HTTPRequest::setCookieData(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

void com::mojang::android::net::HTTPRequest::setContentType(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    
}

std::shared_ptr<jnivm::com::mojang::android::net::HTTPResponse> com::mojang::android::net::HTTPRequest::send(ENV *env, std::shared_ptr<jnivm::java::lang::String> arg0) {
    return 0;
}

void com::mojang::android::net::HTTPRequest::abort(ENV *env) {
    
}