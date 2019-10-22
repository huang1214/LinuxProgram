#include <stdio.h>

int main(){
    printf("hello");
    // 方法1：使用fflush强制清理缓冲区
    // fflush(stdout);

    // 方法2 使用fclose()关闭内容
    // fclose(stdout);

    
    while(1);
    return 0;
}