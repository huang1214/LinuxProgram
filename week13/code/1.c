// 测试信号

#include "my.h"
void sigroutine(int signo)
{
	switch(signo)
	{
		case 1:
			printf("recive SIGHUP\n");
			break;
		case 2:
			printf("recive SIGINT\n");
			break;
		case 3:
			printf("recive SIGQUIT\n");
			break;
	}
}
// 最终的效果是输入命令：kill -x pid 程序不会结束，而是显示上面定义的语句，除非输入的x不在case中，才会结束
int main(int argc, char const *argv[])
{
	signal(1,sigroutine);
	signal(2,sigroutine);
	signal(3,sigroutine);
	printf("test process.\n pid = %d\n",getpid());
	while(1);
	return 0;
}