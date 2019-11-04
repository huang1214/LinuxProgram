#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    int ret;
    char* execv_argv[] = {"./test1", "123" ,"456" ,"abc",NULL};
    printf("caller:pid=%d,ppid=%d\n",getpid(),getppid());
    if (execlp("test1","test1", "123" ,"456" ,"abc",NULL) < 0)
    {
       printf("调用失败\n");
    }
     
    printf("after calling\n");
    sleep(100);
    return 0;
}
