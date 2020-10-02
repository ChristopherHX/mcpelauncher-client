#include "hbui_patch.h"
#if 0
#include <hybris/dlfcn.h>
#endif
#include <mcpelauncher/patch_utils.h>
#include <log.h>

void HbuiPatch::install(void *handle) {
#if 0
    void* ptr = linker::dlsym(handle, "_ZN6cohtml17VerifiyLicenseKeyEPKc");
    if (ptr)
        PatchUtils::patchCallInstruction(ptr, (void*) returnTrue, true);
    ptr = linker::dlsym(handle, "_ZN4hbui10LogHandler8WriteLogEN6cohtml7Logging8SeverityEPKcj");
    if (ptr)
        PatchUtils::patchCallInstruction(ptr, (void*) writeLog, true);
#endif
}

void HbuiPatch::writeLog(void* th, int level, const char *what, unsigned int length) {
    Log::log((LogLevel) level, "Cohtml", "%.*s", length, what);
}