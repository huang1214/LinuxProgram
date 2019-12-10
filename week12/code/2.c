// 验证管道的写阻塞问题
#include "my.h"
int main(int argc, char const *argv[])
{
    pid_t p;
    char w_buf[100],r_buf[100];
    int fd[2];
    int wn = 0;
    int rn = 0;
    memset(w_buf,0,100);
    memset(r_buf,0,100);
    pipe(fd);
    p = fork();
    if (p<0)
    {
        perror("fork失败\n");
        return -1;
    }
    else if ( p == 0)
    {
        char b = 'a';
        close(fd[0]);
        printf("child pid = %d\n",getpid());
        //sprintf(w_buf,"child is running,pid=%d",getpid());
        // 使用for循环频繁写入65537即阻塞
        for (int i = 0; i < 65536; i++)
        {
            printf("child wirte %d times\n",i);
            write(fd[1],&b,1);
        }
        
        // if ((wn = write(fd[1],w_buf,sizeof(w_buf)))<0)
        // {
        //     printf("写入失败");
        //     exit(-1);
        // }
        // printf("child write to pipe %d byte\n",wn);
        close(fd[1]);
        exit(0);
    }
    else
    {
        close(fd[1]);
        wait(NULL);
        for (int i = 0; i < 65536; i++)
        {
            read(fd[0],r_buf,1);
            printf("%d:parent read from pipe:%s\n",i,r_buf);
        }
        
        // if ((rn = read(fd[0],r_buf,sizeof(r_buf)))<0)
        // {
        //     printf("read failed \n");
        //     exit(-1);
        // }
        // printf("parent read from pipe total %d ,content = %s",rn,r_buf);
        return 0;
    }
    
    return 0;
}
