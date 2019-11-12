#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

static void __attribute__((constructor)) before_main()
{
    printf("在main之前运行");
}
static void callback1(void)
{
    printf("callback1 在运行");
}

static void callback2(void)
{
    printf("callback2 在运行");
}
static void callback3(void)
{
    printf("callback3 在运行");
}
int main(int argc, char const *argv[])
{
    int i;
    atexit(callback1);
    atexit(callback2);
    atexit(callback3);
    
    return 0;
}
