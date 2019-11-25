// 验证管道的写阻塞问题
#include "my.h"
int main(int argc, char const *argv[])
{
    pid_t p;
    int w_buf[65537],r_buf[65537];
    int one2twofd[2];
    int two2thrfd[2];
    int wn = 0;
    int rn = 0;
    memset(w_buf,0,100);
    memset(r_buf,0,100);
    // pipe在fork之前建立，避免重复建立
    pipe(one2twofd);
    pipe(two2thrfd);
    pid_t pid = fork();
	if(pid == 0){
		printf("I'm a first son.PID is %d.\n",getpid());
        // 产生0-65536并写入1-2管道
        close(one2twofd[0]);
        for (int i = 0; i < 65536; i++)
        {
            
            write(one2twofd[1],&i,sizeof(int));
        }
        
        close(one2twofd[1]);
		exit(1);    // 使当前进程结束，不执行下面的fork，避免重复fork
	}
	pid_t pid2 = fork();
	if(pid2 == 0){
        // 读出1-2管道
        // 再次写入2-3管道
        close(one2twofd[1]);
        long c = 0;
        for (int i = 0; i < 65536; i++)
        {
            read(one2twofd[0],&r_buf[i],sizeof(int));
            printf("child 2 接受到：%d\n",r_buf[i]); 
        }
        close(one2twofd[0]);
        close(two2thrfd[0]);
        write(two2thrfd[1],&r_buf,sizeof(r_buf));
        close(two2thrfd[1]);
		printf("I'm a second son.PID is %d.\n",getpid());
		exit(1);
	
	}
	pid_t pid3 = fork();
	if(pid3 ==0){
        // 读出2-3管道的数据，并求和
        close(two2thrfd[1]);
        int c = 0;
        long sum = 0;
        read(two2thrfd[0],&w_buf,sizeof(w_buf));
        for (int i = 0; i < 65536; i++)
        {
            sum += w_buf[i];
        }
        close(two2thrfd[0]);
        printf("最终结果是%ld\n",sum);
		printf("I'm a third son.PID is %d.\n",getpid());
		exit(1);
	
	}
	else if(pid != -1){
		printf("Parent forked child process--%d.\n",pid);
		printf("Parent is waiting for child to exit.\n");
		waitpid(pid,NULL,0);
		waitpid(pid2,NULL,0);
		waitpid(pid3,NULL,0);
		printf("Child Process had exited.\n");
		printf("Parent had exited.\n");
	}
	else	printf("Everything was done without error.\n");
    
    return 0;
}
