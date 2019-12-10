#include "my.h"
#define NUM 4
// 传入值给fun计算值

typedef struct INFO
{
    int x;
    int y;
}info;


void fun(void *arg)
{
    info *pt;
    pthread_t my_tid;
    pt = (info *) arg;
    my_tid = pthread_self();
    printf("tid:%d sum = %d,first num:%d,second num:%d\n",my_tid,((*pt).x)+((*pt).y),(*pt).x,(*pt).y);
    //printf("worker thread %d:tid = %p\n",(int)pt,pthread_self());
}

int main(int argc, char const *argv[])
{
    pthread_t tid[NUM];
    int ret;
    int i;
    info arg[NUM];
    
    for ( i = 0; i < NUM; i++)
    {   
        arg[i].x = (i+1)*100;
        arg[i].y = (i+2)*100;
        pthread_create(&tid[i],NULL,(void *(*))fun,(void *)&arg[i]);
    }
    printf("all finished \n");
    return 0;
}
