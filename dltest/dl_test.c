

#include <stdio.h>
#include <dlfcn.h>


int main()
{

        void *dl = NULL;
        dl = dlopen("/usr/lib64/ganesha/libfsalceph.so", RTLD_NOW | RTLD_LOCAL | RTLD_DEEPBIND);

        void (*module_init)(void);
        char *sym_error;
        module_init = dlsym(dl, "fsal_init");
        sym_error = (char *)dlerror();
        printf("error %s\n", sym_error);

        printf("init %p\n", module_init);





        /*dlclose(dl);*/
        return 0;
}
