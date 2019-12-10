#include "my.h"
#define NUM 4
// 传入值给fun计算值
// 尝试函数返回的是void *
typedef struct INFO
{
    int x;
    int y;
}info;
typedef struct RVAL{
    int sum;
    double time;
    pthread_t tid;
}rval;

void * fun(void *arg)
{
    time_t time_begin,time_end;
    info *pt;
    pthread_t my_tid;
    time_begin = clock();
    rval *result = (rval *)malloc(sizeof(rval));
    pt = (info *) arg;
    my_tid = pthread_self();
    result->sum = ((*pt).x)+((*pt).y);
    result->tid = my_tid;
    //printf("tid:%d sum = %d,first num:%d,second num:%d\n",my_tid,((*pt).x)+((*pt).y),(*pt).x,(*pt).y);
    //printf("worker thread %d:tid = %p\n",(int)pt,pthread_self());
    printf("sum:%d,tid:%ld\n",result->sum,result->tid);
    time_end = clock();
    result->time = time_end - time_begin;
    pthread_exit(result);
}


int main(int argc, char const *argv[])
{
    pthread_t tid[NUM];
    int ret;
    int i;
    rval* result;
    info arg[NUM];
    for ( i = 0; i < NUM; i++)
    {   
        result[i].sum = 0;
        result[i].tid = 0;
        arg[i].x = (i+1)*100;
        arg[i].y = (i+2)*100;
        pthread_create(&tid[i],NULL,fun,(void *)&arg[i]);
        
    }
    for ( i = 0; i < NUM; i++)
    {
        pthread_join(tid[i],(void **)&result);
        printf("sum:%d,tid:%ld,time:%lfms\n",result->sum,result->tid,result->time);
    }
    
    printf("all finished \n");
    exit(0);
}

