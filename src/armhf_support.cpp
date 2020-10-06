#include "armhf_support.h"

#include <game_window_manager.h>
//#include <hybris/hook.h>

// #define WRAP_DEF_ORIG(name, ...) static void (* name ## _orig)(__VA_ARGS__);
// #define WRAP_DEF_FUNC(name, ...) static void name ## _wrap(__VA_ARGS__)
// #define WRAP_DEF_FUNC_C(name, ...) name ## _orig(__VA_ARGS__);

// #define WRAP1(name, sa, da) WRAP_DEF_ORIG(name, da); WRAP_DEF_FUNC(name, sa v1) { WRAP_DEF_FUNC_C(name, (da&) v1); }
// #define WRAP2(name, sa, sb, da, db) WRAP_DEF_ORIG(name, da, db); WRAP_DEF_FUNC(name, sa v1, sb v2) { WRAP_DEF_FUNC_C(name, (da&) v1, (db&) v2); }
// #define WRAP3(name, sa, sb, sc, da, db, dc) WRAP_DEF_ORIG(name, da, db, dc); WRAP_DEF_FUNC(name, sa v1, sb v2, sc v3) { WRAP_DEF_FUNC_C(name, (da&) v1, (db&) v2, (dc&) v3); }
// #define WRAP4(name, sa, sb, sc, sd, da, db, dc, dd) WRAP_DEF_ORIG(name, da, db, dc, dd); WRAP_DEF_FUNC(name, sa v1, sb v2, sc v3, sd v4) { WRAP_DEF_FUNC_C(name, (da&) v1, (db&) v2, (dc&) v3, (dd&) v4); }

// WRAP4(glClearColor, int, int, int, int, float, float, float, float)
// WRAP2(glUniform1f, int, int, int, float)
// WRAP1(glClearDepthf, int, float)
// WRAP2(glDepthRangef, int, int, float, float)


// #define WRAP_INSTALL_GL(name) \
//     (void* (*&)()) name ## _orig = procFunc(#name); \
//     hybris_hook(#name, (void*) name ## _wrap);
#include <glad/glad.h>
#define __COMMON
#include <argrewrite.h>
#include <unordered_map>
#include <map>
static PFNGLBLENDCOLORPROC glBlendColor_armhf_orig;
extern std::map<std::string, void*> eglfuncs;
void ArmhfSupport::install() {
    auto eglproc = GameWindowManager::getManager()->getProcAddrFunc();
    std::map<std::string, void*> &sym = eglfuncs;
    // typedef void (APIENTRYP PFNGLBLENDCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    (void* (*&)()) glBlendColor_armhf_orig = eglproc("glBlendColor");
    // auto x = AutoArgRewritten(glBlendColor_armhf_orig);
    sym["glBlendColor"] = AutoArgRewritten(glBlendColor_armhf_orig);
    typedef void (APIENTRYP PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    static PFNGLCLEARCOLORPROC glClearColor_armhf_orig;
    (void* (*&)()) glClearColor_armhf_orig = eglproc("glClearColor");
    sym["glClearColor"] = AutoArgRewritten(glClearColor_armhf_orig);
    typedef void (APIENTRYP PFNGLCLEARDEPTHFPROC)(GLfloat d);
    static PFNGLCLEARDEPTHFPROC glClearDepthf_armhf_orig;
    (void* (*&)()) glClearDepthf_armhf_orig = eglproc("glClearDepthf");
    sym["glClearDepthf"] = AutoArgRewritten(glClearDepthf_armhf_orig);
    typedef void (APIENTRYP PFNGLDEPTHRANGEFPROC)(GLfloat n, GLfloat f);
    static PFNGLDEPTHRANGEFPROC glDepthRangef_armhf_orig;
    (void* (*&)()) glDepthRangef_armhf_orig = eglproc("glDepthRangef");
    sym["glDepthRangef"] = AutoArgRewritten(glDepthRangef_armhf_orig);
    typedef void (APIENTRYP PFNGLLINEWIDTHPROC)(GLfloat width);
    static PFNGLLINEWIDTHPROC glLineWidth_armhf_orig;
    (void* (*&)()) glLineWidth_armhf_orig = eglproc("glLineWidth");
    sym["glLineWidth"] = AutoArgRewritten(glLineWidth_armhf_orig);
    typedef void (APIENTRYP PFNGLPOLYGONOFFSETPROC)(GLfloat factor, GLfloat units);
    static PFNGLPOLYGONOFFSETPROC glPolygonOffset_armhf_orig;
    (void* (*&)()) glPolygonOffset_armhf_orig = eglproc("glPolygonOffset");
    sym["glPolygonOffset"] = AutoArgRewritten(glPolygonOffset_armhf_orig);
    typedef void (APIENTRYP PFNGLSAMPLECOVERAGEPROC)(GLfloat value, GLboolean invert);
    static PFNGLSAMPLECOVERAGEPROC glSampleCoverage_armhf_orig;
    (void* (*&)()) glSampleCoverage_armhf_orig = eglproc("glSampleCoverage");
    sym["glSampleCoverage"] = AutoArgRewritten(glSampleCoverage_armhf_orig);
    typedef void (APIENTRYP PFNGLTEXPARAMETERFPROC)(GLenum target, GLenum pname, GLfloat param);
    static PFNGLTEXPARAMETERFPROC glTexParameterf_armhf_orig;
    (void* (*&)()) glTexParameterf_armhf_orig = eglproc("glTexParameterf");
    sym["glTexParameterf"] = AutoArgRewritten(glTexParameterf_armhf_orig);
    typedef void (APIENTRYP PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
    static PFNGLUNIFORM1FPROC glUniform1f_armhf_orig;
    (void* (*&)()) glUniform1f_armhf_orig = eglproc("glUniform1f");
    sym["glUniform1f"] = AutoArgRewritten(glUniform1f_armhf_orig);
    typedef void (APIENTRYP PFNGLUNIFORM2FPROC)(GLint location, GLfloat v0, GLfloat v1);
    static PFNGLUNIFORM2FPROC glUniform2f_armhf_orig;
    (void* (*&)()) glUniform2f_armhf_orig = eglproc("glUniform2f");
    sym["glUniform2f"] = AutoArgRewritten(glUniform2f_armhf_orig);
    typedef void (APIENTRYP PFNGLUNIFORM3FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
    static PFNGLUNIFORM3FPROC glUniform3f_armhf_orig;
    (void* (*&)()) glUniform3f_armhf_orig = eglproc("glUniform3f");
    sym["glUniform3f"] = AutoArgRewritten(glUniform3f_armhf_orig);
    typedef void (APIENTRYP PFNGLUNIFORM4FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    static PFNGLUNIFORM4FPROC glUniform4f_armhf_orig;
    (void* (*&)()) glUniform4f_armhf_orig = eglproc("glUniform4f");
    sym["glUniform4f"] = AutoArgRewritten(glUniform4f_armhf_orig);
    typedef void (APIENTRYP PFNGLVERTEXATTRIB1FPROC)(GLuint index, GLfloat x);
    static PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f_armhf_orig;
    (void* (*&)()) glVertexAttrib1f_armhf_orig = eglproc("glVertexAttrib1f");
    sym["glVertexAttrib1f"] = AutoArgRewritten(glVertexAttrib1f_armhf_orig);
    typedef void (APIENTRYP PFNGLVERTEXATTRIB2FPROC)(GLuint index, GLfloat x, GLfloat y);
    static PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f_armhf_orig;
    (void* (*&)()) glVertexAttrib2f_armhf_orig = eglproc("glVertexAttrib2f");
    sym["glVertexAttrib2f"] = AutoArgRewritten(glVertexAttrib2f_armhf_orig);
    typedef void (APIENTRYP PFNGLVERTEXATTRIB3FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
    static PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f_armhf_orig;
    (void* (*&)()) glVertexAttrib3f_armhf_orig = eglproc("glVertexAttrib3f");
    sym["glVertexAttrib3f"] = AutoArgRewritten(glVertexAttrib3f_armhf_orig);
    typedef void (APIENTRYP PFNGLVERTEXATTRIB4FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    static PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f_armhf_orig;
    (void* (*&)()) glVertexAttrib4f_armhf_orig = eglproc("glVertexAttrib4f");
    sym["glVertexAttrib4f"] = AutoArgRewritten(glVertexAttrib4f_armhf_orig);
   // WRAP_INSTALL_GL(glClearColor)
   // WRAP_INSTALL_GL(glUniform1f)
   // WRAP_INSTALL_GL(glClearDepthf)
   // WRAP_INSTALL_GL(glDepthRangef)
}
