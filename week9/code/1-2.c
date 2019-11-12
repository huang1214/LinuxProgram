#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// 验证vfork造成的死锁
int main(int argc, char const *argv[])
{
    int a = 1;
    pid_t pid;
    pid = vfork();
    if (pid < 0)
    {
        perror("vfork failed\n");
        exit(-1);
    }
    // 父进程运行段
    else if (pid == 0)
    {
        a++;
        printf("子进程：%d ,a = %d\n",getpid(),a);
    }
    //子进程运行段
    else{
        a++;
        printf("父进程：%d ,a = %d\n",getpid(),a);
    }
    return 0;
}
