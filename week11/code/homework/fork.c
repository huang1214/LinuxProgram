#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	char a[5]="abcd";
	char *b=(char *)malloc(sizeof(char)*5);
	char ch;
	FILE *f;
	if((f=fopen("1.txt","w+"))==NULL)
	{
		perror("Open failed\n");
		exit(1);
	}
	if((pid=fork())<0)
	{
		perror("fork error!\n");
		exit(2);	
	}
	else if(pid==0)
	{
		printf("child pid=%d ppid=%d :f=%p\n",getpid(),getppid(),f);
		fputs(a,f);
		rewind(f);//这个也是可以的
		//fseek(f,0L,SEEK_SET);
		while(fgets(b,5,f)!=NULL)
		fputs(b,stdout);
		putchar('\n');
		//fclose(f);
		free(b);
		exit(0);
	}
	else{
		printf("parent pid=%d: f=%p\n",getpid(),f);
		fputs(a,f);
		//free(b);
		//rewind(f);//这个也是可以的
		fseek(f,0L,SEEK_SET);
		while(fgets(b,5,f)!=NULL)
		fputs(b,stdout);
		putchar('\n');
		//fclose(f);
		exit(0);
	}
	fclose(f);
	return 0;
}
