#include "my.h"
int g = 10;
int main(int argc, char const *argv[])
{
    int s = 20;
    static int k = 30;
    pid_t pid;
    pid = vfork();
    if (pid < 0)
    {
        perror("failed vfork\n");
        exit(-1);
    }
    else if (pid == 0)
    {
        sleep(2);
        printf("child pid = %d:&g = %16p,&k = %16p,&s = %16p\n",getpid(),g,k,s);
        g = 100;
        s = 200;
        k = 300;
        printf("child pid = %d:&g=%d,&k=%d,&s=%d\n",getpid(),g,k,s);
        sleep(2);
        return 0;
    }
    else{
        printf("\nparent pid = %d:&g = %16p,&k = %16p,&s = %16p",getpid(),g,k,s);
        printf("parent pid = %d:&g=%d,&k=%d,&s=%d\n",getpid(),g,k,s);
        return 0;
    }
    return 0;
}
