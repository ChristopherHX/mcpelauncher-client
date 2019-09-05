#include "http_request_stub.h"

#include <mcpelauncher/patch_utils.h>
#include <hybris/dlfcn.h>
#include <log.h>

void LinuxHttpRequestHelper::install(void* handle) {
    void* ptr = hybris_dlsym(handle, "_ZN11HTTPRequestC2ERKSs");
    PatchUtils::patchCallInstruction(ptr, (void *) (void (*)(LinuxHttpRequestInternal*, HTTPRequest*)) [](
            LinuxHttpRequestInternal* th, HTTPRequest* request) {
        new(th)LinuxHttpRequestInternal(request);
    }, true);

    ptr = hybris_dlsym(handle, "_ZN11HTTPRequest4sendEv");
    PatchUtils::patchCallInstruction(ptr, PatchUtils::memberFuncCast(&LinuxHttpRequestInternal::send), true);

    ptr = hybris_dlsym(handle, "_ZN11HTTPRequest5abortEv");
    PatchUtils::patchCallInstruction(ptr, PatchUtils::memberFuncCast(&LinuxHttpRequestInternal::abort), true);
}

void LinuxHttpRequestInternal::send() {
    Log::trace("Launcher", "HTTPRequestInternalAndroid::send stub called");
}

void LinuxHttpRequestInternal::abort() {
    Log::trace("Launcher", "HTTPRequestInternalAndroid::abort stub called");
}