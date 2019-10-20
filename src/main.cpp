#include <log.h>
#include <hybris/hook.h>
#include <hybris/dlfcn.h>
#include <dlfcn.h>
#include <game_window_manager.h>
#include <argparser.h>
#include <mcpelauncher/minecraft_utils.h>
#include <mcpelauncher/minecraft_version.h>
#include <mcpelauncher/crash_handler.h>
#include <mcpelauncher/path_helper.h>
#include <minecraft/Common.h>
#include <minecraft/MinecraftGame.h>
#include <minecraft/ClientInstance.h>
#include <mcpelauncher/mod_loader.h>
#include "client_app_platform.h"
#include "xbox_live_patches.h"
#include "store.h"
#include "window_callbacks.h"
#include "http_request_stub.h"
#include "splitscreen_patch.h"
#include "gl_core_patch.h"
#include "xbox_live_helper.h"
#include "xbox_shutdown_patch.h"
#include "tts_patch.h"
#include "shader_error_patch.h"
#include "hbui_patch.h"
#ifdef USE_ARMHF_SUPPORT
#include "armhf_support.h"
#endif
#ifdef __i386__
#include "cpuid.h"
#include "legacy/legacy_patches.h"
#include "minecraft_game_wrapper.h"
#include "texel_aa_patch.h"
#endif
#include <build_info.h>
#include "native_activity.h"
#include <regex>

const char* ParseJNIType(const char * cur, const char* end, std::string & type){
    switch (*cur) {
    case 'V':
        type = "void";
        break;
    case 'Z':
        type = "jboolean";
        break;
    case 'B':
        type = "jbyte";
        break;
    case 'S':
        type = "jshort";
        break;
    case 'I':
        type = "jint";
        break;
    case 'J':
        type = "jlong";
        break;
    case 'F':
        type = "jfloat";
        break;
    case 'D':
        type = "jdouble";
        break;
    case '[':
        cur = ParseJNIType(cur + 1, end, type);
        type = "Array<" + type + ">*";
        break;
    case 'L':
        auto cend = std::find(cur, end, ';');
        type = "Object<" + std::regex_replace(std::string(cur + 1, cend), std::regex("(/|\\$)"), "::") + ">*";
        cur = cend;
        break;
    }
    return cur;
}

void Declare(JNIEnv* env, const char * signature){
    for(const char* cur = signature, *end = cur + strlen(cur); cur != end; cur++) {
        if(*cur == 'L') {
            auto cend = std::find(cur, end, ';');
            std::string classpath(cur + 1, cend);
            env->FindClass(classpath.data());
            cur = cend;
        }
    }
}

class Method {
public:
    std::string name;
    std::string signature;
    bool _static = false;
    void * nativehandle = 0;

    std::string GenerateHeader(const std::string & cname) {
        std::ostringstream ss;
        std::vector<std::string> parameters;
        std::string rettype;
        bool inarg = false;
        for(const char * cur = signature.data(), *end = cur + signature.length(); cur != end; cur++) {
            std::string type;
            switch (*cur) {
            case '(':
                inarg = true;
                break;
            case ')':
                inarg = false;
                break;
            default:
                cur = ParseJNIType(cur, end, type);
            }
            if(!type.empty()) {
                if(inarg) {
                    parameters.emplace_back(std::move(type));
                } else {
                    rettype = std::move(type);
                }
            }
        }
        if(_static) {
            ss << "static ";
        }
        if(name == "<init>") {
            ss << cname;
        } else {
            ss << rettype << " " << name;
        }
        ss << "(";
        for(int i = 0; i < parameters.size(); i++) {
            if(i != 0) {
                ss << ", ";
            }
            ss << parameters[i];
        }
        ss << ")" << ";";
        return ss.str();
    }

    std::string GenerateStubs(std::string scope, const std::string & cname) {
        std::ostringstream ss;
        std::vector<std::string> parameters;
        std::string rettype;
        bool inarg = false;
        for(const char * cur = signature.data(), *end = cur + signature.length(); cur != end; cur++) {
            std::string type;
            switch (*cur) {
            case '(':
                inarg = true;
                break;
            case ')':
                inarg = false;
                break;
            default:
                cur = ParseJNIType(cur, end, type);
            }
            if(!type.empty()) {
                if(inarg) {
                    parameters.emplace_back(std::move(type));
                } else {
                    rettype = std::move(type);
                }
            }
        }
        if(name == "<init>") {
            ss << scope << cname;
        } else {
            ss << rettype << " " << scope << name;
        }
        ss << "(";
        for(int i = 0; i < parameters.size(); i++) {
            if(i != 0) {
                ss << ", ";
            }
            ss << parameters[i] << " arg" << i;
        }
        ss << ") {\n    \n}\n\n";
        return ss.str();
    }
    
    std::string GenerateJNIBinding(std::string scope, const std::string & cname) {
        std::ostringstream ss;
        std::vector<std::string> parameters;
        std::string rettype;
        bool inarg = false;
        for(const char * cur = signature.data(), *end = cur + signature.length(); cur != end; cur++) {
            std::string type;
            switch (*cur) {
            case '(':
                inarg = true;
                break;
            case ')':
                inarg = false;
                break;
            default:
                cur = ParseJNIType(cur, end, type);
            }
            if(!type.empty()) {
                if(inarg) {
                    parameters.emplace_back(std::move(type));
                } else {
                    rettype = std::move(type);
                }
            }
        }
        ss << "extern \"C\" ";
        auto cl = scope.substr(0, scope.length() - 2);
        if(name == "<init>") {
            scope += cname;
        } else {
            scope += name;
        }
        if(name == "<init>") {
            ss << "void ";
        } else {
            ss << rettype << " ";
        }
        ss << std::regex_replace(scope, std::regex("::"), "_") << "(";
        if(!_static) {
            ss << "Object<" << cl << ">* obj, ";
        }
        ss << "va_list list) {\n    using Param = std::tuple<";
        if(!_static) {
            ss << cl << "*";
            if(parameters.size()) {
                ss << ", ";
            }
        }
        for(int i = 0; i < parameters.size(); i++) {
            if(i != 0) {
                ss << ", ";
            }
            ss << parameters[i];
        }
        ss << ">;\n    Param param;\n";
        if(!_static) {
            ss << "    std::get<0>(param) = obj->value;\n";
        }
        for(int i = 0; i < parameters.size(); i++) {
            ss << "    std::get<" << (_static ? i : (i + 1)) << ">(param) = va_arg(list, " << (parameters[i] == "jboolean" ? "int" : parameters[i]) << ");\n";
        }
        ss << "    return std::apply(&" << (name == "<init>" ? "Create<Param>::create" : scope) << ", param);\n}\n\n";
        return ss.str();
    }
};

class Field {
public:
    std::string name;
    std::string type;
    bool _static = false;
    void * getnativehandle;
    void * setnativehandle;

    std::string GenerateHeader() {
        std::ostringstream ss;
        std::string ctype;
        ParseJNIType(type.data(), type.data() + type.length(), ctype);
        if(_static) {
            ss << "static ";
        }
        ss << ctype << " " << name << ";";
        return ss.str();
    }

    std::string GenerateJNIBinding(std::string scope) {
        std::ostringstream ss;
        std::string rettype;
        ParseJNIType(type.data(), type.data() + type.length(), rettype);
        auto cl = scope.substr(0, scope.length() - 2);
        scope = std::regex_replace(scope, std::regex("::"), "_") + name;
        ss << "extern \"C\" " << rettype << " get_" << scope << "(";
        if(!_static) {
            ss << "Object<" << cl << ">* obj";
        }
        ss << ") {\n    return ";
        if(_static) {
            ss << cl << "::" << name;
        } else {
            ss << "obj->value->" << name;
        }
        ss << ";\n}\n\n";
        ss << "extern \"C\" void set_" << scope << "(";
        if(!_static) {
            ss << "Object<" << cl << ">* obj, ";
        }
        ss << rettype << " value) {\n    ";
        if(_static) {
            ss << cl << "::" << name;
        } else {
            ss << "obj->value->" << name;
        }
        ss << " = value;\n}\n\n";
        return ss.str();
    }
};

class Class {
public:
    std::string name;
    std::string nativeprefix;
    std::vector<std::shared_ptr<Class>> classes;
    std::vector<std::shared_ptr<Field>> fields;
    std::vector<std::shared_ptr<Method>> methods;

    std::string GenerateHeader(std::string scope) {
        std::ostringstream ss;
        ss << "class " << scope << name << " {\npublic:\n";
        for (auto &field : fields) {
            ss << std::regex_replace(field->GenerateHeader(), std::regex("(^|\n)([^\n]+)"), "$1    $2");
            ss << "\n";
        }
        for (auto &method : methods) {
            ss << std::regex_replace(method->GenerateHeader(name), std::regex("(^|\n)([^\n]+)"), "$1    $2");
            ss << "\n";
        }
        ss << "};";
        return ss.str();
    }

    std::string GeneratePreDeclaration() {
        std::ostringstream ss;
        ss << "class " << name << ";";
        return ss.str();
    }

    std::string GenerateStubs(std::string scope) {
        std::ostringstream ss;
        scope += name + "::";
        for (auto &cl : classes) {
            ss << cl->GenerateStubs(scope);
        }
        for (auto &method : methods) {
            ss << method->GenerateStubs(scope, name);
        }
        return ss.str();
    }

    std::string GenerateJNIBinding(std::string scope) {
        std::ostringstream ss;
        scope += name + "::";
        for (auto &cl : classes) {
            ss << cl->GenerateJNIBinding(scope);
        }
        for (auto &field : fields) {
            ss << field->GenerateJNIBinding(scope);
        }
        for (auto &method : methods) {
            ss << method->GenerateJNIBinding(scope, name);
        }
        return ss.str();
    }
};

class Namespace {
    public:
    std::string name;
    std::vector<std::shared_ptr<Namespace>> namespaces;
    std::vector<std::shared_ptr<Class>> classes;

    std::string GenerateHeader(std::string scope) {
        std::ostringstream ss;
        if(name.length()) {
            scope += name + "::";
        }
        for (auto &cl : classes) {
            ss << cl->GenerateHeader(scope);
            ss << "\n";
        }
        for (auto &np : namespaces) {
            ss << np->GenerateHeader(scope);
            ss << "\n";
        }
        return ss.str();
    }

    std::string GeneratePreDeclaration() {
        std::ostringstream ss;
        bool indent = name.length();
        if(indent) {
            ss << "namespace " << name << " {\n";
        }
        for (auto &cl : classes) {
            ss << (indent ? std::regex_replace(cl->GeneratePreDeclaration(), std::regex("(^|\n)([^\n]+)"), "$1    $2") : cl->GeneratePreDeclaration());
            ss << "\n";
        }
        for (auto &np : namespaces) {
            ss << (indent ? std::regex_replace(np->GeneratePreDeclaration(), std::regex("(^|\n)([^\n]+)"), "$1    $2") : np->GeneratePreDeclaration());
            ss << "\n";
        }
        if(indent) {
            ss << "}";
        }
        return ss.str();
    }

    std::string GenerateStubs(std::string scope) {
        std::ostringstream ss;
        if(name.length()) {
            scope += name + "::";
        }
        for (auto &cl : classes) {
            ss << cl->GenerateStubs(scope);
        }
        for (auto &np : namespaces) {
            ss << np->GenerateStubs(scope);
        }
        return ss.str();
    }

    std::string GenerateJNIBinding(std::string scope) {
        std::ostringstream ss;
        if(name.length()) {
            scope += name + "::";
        }
        for (auto &cl : classes) {
            ss << cl->GenerateJNIBinding(scope);
        }
        for (auto &np : namespaces) {
            ss << np->GenerateJNIBinding(scope);
        }
        return ss.str();
    }
};

template<class T> class Object {
public:
    // Object(jclass cl, T* value);
    jclass cl;
    T* value;
};

template<class T> class Array : public Object<std::vector<T>> {
public:
    using Object<std::vector<T>>::Object;
    T * data() {
        return Object<std::vector<T>>::value->data();
    }
    size_t length() {
        return Object<std::vector<T>>::value->size();
    }
};

static std::unique_ptr<ClientAppPlatform> appPlatform;

void printVersionInfo();

 jint GetVersion(JNIEnv *) {
Log::trace("JNIENVSTUB", "GetVersion");
};
        jclass DefineClass(JNIEnv*, const char*, jobject, const jbyte*,
                            jsize) {
Log::trace("JNIENVSTUB", "DefineClass");
};
        jclass FindClass(JNIEnv* env, const char* name) {
            Log::trace("JNIENVSTUB", "FindClass %s", name);
            auto prefix = std::regex_replace(name, std::regex("(/|\\$)"), "_") + '_';
            auto end = name + strlen(name);
            auto pos = name;
            Namespace * cur = (Namespace*)env->functions->reserved0;
            while((pos = std::find(name, end, '/')) != end) {
                std::string sname = std::string(name, pos);
                auto namsp = std::find_if(cur->namespaces.begin(), cur->namespaces.end(), [&sname](std::shared_ptr<Namespace>& namesp) {
                    return namesp->name == sname;
                });
                Namespace * next;
                if(namsp != cur->namespaces.end()) {
                    next = namsp->get();
                } else {
                    cur->namespaces.emplace_back(new Namespace());
                    next = cur->namespaces.back().get();
                    next->name = std::move(sname);
                }
                cur = next;
                name = pos + 1;
            }
            Class * curc = nullptr;
            do {
                pos = std::find(name, end, '$');
                std::string sname = std::string(name, pos);
                Class * next;
                if(curc) {
                    auto cl = std::find_if(curc->classes.begin(), curc->classes.end(), [&sname](std::shared_ptr<Class>& namesp) {
                        return namesp->name == sname;
                    });
                    if(cl != curc->classes.end()) {
                        next = cl->get();
                    } else {
                        curc->classes.emplace_back(new Class());
                        next = curc->classes.back().get();
                        next->name = std::move(sname);
                    }
                } else {
                    auto cl = std::find_if(cur->classes.begin(), cur->classes.end(), [&sname](std::shared_ptr<Class>& namesp) {
                        return namesp->name == sname;
                    });
                    if(cl != cur->classes.end()) {
                        next = cl->get();
                    } else {
                        cur->classes.emplace_back(new Class());
                        next = cur->classes.back().get();
                        next->name = std::move(sname);
                    }
                }
                curc = next;
                name = pos + 1;
            } while(pos != end);
            curc->nativeprefix = std::move(prefix);
            return (jclass)curc;
        };
        jmethodID FromReflectedMethod(JNIEnv*, jobject) {
Log::trace("JNIENVSTUB", "FromReflectedMethod");
};
        jfieldID FromReflectedField(JNIEnv*, jobject) {
Log::trace("JNIENVSTUB", "FromReflectedField");
};
        /* spec doesn't show jboolean parameter */
        jobject ToReflectedMethod(JNIEnv*, jclass, jmethodID, jboolean) {
Log::trace("JNIENVSTUB", "ToReflectedMethod");
};
        jclass GetSuperclass(JNIEnv*, jclass) {
Log::trace("JNIENVSTUB", "GetSuperclass");
};
        jboolean IsAssignableFrom(JNIEnv*, jclass, jclass) {
Log::trace("JNIENVSTUB", "IsAssignableFrom");
};
        /* spec doesn't show jboolean parameter */
        jobject ToReflectedField(JNIEnv*, jclass, jfieldID, jboolean) {
Log::trace("JNIENVSTUB", "ToReflectedField");
};
        jint Throw(JNIEnv*, jthrowable) {
Log::trace("JNIENVSTUB", "Throw");
};
        jint ThrowNew(JNIEnv *, jclass, const char *) {
Log::trace("JNIENVSTUB", "ThrowNew");
};
        jthrowable ExceptionOccurred(JNIEnv*) {
Log::trace("JNIENVSTUB", "ExceptionOccurred");
};
        void ExceptionDescribe(JNIEnv*) {
Log::trace("JNIENVSTUB", "ExceptionDescribe");
};
        void ExceptionClear(JNIEnv*) {
Log::trace("JNIENVSTUB", "ExceptionClear");
};
        void FatalError(JNIEnv*, const char*) {
Log::trace("JNIENVSTUB", "FatalError");
};
        jint PushLocalFrame(JNIEnv*, jint) {
Log::trace("JNIENVSTUB", "PushLocalFrame");
};
        jobject PopLocalFrame(JNIEnv*, jobject) {
Log::trace("JNIENVSTUB", "PopLocalFrame");
};
        jobject NewGlobalRef(JNIEnv*, jobject obj) {
Log::trace("JNIENVSTUB", "NewGlobalRef %d", (int)obj);
        return obj;
};
        void DeleteGlobalRef(JNIEnv*, jobject) {
Log::trace("JNIENVSTUB", "DeleteGlobalRef");
};
        void DeleteLocalRef(JNIEnv*, jobject) {
Log::trace("JNIENVSTUB", "DeleteLocalRef");
};
        jboolean IsSameObject(JNIEnv*, jobject, jobject) {
Log::trace("JNIENVSTUB", "IsSameObject");
};
        jobject NewLocalRef(JNIEnv*, jobject) {
Log::trace("JNIENVSTUB", "NewLocalRef");
};
        jint EnsureLocalCapacity(JNIEnv*, jint) {
Log::trace("JNIENVSTUB", "EnsureLocalCapacity");
};
jobject AllocObject(JNIEnv* env, jclass cl) {
    Log::trace("JNIENVSTUB", "AllocObject");
    // return (jobject) new Object<> { cl = cl };
};
        jobject NewObject(JNIEnv*, jclass, jmethodID, ...) {
Log::trace("JNIENVSTUB", "NewObject");
};
        jobject NewObjectV(JNIEnv*, jclass, jmethodID, va_list) {
Log::trace("JNIENVSTUB", "NewObjectV");
};
        jobject NewObjectA(JNIEnv*, jclass, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "NewObjectA");
};
jclass GetObjectClass(JNIEnv* env, jobject jo) {
    Log::trace("JNIENVSTUB", "GetObjectClass %d", jo);
    return ((Object<void>*)jo)->cl;
};
        jboolean IsInstanceOf(JNIEnv*, jobject, jclass) {
Log::trace("JNIENVSTUB", "IsInstanceOf");
};
jmethodID GetMethodID(JNIEnv*env, jclass cl, const char* str0, const char* str1) {
        std::string & classname = ((Class*)cl)->name;
        Log::trace("JNIENVSTUB", "GetMethodID(%s, '%s','%s')", classname.data(), str0, str1);
        auto cur = (Class*)cl;
        auto sname = str0;
        auto ssig = str1;
        auto ccl = std::find_if(cur->methods.begin(), cur->methods.end(), [&sname, &ssig](std::shared_ptr<Method>& namesp) {
            return namesp->name == sname && namesp->signature == ssig;
        });
        Method * next;
        if(ccl != cur->methods.end()) {
            next = ccl->get();
        } else {
            cur->methods.emplace_back(new Method());
            next = cur->methods.back().get();
            next->name = std::move(sname);
            next->signature = std::move(ssig);
            Declare(env, next->signature.data());
            auto This = dlopen(nullptr, RTLD_LAZY);
            std::string symbol = ((Class*)cl)->nativeprefix + (!strcmp(str0, "<init>") ? classname : str0);
            if(!(next->nativehandle = dlsym(This, symbol.data()))) {
                Log::trace("JNIBinding", "Unresolved symbol %s", symbol.data());
                if(symbol == "android_app_NativeActivity_getApplicationContext") {
                        std::cout << ((Namespace*&)env->functions->reserved0)->GeneratePreDeclaration();
                        std::cout << ((Namespace*&)env->functions->reserved0)->GenerateHeader("");
                        std::cout << ((Namespace*&)env->functions->reserved0)->GenerateStubs("");
                        std::cout << ((Namespace*&)env->functions->reserved0)->GenerateJNIBinding("");
                }
            }
            dlclose(This);
        }
        return (jmethodID)next;
};
        jobject CallObjectMethod(JNIEnv*, jobject, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallObjectMethod");
};
jobject CallObjectMethodV(JNIEnv*, jobject obj, jmethodID id, va_list param) {
    auto mid = ((Method*)id);
    Log::trace("JNIENVSTUB", "CallObjectMethodV %s", mid->name.data());
    if(mid->nativehandle) {
        return ((jobject(*)(jobject, va_list))mid->nativehandle)(obj, param);
    }
};
        jobject CallObjectMethodA(JNIEnv*, jobject, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallObjectMethodA");
};
        jboolean CallBooleanMethod(JNIEnv*, jobject, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallBooleanMethod");
};
        jboolean CallBooleanMethodV(JNIEnv*, jobject obj, jmethodID id, va_list param) {
    auto mid = ((Method*)id);
    Log::trace("JNIENVSTUB", "CallObjectMethodV %s", mid->name.data());
    if(mid->nativehandle) {
        return ((jboolean(*)(jobject, va_list))mid->nativehandle)(obj, param);
    }};
        jboolean CallBooleanMethodA(JNIEnv*, jobject, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallBooleanMethodA");
};
        jbyte CallByteMethod(JNIEnv*, jobject, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallByteMethod");
};
        jbyte CallByteMethodV(JNIEnv*, jobject obj, jmethodID id, va_list param) {
    auto mid = ((Method*)id);
    Log::trace("JNIENVSTUB", "CallObjectMethodV %s", mid->name.data());
    if(mid->nativehandle) {
        return ((jbyte(*)(jobject, va_list))mid->nativehandle)(obj, param);
    }
        };
        jbyte CallByteMethodA(JNIEnv*, jobject, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallByteMethodA");
};
        jchar CallCharMethod(JNIEnv*, jobject, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallCharMethod");
};
        jchar CallCharMethodV(JNIEnv*, jobject obj, jmethodID id, va_list param) {
    auto mid = ((Method*)id);
    Log::trace("JNIENVSTUB", "CallObjectMethodV %s", mid->name.data());
    if(mid->nativehandle) {
        return ((jchar(*)(jobject, va_list))mid->nativehandle)(obj, param);
    }
};
        jchar CallCharMethodA(JNIEnv*, jobject, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallCharMethodA");
};
        jshort CallShortMethod(JNIEnv*, jobject, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallShortMethod");
};
        jshort CallShortMethodV(JNIEnv*, jobject obj, jmethodID id, va_list param) {
    auto mid = ((Method*)id);
    Log::trace("JNIENVSTUB", "CallObjectMethodV %s", mid->name.data());
    if(mid->nativehandle) {
        return ((jshort(*)(jobject, va_list))mid->nativehandle)(obj, param);
    }
};
        jshort CallShortMethodA(JNIEnv*, jobject, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallShortMethodA");
};
        jint CallIntMethod(JNIEnv*, jobject, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallIntMethod");
};
        jint CallIntMethodV(JNIEnv*, jobject obj, jmethodID id, va_list param) {
    Log::trace("JNIENVSTUB", "CallIntMethodV %s", ((Method*)id)->name.data());
    auto mid = ((Method*)id);
    if(mid->nativehandle) {
        return ((jint(*)(jobject, va_list))mid->nativehandle)(obj, param);
    }
};
        jint CallIntMethodA(JNIEnv*, jobject, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallIntMethodA");
};
        jlong CallLongMethod(JNIEnv*, jobject, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallLongMethod");
};
        jlong CallLongMethodV(JNIEnv*, jobject obj, jmethodID id, va_list param) {
    auto mid = ((Method*)id);
    Log::trace("JNIENVSTUB", "CallObjectMethodV %s", mid->name.data());
    if(mid->nativehandle) {
        return ((jlong(*)(jobject, va_list))mid->nativehandle)(obj, param);
    }
};
        jlong CallLongMethodA(JNIEnv*, jobject, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallLongMethodA");
};
        jfloat CallFloatMethod(JNIEnv*, jobject, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallFloatMethod");
};
        jfloat CallFloatMethodV(JNIEnv*, jobject obj, jmethodID id, va_list param) {
    auto mid = ((Method*)id);
    Log::trace("JNIENVSTUB", "CallObjectMethodV %s", mid->name.data());
    if(mid->nativehandle) {
        return ((jfloat(*)(jobject, va_list))mid->nativehandle)(obj, param);
    }
};
        jfloat CallFloatMethodA(JNIEnv*, jobject, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallFloatMethodA");
};
        jdouble CallDoubleMethod(JNIEnv*, jobject, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallDoubleMethod");
};
        jdouble CallDoubleMethodV(JNIEnv*, jobject obj, jmethodID id, va_list param) {
    auto mid = ((Method*)id);
    Log::trace("JNIENVSTUB", "CallObjectMethodV %s", mid->name.data());
    if(mid->nativehandle) {
        return ((jfloat(*)(jobject, va_list))mid->nativehandle)(obj, param);
    }
};
        jdouble CallDoubleMethodA(JNIEnv*, jobject, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallDoubleMethodA");
};
        void CallVoidMethod(JNIEnv*, jobject, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallVoidMethod");
};
        void CallVoidMethodV(JNIEnv*, jobject obj, jmethodID id, va_list param) {
    auto mid = ((Method*)id);
    Log::trace("JNIENVSTUB", "CallObjectMethodV %s", mid->name.data());
    if(mid->nativehandle) {
        return ((void(*)(jobject, va_list))mid->nativehandle)(obj, param);
    }
};
        void CallVoidMethodA(JNIEnv*, jobject, jmethodID id, jvalue*) {
    Log::trace("JNIENVSTUB", "CallVoidMethodA %s", ((Method*)id)->name.data());
};
        jobject CallNonvirtualObjectMethod(JNIEnv*, jobject, jclass,
                            jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallNonvirtualObjectMethod");
};
        jobject CallNonvirtualObjectMethodV(JNIEnv*, jobject, jclass,
                            jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallNonvirtualObjectMethodV");
};
        jobject CallNonvirtualObjectMethodA(JNIEnv*, jobject, jclass,
                            jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallNonvirtualObjectMethodA");
};
        jboolean CallNonvirtualBooleanMethod(JNIEnv*, jobject, jclass,
                            jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallNonvirtualBooleanMethod");
};
        jboolean CallNonvirtualBooleanMethodV(JNIEnv*, jobject, jclass,
                            jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallNonvirtualBooleanMethodV");
};
        jboolean CallNonvirtualBooleanMethodA(JNIEnv*, jobject, jclass,
                            jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallNonvirtualBooleanMethodA");
};
        jbyte CallNonvirtualByteMethod(JNIEnv*, jobject, jclass,
                            jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallNonvirtualByteMethod");
};
        jbyte CallNonvirtualByteMethodV(JNIEnv*, jobject, jclass,
                            jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallNonvirtualByteMethodV");
};
        jbyte CallNonvirtualByteMethodA(JNIEnv*, jobject, jclass,
                            jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallNonvirtualByteMethodA");
};
        jchar CallNonvirtualCharMethod(JNIEnv*, jobject, jclass,
                            jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallNonvirtualCharMethod");
};
        jchar CallNonvirtualCharMethodV(JNIEnv*, jobject, jclass,
                            jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallNonvirtualCharMethodV");
};
        jchar CallNonvirtualCharMethodA(JNIEnv*, jobject, jclass,
                            jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallNonvirtualCharMethodA");
};
        jshort CallNonvirtualShortMethod(JNIEnv*, jobject, jclass,
                            jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallNonvirtualShortMethod");
};
        jshort CallNonvirtualShortMethodV(JNIEnv*, jobject, jclass,
                            jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallNonvirtualShortMethodV");
};
        jshort CallNonvirtualShortMethodA(JNIEnv*, jobject, jclass,
                            jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallNonvirtualShortMethodA");
};
        jint CallNonvirtualIntMethod(JNIEnv*, jobject, jclass,
                            jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallNonvirtualIntMethod");
};
        jint CallNonvirtualIntMethodV(JNIEnv*, jobject, jclass,
                            jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallNonvirtualIntMethodV");
};
        jint CallNonvirtualIntMethodA(JNIEnv*, jobject, jclass,
                            jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallNonvirtualIntMethodA");
};
        jlong CallNonvirtualLongMethod(JNIEnv*, jobject, jclass,
                            jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallNonvirtualLongMethod");
};
        jlong CallNonvirtualLongMethodV(JNIEnv*, jobject, jclass,
                            jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallNonvirtualLongMethodV");
};
        jlong CallNonvirtualLongMethodA(JNIEnv*, jobject, jclass,
                            jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallNonvirtualLongMethodA");
};
        jfloat CallNonvirtualFloatMethod(JNIEnv*, jobject, jclass,
                            jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallNonvirtualFloatMethod");
};
        jfloat CallNonvirtualFloatMethodV(JNIEnv*, jobject, jclass,
                            jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallNonvirtualFloatMethodV");
};
        jfloat CallNonvirtualFloatMethodA(JNIEnv*, jobject, jclass,
                            jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallNonvirtualFloatMethodA");
};
        jdouble CallNonvirtualDoubleMethod(JNIEnv*, jobject, jclass,
                            jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallNonvirtualDoubleMethod");
};
        jdouble CallNonvirtualDoubleMethodV(JNIEnv*, jobject, jclass,
                            jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallNonvirtualDoubleMethodV");
};
        jdouble CallNonvirtualDoubleMethodA(JNIEnv*, jobject, jclass,
                            jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallNonvirtualDoubleMethodA");
};
        void CallNonvirtualVoidMethod(JNIEnv*, jobject, jclass,
                            jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallNonvirtualVoidMethod");
};
        void CallNonvirtualVoidMethodV(JNIEnv*, jobject, jclass,
                            jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallNonvirtualVoidMethodV");
};
        void CallNonvirtualVoidMethodA(JNIEnv*, jobject, jclass,
                            jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallNonvirtualVoidMethodA");
};
jfieldID GetFieldID(JNIEnv* env, jclass cl, const char* name, const char* type) {
    std::string & classname = ((Class*)cl)->name;
    Log::trace("JNIENVSTUB", "GetFieldID(%s, '%s','%s')", classname.data(), name, type);
    auto cur = (Class*)cl;
    auto sname = name;
    auto ssig = type;
    auto ccl = std::find_if(cur->fields.begin(), cur->fields.end(), [&sname, &ssig](std::shared_ptr<Field>& namesp) {
        return namesp->name == sname && namesp->type == ssig;
    });
    Field * next;
    if(ccl != cur->fields.end()) {
        next = ccl->get();
    } else {
        cur->fields.emplace_back(new Field());
        next = cur->fields.back().get();
        next->name = std::move(sname);
        next->type = std::move(ssig);
        Declare(env, next->type.data());
        auto This = dlopen(nullptr, RTLD_LAZY);
        std::string symbol = ((Class*)cl)->nativeprefix + name;
        std::string gsymbol = "get_" + symbol;
        std::string ssymbol = "set_" + symbol;
        if(!(next->setnativehandle = dlsym(This, ssymbol.data()))) {
            Log::trace("JNIBinding", "Unresolved symbol %s", symbol.data());
        }
        if(!(next->getnativehandle = dlsym(This, gsymbol.data()))) {
            Log::trace("JNIBinding", "Unresolved symbol %s", symbol.data());
        }
        dlclose(This);
    }
    return (jfieldID)next;
};

template<class T> T GetField(JNIEnv*, jobject obj, jfieldID id) {
    auto fid = ((Field*)id);
    Log::trace("JNIENVSTUB", "GetField %s", fid->name.data());
    if(fid->getnativehandle) {
        return ((T(*)(jobject))fid->getnativehandle)(obj);
    }
}

template<class T> void SetField(JNIEnv*, jobject obj, jfieldID id, T value) {
    auto fid = ((Field*)id);
    Log::trace("JNIENVSTUB", "SetField %s", fid->name.data());
    if(fid->getnativehandle) {
        ((void(*)(jobject, T))fid->setnativehandle)(obj, value);
    }
}

jmethodID GetStaticMethodID(JNIEnv* env, jclass cl, const char* str0, const char* str1) {
    std::string & classname = ((Class*)cl)->name;
    Log::trace("JNIENVSTUB", "GetStaticMethodID(%s, '%s','%s')", classname.data(), str0, str1);
    auto cur = (Class*)cl;
    auto sname = str0;
    auto ssig = str1;
    auto ccl = std::find_if(cur->methods.begin(), cur->methods.end(), [&sname, &ssig](std::shared_ptr<Method>& namesp) {
        return namesp->name == sname && namesp->signature == ssig;
    });
    Method * next;
    if(ccl != cur->methods.end()) {
        next = ccl->get();
    } else {
        cur->methods.emplace_back(new Method());
        next = cur->methods.back().get();
        next->name = std::move(sname);
        next->signature = std::move(ssig);
        next->_static = true;
        Declare(env, next->signature.data());
        auto This = dlopen(nullptr, RTLD_LAZY);
        std::string symbol = ((Class*)cl)->nativeprefix + str0;
        if(!(next->nativehandle = dlsym(This, symbol.data()))) {
            Log::trace("JNIBinding", "Unresolved symbol %s", symbol.data());
        }
        dlclose(This);
    }
    return (jmethodID)next;
};

template<class T> T CallStaticMethodV(JNIEnv*, jclass cl, jmethodID id, va_list param) {
    auto mid = ((Method*)id);
    Log::trace("JNIENVSTUB", "CallStaticMethodV %s", mid->name.data());
    if(mid->nativehandle) {
        return ((T(*)(va_list))mid->nativehandle)(param);
    }
};

        jobject CallStaticObjectMethod(JNIEnv*, jclass, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallStaticObjectMethod");
};
        jobject CallStaticObjectMethodV(JNIEnv*, jclass, jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallStaticObjectMethodV");
};
        jobject CallStaticObjectMethodA(JNIEnv*, jclass, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallStaticObjectMethodA");
};
        jboolean CallStaticBooleanMethod(JNIEnv*, jclass, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallStaticBooleanMethod");
};
        jboolean CallStaticBooleanMethodV(JNIEnv*, jclass, jmethodID,
                            va_list) {
Log::trace("JNIENVSTUB", "CallStaticBooleanMethodV");
};
        jboolean CallStaticBooleanMethodA(JNIEnv*, jclass, jmethodID,
                            jvalue*) {
Log::trace("JNIENVSTUB", "CallStaticBooleanMethodA");
};
        jbyte CallStaticByteMethod(JNIEnv*, jclass, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallStaticByteMethod");
};
        jbyte CallStaticByteMethodV(JNIEnv*, jclass, jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallStaticByteMethodV");
};
        jbyte CallStaticByteMethodA(JNIEnv*, jclass, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallStaticByteMethodA");
};
        jchar CallStaticCharMethod(JNIEnv*, jclass, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallStaticCharMethod");
};
        jchar CallStaticCharMethodV(JNIEnv*, jclass, jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallStaticCharMethodV");
};
        jchar CallStaticCharMethodA(JNIEnv*, jclass, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallStaticCharMethodA");
};
        jshort CallStaticShortMethod(JNIEnv*, jclass, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallStaticShortMethod");
};
        jshort CallStaticShortMethodV(JNIEnv*, jclass, jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallStaticShortMethodV");
};
        jshort CallStaticShortMethodA(JNIEnv*, jclass, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallStaticShortMethodA");
};
        jint CallStaticIntMethod(JNIEnv*, jclass, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallStaticIntMethod");
};
        jint CallStaticIntMethodV(JNIEnv*, jclass, jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallStaticIntMethodV");
};
        jint CallStaticIntMethodA(JNIEnv*, jclass, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallStaticIntMethodA");
};
        jlong CallStaticLongMethod(JNIEnv*, jclass, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallStaticLongMethod");
};
        jlong CallStaticLongMethodV(JNIEnv*, jclass, jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallStaticLongMethodV");
};
        jlong CallStaticLongMethodA(JNIEnv*, jclass, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallStaticLongMethodA");
};
        jfloat CallStaticFloatMethod(JNIEnv*, jclass, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallStaticFloatMethod");
};
        jfloat CallStaticFloatMethodV(JNIEnv*, jclass, jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallStaticFloatMethodV");
};
        jfloat CallStaticFloatMethodA(JNIEnv*, jclass, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallStaticFloatMethodA");
};
        jdouble CallStaticDoubleMethod(JNIEnv*, jclass, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallStaticDoubleMethod");
};
        jdouble CallStaticDoubleMethodV(JNIEnv*, jclass, jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallStaticDoubleMethodV");
};
        jdouble CallStaticDoubleMethodA(JNIEnv*, jclass, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallStaticDoubleMethodA");
};
        void CallStaticVoidMethod(JNIEnv*, jclass, jmethodID, ...) {
Log::trace("JNIENVSTUB", "CallStaticVoidMethod");
};
        void CallStaticVoidMethodV(JNIEnv*, jclass, jmethodID, va_list) {
Log::trace("JNIENVSTUB", "CallStaticVoidMethodV");
};
        void CallStaticVoidMethodA(JNIEnv*, jclass, jmethodID, jvalue*) {
Log::trace("JNIENVSTUB", "CallStaticVoidMethodA");
};
jfieldID GetStaticFieldID(JNIEnv* env, jclass cl, const char* name, const char* type) {
std::string & classname = ((Class*)cl)->name;
    Log::trace("JNIENVSTUB", "GetStaticFieldID(%s, '%s','%s')", classname.data(), name, type);
    auto cur = (Class*)cl;
    auto sname = name;
    auto ssig = type;
    auto ccl = std::find_if(cur->fields.begin(), cur->fields.end(), [&sname, &ssig](std::shared_ptr<Field>& namesp) {
        return namesp->name == sname && namesp->type == ssig;
    });
    Field * next;
    if(ccl != cur->fields.end()) {
        next = ccl->get();
    } else {
        cur->fields.emplace_back(new Field());
        next = cur->fields.back().get();
        next->name = std::move(sname);
        next->type = std::move(ssig);
        next->_static = true;
        Declare(env, next->type.data());
        auto This = dlopen(nullptr, RTLD_LAZY);
        std::string symbol = ((Class*)cl)->nativeprefix + name;
        std::string gsymbol = "get_" + symbol;
        std::string ssymbol = "set_" + symbol;
        if(!(next->setnativehandle = dlsym(This, ssymbol.data()))) {
            Log::trace("JNIBinding", "Unresolved symbol %s", symbol.data());
        }
        if(!(next->getnativehandle = dlsym(This, gsymbol.data()))) {
            Log::trace("JNIBinding", "Unresolved symbol %s", symbol.data());
        }
        dlclose(This);
    }
    return (jfieldID)next;
};

template<class T> T GetStaticField(JNIEnv*, jclass cl, jfieldID id) {
    auto fid = ((Field*)id);
    Log::trace("JNIENVSTUB", "GetStaticField %s", fid->name.data());
    if(fid->getnativehandle) {
        return ((T(*)())fid->getnativehandle)();
    }
}

template<class T> void SetStaticField(JNIEnv*, jclass cl, jfieldID id, T value) {
    auto fid = ((Field*)id);
    Log::trace("JNIENVSTUB", "SetStaticField %s", fid->name.data());
    if(fid->getnativehandle) {
        ((void(*)(T))fid->setnativehandle)(value);
    }
}

        jstring NewString(JNIEnv*, const jchar*, jsize) {
Log::trace("JNIENVSTUB", "NewString");
};
        jsize GetStringLength(JNIEnv*, jstring) {
Log::trace("JNIENVSTUB", "GetStringLength");
};
        const jchar* GetStringChars(JNIEnv*, jstring, jboolean*) {
Log::trace("JNIENVSTUB", "GetStringChars");
};
        void ReleaseStringChars(JNIEnv*, jstring, const jchar*) {
Log::trace("JNIENVSTUB", "ReleaseStringChars");
};
        jstring NewStringUTF(JNIEnv*, const char* str) {
Log::trace("JNIENVSTUB", "NewStringUTF %s", str);
    return (jstring)(new Object<std::string> { .cl = 0,.value = new std::string(str) });
};
        jsize GetStringUTFLength(JNIEnv*, jstring) {
Log::trace("JNIENVSTUB", "GetStringUTFLength");
    return 19;
};
        /* JNI spec says this returns const jbyte*, but that's inconsistent */
        const char* GetStringUTFChars(JNIEnv*, jstring str, jboolean* copy) {
            if(copy) {
                *copy = false;
            }
Log::trace("JNIENVSTUB", "GetStringUTFChars");
    return str && ((Object<std::string>*)str)->value ? ((Object<std::string>*)str)->value->data() : "asfbdbbfsdnbsbsdbd";
};
        void ReleaseStringUTFChars(JNIEnv*, jstring, const char*) {
Log::trace("JNIENVSTUB", "ReleaseStringUTFChars");
};
        jsize GetArrayLength(JNIEnv*, jarray) {
Log::trace("JNIENVSTUB", "GetArrayLength");
};
        jobjectArray NewObjectArray(JNIEnv*, jsize, jclass, jobject) {
Log::trace("JNIENVSTUB", "NewObjectArray");
};
        jobject GetObjectArrayElement(JNIEnv*, jobjectArray, jsize) {
Log::trace("JNIENVSTUB", "GetObjectArrayElement");
};
        void SetObjectArrayElement(JNIEnv*, jobjectArray, jsize, jobject) {
Log::trace("JNIENVSTUB", "SetObjectArrayElement");
};
        jbooleanArray NewBooleanArray(JNIEnv*, jsize) {
Log::trace("JNIENVSTUB", "NewBooleanArray");
};
        jbyteArray NewByteArray(JNIEnv*, jsize) {
Log::trace("JNIENVSTUB", "NewByteArray");
};
        jcharArray NewCharArray(JNIEnv*, jsize) {
Log::trace("JNIENVSTUB", "NewCharArray");
};
        jshortArray NewShortArray(JNIEnv*, jsize) {
Log::trace("JNIENVSTUB", "NewShortArray");
};
        jintArray NewIntArray(JNIEnv*, jsize) {
Log::trace("JNIENVSTUB", "NewIntArray");
};
        jlongArray NewLongArray(JNIEnv*, jsize) {
Log::trace("JNIENVSTUB", "NewLongArray");
};
        jfloatArray NewFloatArray(JNIEnv*, jsize) {
Log::trace("JNIENVSTUB", "NewFloatArray");
};
        jdoubleArray NewDoubleArray(JNIEnv*, jsize) {
Log::trace("JNIENVSTUB", "NewDoubleArray");
};

template<class T> struct JNITypes {
    using Array = jobjectArray;
};

template<> struct JNITypes<jboolean> {
    using Array = jbooleanArray;
};

template<> struct JNITypes<jbyte> {
    using Array = jbyteArray;
};

template<> struct JNITypes<jshort> {
    using Array = jshortArray;
};

template<> struct JNITypes<jint> {
    using Array = jintArray;
};

template<> struct JNITypes<jlong> {
    using Array = jlongArray;
};

template<> struct JNITypes<jfloat> {
    using Array = jfloatArray;
};

template<> struct JNITypes<jdouble> {
    using Array = jdoubleArray;
};

template<> struct JNITypes<jchar> {
    using Array = jcharArray;
};

template<class T> T* GetArrayElements(JNIEnv*, typename JNITypes<T>::Array a, jboolean* iscopy) {
    Log::trace("JNIENVSTUB", "GetArrayElements");
    if(iscopy) {
        *iscopy = false;
    }
    return ((Array<T>*)a)->data();
};
        void ReleaseBooleanArrayElements(JNIEnv*, jbooleanArray,
                            jboolean*, jint) {
Log::trace("JNIENVSTUB", "ReleaseBooleanArrayElements");
};
        void ReleaseByteArrayElements(JNIEnv*, jbyteArray,
                            jbyte*, jint) {
Log::trace("JNIENVSTUB", "ReleaseByteArrayElements");
};
        void ReleaseCharArrayElements(JNIEnv*, jcharArray,
                            jchar*, jint) {
Log::trace("JNIENVSTUB", "ReleaseCharArrayElements");
};
        void ReleaseShortArrayElements(JNIEnv*, jshortArray,
                            jshort*, jint) {
Log::trace("JNIENVSTUB", "ReleaseShortArrayElements");
};
        void ReleaseIntArrayElements(JNIEnv*, jintArray,
                            jint*, jint) {
Log::trace("JNIENVSTUB", "ReleaseIntArrayElements");
};
        void ReleaseLongArrayElements(JNIEnv*, jlongArray,
                            jlong*, jint) {
Log::trace("JNIENVSTUB", "ReleaseLongArrayElements");
};
        void ReleaseFloatArrayElements(JNIEnv*, jfloatArray,
                            jfloat*, jint) {
Log::trace("JNIENVSTUB", "ReleaseFloatArrayElements");
};
        void ReleaseDoubleArrayElements(JNIEnv*, jdoubleArray,
                            jdouble*, jint) {
Log::trace("JNIENVSTUB", "ReleaseDoubleArrayElements");
};
        void GetBooleanArrayRegion(JNIEnv*, jbooleanArray,
                            jsize, jsize, jboolean*) {
Log::trace("JNIENVSTUB", "GetBooleanArrayRegion");
};
        void GetByteArrayRegion(JNIEnv*, jbyteArray,
                            jsize, jsize, jbyte*) {
Log::trace("JNIENVSTUB", "GetByteArrayRegion");
};
        void GetCharArrayRegion(JNIEnv*, jcharArray,
                            jsize, jsize, jchar*) {
Log::trace("JNIENVSTUB", "GetCharArrayRegion");
};
        void GetShortArrayRegion(JNIEnv*, jshortArray,
                            jsize, jsize, jshort*) {
Log::trace("JNIENVSTUB", "GetShortArrayRegion");
};
        void GetIntArrayRegion(JNIEnv*, jintArray,
                            jsize, jsize, jint*) {
Log::trace("JNIENVSTUB", "GetIntArrayRegion");
};
        void GetLongArrayRegion(JNIEnv*, jlongArray,
                            jsize, jsize, jlong*) {
Log::trace("JNIENVSTUB", "GetLongArrayRegion");
};
        void GetFloatArrayRegion(JNIEnv*, jfloatArray,
                            jsize, jsize, jfloat*) {
Log::trace("JNIENVSTUB", "GetFloatArrayRegion");
};
        void GetDoubleArrayRegion(JNIEnv*, jdoubleArray,
                            jsize, jsize, jdouble*) {
Log::trace("JNIENVSTUB", "GetDoubleArrayRegion");
};
        /* spec shows these without const; some jni.h do, some don't */
        void SetBooleanArrayRegion(JNIEnv*, jbooleanArray,
                            jsize, jsize, const jboolean*) {
Log::trace("JNIENVSTUB", "SetBooleanArrayRegion");
};
        void SetByteArrayRegion(JNIEnv*, jbyteArray,
                            jsize, jsize, const jbyte*) {
Log::trace("JNIENVSTUB", "SetByteArrayRegion");
};
        void SetCharArrayRegion(JNIEnv*, jcharArray,
                            jsize, jsize, const jchar*) {
Log::trace("JNIENVSTUB", "SetCharArrayRegion");
};
        void SetShortArrayRegion(JNIEnv*, jshortArray,
                            jsize, jsize, const jshort*) {
Log::trace("JNIENVSTUB", "SetShortArrayRegion");
};
        void SetIntArrayRegion(JNIEnv*, jintArray,
                            jsize, jsize, const jint*) {
Log::trace("JNIENVSTUB", "SetIntArrayRegion");
};
        void SetLongArrayRegion(JNIEnv*, jlongArray,
                            jsize, jsize, const jlong*) {
Log::trace("JNIENVSTUB", "SetLongArrayRegion");
};
        void SetFloatArrayRegion(JNIEnv*, jfloatArray,
                            jsize, jsize, const jfloat*) {
Log::trace("JNIENVSTUB", "SetFloatArrayRegion");
};
        void SetDoubleArrayRegion(JNIEnv*, jdoubleArray,
                            jsize, jsize, const jdouble*) {
Log::trace("JNIENVSTUB", "SetDoubleArrayRegion");
};
        jint RegisterNatives(JNIEnv* env, jclass c, const JNINativeMethod* method,
                            jint i) {
Log::trace("JNIENVSTUB", "RegisterNatives");
};
        jint UnregisterNatives(JNIEnv*, jclass) {
Log::trace("JNIENVSTUB", "UnregisterNatives");
};
        jint MonitorEnter(JNIEnv*, jobject) {
Log::trace("JNIENVSTUB", "MonitorEnter");
};
        jint MonitorExit(JNIEnv*, jobject) {
Log::trace("JNIENVSTUB", "MonitorExit");
};
        jint GetJavaVM(JNIEnv*, JavaVM**) {
Log::trace("JNIENVSTUB", "GetJavaVM");
};
        void GetStringRegion(JNIEnv*, jstring, jsize, jsize, jchar*) {
Log::trace("JNIENVSTUB", "GetStringRegion");
};
        void GetStringUTFRegion(JNIEnv*, jstring, jsize, jsize, char*) {
Log::trace("JNIENVSTUB", "GetStringUTFRegion");
};
        void* GetPrimitiveArrayCritical(JNIEnv*, jarray, jboolean*) {
Log::trace("JNIENVSTUB", "GetPrimitiveArrayCritical");
};
        void ReleasePrimitiveArrayCritical(JNIEnv*, jarray, void*, jint) {
Log::trace("JNIENVSTUB", "ReleasePrimitiveArrayCritical");
};
        const jchar* GetStringCritical(JNIEnv*, jstring, jboolean*) {
Log::trace("JNIENVSTUB", "GetStringCritical");
};
        void ReleaseStringCritical(JNIEnv*, jstring, const jchar*) {
Log::trace("JNIENVSTUB", "ReleaseStringCritical");
};
        jweak NewWeakGlobalRef(JNIEnv*, jobject) {
Log::trace("JNIENVSTUB", "NewWeakGlobalRef");
};
        void DeleteWeakGlobalRef(JNIEnv*, jweak) {
Log::trace("JNIENVSTUB", "DeleteWeakGlobalRef");
};
        jboolean ExceptionCheck(JNIEnv*) {
Log::trace("JNIENVSTUB", "ExceptionCheck");
};
        jobject NewDirectByteBuffer(JNIEnv*, void*, jlong) {
Log::trace("JNIENVSTUB", "NewDirectByteBuffer");
};
        void* GetDirectBufferAddress(JNIEnv*, jobject) {
Log::trace("JNIENVSTUB", "GetDirectBufferAddress");
};
        jlong GetDirectBufferCapacity(JNIEnv*, jobject) {
Log::trace("JNIENVSTUB", "GetDirectBufferCapacity");
};
        /* added in JNI 1.6 */
        jobjectRefType GetObjectRefType(JNIEnv*, jobject) {
Log::trace("JNIENVSTUB", "GetObjectRefType");
};

int main(int argc, char *argv[]) {
    auto windowManager = GameWindowManager::getManager();
    CrashHandler::registerCrashHandler();
    MinecraftUtils::workaroundLocaleBug();

    argparser::arg_parser p;
    argparser::arg<bool> printVersion (p, "--version", "-v", "Prints version info");
    argparser::arg<std::string> gameDir (p, "--game-dir", "-dg", "Directory with the game and assets");
    argparser::arg<std::string> dataDir (p, "--data-dir", "-dd", "Directory to use for the data");
    argparser::arg<std::string> cacheDir (p, "--cache-dir", "-dc", "Directory to use for cache");
    argparser::arg<int> windowWidth (p, "--width", "-ww", "Window width", 720);
    argparser::arg<int> windowHeight (p, "--height", "-wh", "Window height", 480);
    argparser::arg<float> pixelScale (p, "--scale", "-s", "Pixel Scale", 2.f);
    argparser::arg<bool> mallocZero (p, "--malloc-zero", "-mz", "Patch malloc to always zero initialize memory, this may help workaround MCPE bugs");
    argparser::arg<bool> disableFmod (p, "--disable-fmod", "-df", "Disables usage of the FMod audio library");
    if (!p.parse(argc, (const char**) argv))
        return 1;
    if (printVersion) {
        printVersionInfo();
        return 0;
    }
    if (!gameDir.get().empty())
        PathHelper::setGameDir(gameDir);
    if (!dataDir.get().empty())
        PathHelper::setDataDir(dataDir);
    if (!cacheDir.get().empty())
        PathHelper::setCacheDir(cacheDir);
    if (mallocZero)
        MinecraftUtils::setMallocZero();

    Log::info("Launcher", "Version: client %s / manifest %s", CLIENT_GIT_COMMIT_HASH, MANIFEST_GIT_COMMIT_HASH);
#ifdef __i386__
    {
        CpuId cpuid;
        Log::info("Launcher", "CPU: %s %s", cpuid.getManufacturer(), cpuid.getBrandString());
        Log::info("Launcher", "CPU supports SSSE3: %s",
                cpuid.queryFeatureFlag(CpuId::FeatureFlag::SSSE3) ? "YES" : "NO");
    }
#endif

    GraphicsApi graphicsApi = GLCorePatch::mustUseDesktopGL() ? GraphicsApi::OPENGL : GraphicsApi::OPENGL_ES2;

    Log::trace("Launcher", "Loading hybris libraries");
    if (!disableFmod)
        MinecraftUtils::loadFMod();
    else
        MinecraftUtils::stubFMod();
    MinecraftUtils::setupHybris();
    hybris_hook("eglGetProcAddress", (void*) +[](	char const * procname) {
        Log::warn("Launcher", "EGL stub called");
        return (void*)+[]() {
        Log::warn("Launcher", "EGL stub called");
        };
    });
    // hybris_hook("eglGetProcAddress", (void*) windowManager->getProcAddrFunc());
    // MinecraftUtils::setupGLES2Symbols((void* (*)(const char*)) windowManager->getProcAddrFunc());
#ifdef USE_ARMHF_SUPPORT
    ArmhfSupport::install();
#endif

    Log::trace("Launcher", "Loading Minecraft library");
    void* handle = MinecraftUtils::loadMinecraftLib();
    Log::info("Launcher", "Loaded Minecraft library");
    Log::debug("Launcher", "Minecraft is at offset 0x%x", MinecraftUtils::getLibraryBase(handle));

    ModLoader modLoader;
    modLoader.loadModsFromDirectory(PathHelper::getPrimaryDataDirectory() + "mods/");
    MinecraftUtils::initSymbolBindings(handle);
    // Log::info("Launcher", "Game version: %s", Common::getGameVersionStringNet().c_str());
    SharedConstants::RevisionVersion = new int[1] { 1 };
    SharedConstants::MajorVersion = new int[1] { 0 };
    SharedConstants::MinorVersion = new int[1] { 14 };
    SharedConstants::PatchVersion = new int[1] { 0 };
//     Log::info("Launcher", "Applying patches");
//     LauncherStore::install(handle);
//     TTSPatch::install(handle);
//     XboxLivePatches::install(handle);
// #ifdef __i386__
//     XboxShutdownPatch::install(handle);
//     TexelAAPatch::install(handle);
// #endif
//     LinuxHttpRequestHelper::install(handle);
//     HbuiPatch::install(handle);
//     SplitscreenPatch::install(handle);
    ShaderErrorPatch::install(handle);
//     if (graphicsApi == GraphicsApi::OPENGL)
//         GLCorePatch::install(handle);
//     LegacyPatches::install(handle);

    Log::info("Launcher", "Creating window");
    WindowCallbacks::loadGamepadMappings();
    auto window = windowManager->createWindow("Minecraft", windowWidth, windowHeight, graphicsApi);
    window->setIcon(PathHelper::getIconPath());
    window->show();

//     SplitscreenPatch::onGLContextCreated();
        GLCorePatch::onGLContextCreated();
//     ShaderErrorPatch::onGLContextCreated();

//     Log::trace("Launcher", "Initializing AppPlatform (vtable)");
//     ClientAppPlatform::initVtable(handle);
    Log::trace("Launcher", "Initializing AppPlatform (create instance)");
    auto ANativeActivity_onCreate = (ANativeActivity_createFunc*)hybris_dlsym(handle, "ANativeActivity_onCreate");
    ANativeActivity activity;
    memset(&activity, 0, sizeof(ANativeActivity));
    activity.internalDataPath = "./idata";
    activity.externalDataPath = "./edata";
    activity.obbPath = "./obb";
    activity.sdkVersion = 200;
    static JNIEnv env;
    JNIInvokeInterface invokeInterface {
    NULL,
    NULL,
    NULL,
    [](JavaVM*) -> jint {
Log::trace("JNIENVSTUB", "DestroyJavaVM");
},
    [](JavaVM*, JNIEnv**, void*) -> jint {
Log::trace("JNIENVSTUB", "AttachCurrentThread");
},
    [](JavaVM*) -> jint {
Log::trace("JNIENVSTUB", "DetachCurrentThread");
},
    [](JavaVM*, void** penv, jint) -> jint {
Log::trace("JNIENVSTUB", "GetEnv");
        *penv = &env;
        return JNI_OK;
},
    [](JavaVM*, JNIEnv**, void*) -> jint {
Log::trace("JNIENVSTUB", "AttachCurrentThreadAsDaemon");
},
};
    static JavaVM vm;
    vm.functions = &invokeInterface;
    activity.vm = &vm;
    activity.clazz = (jclass)43;
    ANativeActivityCallbacks callbacks;
    memset(&callbacks, 0, sizeof(ANativeActivityCallbacks));
    activity.callbacks = &callbacks;
    JNINativeInterface interface = {
        NULL,
        NULL,
        NULL,
        NULL,
        GetVersion,
        DefineClass,
        FindClass,
        FromReflectedMethod,
        FromReflectedField,
        /* spec doesn't show jboolean parameter */
        ToReflectedMethod,
        GetSuperclass,
        IsAssignableFrom,
        /* spec doesn't show jboolean parameter */
        ToReflectedField,
        Throw,
        ThrowNew,
        ExceptionOccurred,
        ExceptionDescribe,
        ExceptionClear,
        FatalError,
        PushLocalFrame,
        PopLocalFrame,
        NewGlobalRef,
        DeleteGlobalRef,
        DeleteLocalRef,
        IsSameObject,
        NewLocalRef,
        EnsureLocalCapacity,
        AllocObject,
        NewObject,
        NewObjectV,
        NewObjectA,
        GetObjectClass,
        IsInstanceOf,
        GetMethodID,
        CallObjectMethod,
        CallObjectMethodV,
        CallObjectMethodA,
        CallBooleanMethod,
        CallBooleanMethodV,
        CallBooleanMethodA,
        CallByteMethod,
        CallByteMethodV,
        CallByteMethodA,
        CallCharMethod,
        CallCharMethodV,
        CallCharMethodA,
        CallShortMethod,
        CallShortMethodV,
        CallShortMethodA,
        CallIntMethod,
        CallIntMethodV,
        CallIntMethodA,
        CallLongMethod,
        CallLongMethodV,
        CallLongMethodA,
        CallFloatMethod,
        CallFloatMethodV,
        CallFloatMethodA,
        CallDoubleMethod,
        CallDoubleMethodV,
        CallDoubleMethodA,
        CallVoidMethod,
        CallVoidMethodV,
        CallVoidMethodA,
        CallNonvirtualObjectMethod,
        CallNonvirtualObjectMethodV,
        CallNonvirtualObjectMethodA,
        CallNonvirtualBooleanMethod,
        CallNonvirtualBooleanMethodV,
        CallNonvirtualBooleanMethodA,
        CallNonvirtualByteMethod,
        CallNonvirtualByteMethodV,
        CallNonvirtualByteMethodA,
        CallNonvirtualCharMethod,
        CallNonvirtualCharMethodV,
        CallNonvirtualCharMethodA,
        CallNonvirtualShortMethod,
        CallNonvirtualShortMethodV,
        CallNonvirtualShortMethodA,
        CallNonvirtualIntMethod,
        CallNonvirtualIntMethodV,
        CallNonvirtualIntMethodA,
        CallNonvirtualLongMethod,
        CallNonvirtualLongMethodV,
        CallNonvirtualLongMethodA,
        CallNonvirtualFloatMethod,
        CallNonvirtualFloatMethodV,
        CallNonvirtualFloatMethodA,
        CallNonvirtualDoubleMethod,
        CallNonvirtualDoubleMethodV,
        CallNonvirtualDoubleMethodA,
        CallNonvirtualVoidMethod,
        CallNonvirtualVoidMethodV,
        CallNonvirtualVoidMethodA,
        GetFieldID,
        GetField<jobject>,
        GetField<jboolean>,
        GetField<jbyte>,
        GetField<jchar>,
        GetField<jshort>,
        GetField<jint>,
        GetField<jlong>,
        GetField<jfloat>,
        GetField<jdouble>,
        SetField<jobject>,
        SetField<jboolean>,
        SetField<jbyte>,
        SetField<jchar>,
        SetField<jshort>,
        SetField<jint>,
        SetField<jlong>,
        SetField<jfloat>,
        SetField<jdouble>,
        GetStaticMethodID,
        CallStaticObjectMethod,
        CallStaticMethodV<jobject>,
        CallStaticObjectMethodA,
        CallStaticBooleanMethod,
        CallStaticMethodV<jboolean>,
        CallStaticBooleanMethodA,
        CallStaticByteMethod,
        CallStaticMethodV<jbyte>,
        CallStaticByteMethodA,
        CallStaticCharMethod,
        CallStaticMethodV<jchar>,
        CallStaticCharMethodA,
        CallStaticShortMethod,
        CallStaticMethodV<jshort>,
        CallStaticShortMethodA,
        CallStaticIntMethod,
        CallStaticMethodV<jint>,
        CallStaticIntMethodA,
        CallStaticLongMethod,
        CallStaticMethodV<jlong>,
        CallStaticLongMethodA,
        CallStaticFloatMethod,
        CallStaticMethodV<jfloat>,
        CallStaticFloatMethodA,
        CallStaticDoubleMethod,
        CallStaticMethodV<jdouble>,
        CallStaticDoubleMethodA,
        CallStaticVoidMethod,
        CallStaticMethodV<void>,
        CallStaticVoidMethodA,
        GetStaticFieldID,
        GetStaticField<jobject>,
        GetStaticField<jboolean>,
        GetStaticField<jbyte>,
        GetStaticField<jchar>,
        GetStaticField<jshort>,
        GetStaticField<jint>,
        GetStaticField<jlong>,
        GetStaticField<jfloat>,
        GetStaticField<jdouble>,
        SetStaticField<jobject>,
        SetStaticField<jboolean>,
        SetStaticField<jbyte>,
        SetStaticField<jchar>,
        SetStaticField<jshort>,
        SetStaticField<jint>,
        SetStaticField<jlong>,
        SetStaticField<jfloat>,
        SetStaticField<jdouble>,
        NewString,
        GetStringLength,
        GetStringChars,
        ReleaseStringChars,
        NewStringUTF,
        GetStringUTFLength,
        /* JNI spec says this returns const jbyte*, but that's inconsistent */
        GetStringUTFChars,
        ReleaseStringUTFChars,
        GetArrayLength,
        NewObjectArray,
        GetObjectArrayElement,
        SetObjectArrayElement,
        NewBooleanArray,
        NewByteArray,
        NewCharArray,
        NewShortArray,
        NewIntArray,
        NewLongArray,
        NewFloatArray,
        NewDoubleArray,
        GetArrayElements<jboolean>,
        GetArrayElements<jbyte>,
        GetArrayElements<jchar>,
        GetArrayElements<jshort>,
        GetArrayElements<jint>,
        GetArrayElements<jlong>,
        GetArrayElements<jfloat>,
        GetArrayElements<jdouble>,
        ReleaseBooleanArrayElements,
        ReleaseByteArrayElements,
        ReleaseCharArrayElements,
        ReleaseShortArrayElements,
        ReleaseIntArrayElements,
        ReleaseLongArrayElements,
        ReleaseFloatArrayElements,
        ReleaseDoubleArrayElements,
        GetBooleanArrayRegion,
        GetByteArrayRegion,
        GetCharArrayRegion,
        GetShortArrayRegion,
        GetIntArrayRegion,
        GetLongArrayRegion,
        GetFloatArrayRegion,
        GetDoubleArrayRegion,
        /* spec shows these without const; some jni.h do, some don't */
        SetBooleanArrayRegion,
        SetByteArrayRegion,
        SetCharArrayRegion,
        SetShortArrayRegion,
        SetIntArrayRegion,
        SetLongArrayRegion,
        SetFloatArrayRegion,
        SetDoubleArrayRegion,
        RegisterNatives,
        UnregisterNatives,
        MonitorEnter,
        MonitorExit,
        GetJavaVM,
        GetStringRegion,
        GetStringUTFRegion,
        GetPrimitiveArrayCritical,
        ReleasePrimitiveArrayCritical,
        GetStringCritical,
        ReleaseStringCritical,
        NewWeakGlobalRef,
        DeleteWeakGlobalRef,
        ExceptionCheck,
        NewDirectByteBuffer,
        GetDirectBufferAddress,
        GetDirectBufferCapacity,
        /* added in JNI 1.6 */
        GetObjectRefType,
    };
    env.functions = &interface;
    activity.env = &env;
    // env.
//     PatchUtils::patchCallInstruction(hybris_dlsym(handle, "_ZN11JVMAttacherC2EP7_JavaVM"), (void*) + [](void * jwmattacher, void * jvm) {
//         Log::debug("JVMAttacher", "<<Create>>");
//     }, true);
//     PatchUtils::patchCallInstruction(hybris_dlsym(handle, "_ZN11JVMAttacherD2Ev"), (void*) + [](void * jwmattacher, void * jvm) {
//         Log::debug("JVMAttacher", "<<Destruct>>");
//     }, true);
//     PatchUtils::patchCallInstruction(hybris_dlsym(handle, "_ZN11JVMAttacher6getEnvEv"), (void*) + [](void * jwmattacher) {
//         Log::debug("JVMAttacher", "getEnv");
//         return env;
//     }, true);
//     PatchUtils::patchCallInstruction(hybris_dlsym(handle, "_ZN11JVMAttacher10isAttachedEv"), (void*) + [](void * jwmattacher) -> bool {
//         Log::debug("JVMAttacher", "isAttached");
//         return true;
//     }, true);
//     PatchUtils::patchCallInstruction(hybris_dlsym(handle, "_ZN11JVMAttacher11forceDetachEv"), (void*) + [](void * jwmattacher) {
//         Log::debug("JVMAttacher", "forceDetach");
//     }, true);

//     PatchUtils::patchCallInstruction(hybris_dlsym(handle, "_ZN8JavaUtil5getVMEv"), (void*) + [](void* j) {
//         Log::debug("JVMAttacher", "_ZN8JavaUtil5getVMEv");
//         return &vm;
//     }, true);
//     PatchUtils::patchCallInstruction(hybris_dlsym(handle, "_ZN8JavaUtil5setVMEP7_JavaVM"), (void*) + [](void* j, void* vm) {
//         Log::debug("JVMAttacher", "_ZN8JavaUtil5setVMEP7_JavaVM");
//     }, true);
    // PatchUtils::patchCallInstruction((void*)((char*)hybris_dlsym(handle, "android_main") + 432), (void*) + [](void * jwmattacher) {
    //     Log::debug("JVMAttacher", "forceDetach");
    // }, true);
    ((Namespace*&)env.functions->reserved0) = new Namespace();
    // Resolable by correctly implement Alooper
    memset((char*)hybris_dlsym(handle, "android_main") + 394, 0x90, 18);
//     memset((void*)0xee29110e, 0x90, 1);
    jint ver = ((jint (*)(JavaVM* vm, void* reserved))hybris_dlsym(handle, "JNI_OnLoad"))(&vm, 0);
    activity.clazz = new Object<int> { .cl = env.FindClass("com/mojang/minecraftpe/MainActivity") };
    ANativeActivity_onCreate(&activity, 0, 0);
    // size_t savestate = 0;
    // void * data = activity.callbacks->onSaveInstanceState(&activity, &savestate);
    // free(data);
//     activity.callbacks->onInputQueueCreated(&activity, (AInputQueue*)2);
//     activity.callbacks->onNativeWindowCreated(&activity, (ANativeWindow*)1);
//     activity.callbacks->onWindowFocusChanged(&activity, true);
//     activity.callbacks->onResume(&activity);
//     activity.callbacks->onStart(&activity);
    // appPlatform = std::unique_ptr<ClientAppPlatform>(new ClientAppPlatform());
    // appPlatform->setWindow(window);
    // Log::trace("Launcher", "Initializing AppPlatform (initialize call)");
    // if (MinecraftVersion::isAtLeast(0, 17, 2))
    //     appPlatform->initialize();
    // if (MinecraftVersion::isAtLeast(0, 16) && !MinecraftVersion::isAtLeast(1, 13, 0, 9))
    //     mce::Platform::OGL::InitBindings();

    // // Log::info("Launcher", "OpenGL: version: %s, renderer: %s, vendor: %s",
    // //           gl::getOpenGLVersion().c_str(), gl::getOpenGLRenderer().c_str(), gl::getOpenGLVendor().c_str());



    // Log::trace("Launcher", "Initializing MinecraftGame (create instance)");
    // std::unique_ptr<MinecraftGameWrapper> game (MinecraftGameWrapper::create(argc, argv));
    // Log::trace("Launcher", "Initializing MinecraftGame (init call)");
    // AppContext ctx;
    // ctx.platform = appPlatform.get();
    // ctx.doRender = true;
    // game->init(ctx);
    // Log::info("Launcher", "Game initialized");

    // modLoader.onGameInitialized((MinecraftGame*) game->getWrapped());

    // WindowCallbacks windowCallbacks (*game, *appPlatform, *window);
    // windowCallbacks.setPixelScale(pixelScale);
    // windowCallbacks.registerCallbacks();
    // if (MinecraftVersion::isAtLeast(1, 8)) {
    //     game->getWrapped()->doPrimaryClientReadyWork([&windowCallbacks]() {
    //         windowCallbacks.handleInitialWindowSize();
    //     });
    // } else {
    //     windowCallbacks.handleInitialWindowSize();
    // }
    // window->runLoop();

    // game->leaveGame();
    // game.reset();

    // MinecraftUtils::workaroundShutdownCrash(handle);
    // XboxLivePatches::workaroundShutdownFreeze(handle);
    // XboxShutdownPatch::notifyShutdown();

    // XboxLiveHelper::getInstance().shutdown();
    // appPlatform->teardown();
    // appPlatform->setWindow(nullptr);
    // std::cout << ((Namespace*&)env.functions->reserved0)->GeneratePreDeclaration();
    // std::cout << ((Namespace*&)env.functions->reserved0)->GenerateHeader("");
    // std::cout << ((Namespace*&)env.functions->reserved0)->GenerateStubs("");
    // std::cout << ((Namespace*&)env.functions->reserved0)->GenerateJNIBinding("");
    // std::this_thread::sleep_for(std::chrono::seconds(2));
//     activity.callbacks->onStart(&activity);
//     activity.callbacks->onResume(&activity);
//     activity.callbacks->onWindowFocusChanged(&activity, true);
    // PatchUtils::patchCallInstruction(hybris_dlsym(handle, "_ZN8InitOnce8initOnceEv"), (void*)+[]() {
    //     return;
    // }, true);
    activity.callbacks->onNativeWindowCreated(&activity, (ANativeWindow*)1);
//     activity.callbacks->onInputQueueCreated(&activity, (AInputQueue*)2);
    std::this_thread::sleep_for(std::chrono::hours(10));
    return 0;
}

void printVersionInfo() {
    printf("mcpelauncher-client %s / manifest %s\n", CLIENT_GIT_COMMIT_HASH, MANIFEST_GIT_COMMIT_HASH);
#ifdef __i386__
    CpuId cpuid;
    printf("CPU: %s %s\n", cpuid.getManufacturer(), cpuid.getBrandString());
    printf("SSSE3 support: %s\n", cpuid.queryFeatureFlag(CpuId::FeatureFlag::SSSE3) ? "YES" : "NO");
#endif
    auto windowManager = GameWindowManager::getManager();
    GraphicsApi graphicsApi = GLCorePatch::mustUseDesktopGL() ? GraphicsApi::OPENGL : GraphicsApi::OPENGL_ES2;
    auto window = windowManager->createWindow("mcpelauncher", 32, 32, graphicsApi);
    auto glGetString = (const char* (*)(int)) windowManager->getProcAddrFunc()("glGetString");
    printf("GL Vendor: %s\n", glGetString(0x1F00 /* GL_VENDOR */));
    printf("GL Renderer: %s\n", glGetString(0x1F01 /* GL_RENDERER */));
    printf("GL Version: %s\n", glGetString(0x1F02 /* GL_VERSION */));
    printf("MSA daemon path: %s\n", XboxLiveHelper::findMsa().c_str());
}