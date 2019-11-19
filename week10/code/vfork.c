#include "my.h"

int main(int argc, char const *argv[])
{
    __pid_t pid;
    // 既然是讨论是否共享，那么就应该是在分子进程之前就分配文件指针
    FILE* fd = fopen("vfork.txt","a+");
    
    char* child_buf = "child";
    char* parent_buf = "parent";
    pid = vfork();
    if (pid < 0)
    {
        perror("创建子进程失败\n");
    }
    else if (pid == 0)
    {
        // 子进程内容
        if (fwrite(child_buf,sizeof(child_buf),1,fd)!=1)
        {
            perror("写入失败\n");
        }
        exit(0);
    }
    else{
        if (fwrite(parent_buf,sizeof(parent_buf),1,fd)!=1)
        {
            perror("写入失败\n");
        }
    }
    fclose(fd);
    exit(0);
}
