#include "my.h"
void init_daemon(void);

int main(int argc, char const *argv[])
{
    FILE* fp;
    time_t t;
    printf("aaa\n");
    init_daemon();
    printf("ccc\n");
    while (1)
    {
        sleep(10);
        if ((fp = fopen("6-8.log","a")) >= 0)
        {
            t = time(0);
            fprintf(fp,"守护进程还在运行，时间是:%s",asctime(localtime(&t)));
            fclose(fp);
        }
        
    }
    return 0;
}
