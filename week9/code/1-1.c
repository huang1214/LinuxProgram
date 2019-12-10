#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

static void fun1(void)
{
    printf("invoked callbackfun\n");
}
int main(int argc, char const *argv[])
{
    atexit(fun1);
    FILE *fp;
    char buf[] = "buffer data!";
    if ((fp = fopen("test.dat","w+")) == NULL)
    {
        perror("create file failed\n");
        exit(-1);
    }
    if (fputs(buf,fp) == EOF)
    {
        perror("fputs file failed\n");
        exit(-1);
    }
    printf("hello ");
    exit(0);
}
