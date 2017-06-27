#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>

//申明结构体
typedef struct __test {
    int i;
    void (* echo_fun)(struct __test *p);
}Test;

//供动态库使用的注册函数
void __register(Test *p) {
    p->i = 1;
    p->echo_fun(p);
}

int main(void) {

    void *handle = NULL;
    char *error;
    char *myso = "./mylib.so";

    /*
     *RTLD_LAZY 暂缓决定，等有需要时再解出符号 
     *RTLD_NOW 立即决定，返回前解除所有未决定的符号。
     */
    /*if((handle = dlopen(myso, RTLD_LAZY)) == NULL) {*/
    if((handle = dlopen(myso, RTLD_NOW | RTLD_LOCAL | RTLD_DEEPBIND)) == NULL) {
        printf("dlopen - %sn", dlerror());
        exit(-1);
    }

    int (*add_fun)(int, int) = NULL;
    *(void **)(&add_fun) = dlsym(handle, "add");
    /*add_fun = (int(*)(int, int))dlsym(handle, "add");*/
    if ((error = dlerror()) != NULL) {
            fprintf(stderr, "err: %s\n", error);
            exit(-1);
    } 
    
    printf("add 1 + 3 = %d\n", (*add_fun)(1, 3));

    return 0;
}
