#include <stdio.h>
#include <stdlib.h>


#define MODULE_INIT __attribute__((constructor))
#define MODULE_FINI __attribute__((destructor))


//申明结构体类型
typedef struct __test {
    int i;
    void (*echo_fun)(struct __test *p);
}Test;

//申明注册函数原型
void __register(Test *p);

static void __printf(Test *p) {
    printf("i = %dn\n", p->i);
}

//动态库申请一个全局变量空间
//这种 ".成员"的赋值方式为c99标准
static Test config = {
    .i = 0,
    .echo_fun = __printf,
};

int add(int a, int b)
{
        return a + b;
}

//加载动态库的自动初始化函数
// 默认是 _init
// 可用 __attribute__((constructor)) 指定
/*void _init(void) {*/
MODULE_INIT void my_init(void)
{
    printf("init\n");
    //调用主程序的注册函数
    __register(&config);
}

MODULE_FINI void finish(void)
{
        printf("finish\n");
}
