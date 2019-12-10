#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[],char *env[])
{
    int i = 0;
    extern char **environ;
    printf("main参数中的env-> 输出环境变量内容:");
    for ( i = 0; env[i]; i++)
    {
        printf("%s\n",env[i]);
    }
    printf("外部参数enbviron-> 输出环境变量内容:");
    for ( i = 0; environ[i]; i++)
    {
        printf("%s\n",environ[i]);
    }
    printf("调用getenv\n");
    printf("%s\n",getenv("PATH"));
    return 0;
}
