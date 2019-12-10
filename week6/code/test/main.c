#include "lib.h"
#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>

int main(){
    int a[5] = {10,95,-10,32,5};
    void *handle;
    void (*f1)();
    int (*f2)(),(*f3)();
    char *error;

    handle = dlopen("/home/rlk/linuxprogram/week6/code/dynamiclib/libtest.so",RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr,"%s\n",dlerror());
        exit(1);
    }
    f1 = dlsym(handle,"show");
    if ((error==dlerror())!=NULL)
    {
        fprintf(stderr,"%s\n",dlerror());
        exit(1);
    }
    f2 = dlsym(handle,"max");
    if ((error==dlerror())!=NULL)
    {
        fprintf(stderr,"%s\n",dlerror());
        exit(1);
    }
    f3 = dlsym(handle,"sum");
    if ((error==dlerror())!=NULL)
    {
        fprintf(stderr,"%s\n",dlerror());
        exit(1);
    }
    f1(a,5);
    printf("max:%d\n",f2(a,5));
    printf("sum:%d\n",f3(a,5));
    if (dlclose(handle) < 0)
    {
        fprintf(stderr,"%s\n",dlerror());
        exit(1);
    }
    return 0;
}
