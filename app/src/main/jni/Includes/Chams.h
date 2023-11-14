#ifndef HENZRY_CHAMS
#define HENZRY_CHAMS
#include <GLES2/gl2.h>
#include <dlfcn.h>
static void* handle;

bool mlovinit(){
    handle = NULL;
    handle = dlopen("libGLESv2.so", RTLD_LAZY);
    if(!handle){
        return false;
    }
    return true;
}
#endif

