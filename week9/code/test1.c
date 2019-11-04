#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int x = 100;
int main(int argc,char* argv[]){
    int y = 0;
    static int w = 33;
    printf("test1:pid=%d,ppid=%d\n",getpid(),getppid());
    for (int i = 0; i < argc; i++)
    {
        printf("%d : %s \n",i, argv[i]);
    }

    printf("test1:address x= %ld,y = %ld,w=%ld\n",&x,&y,&w);
    sleep(50);
    return 0;
}