#include "my.h"
#define NUM 4
void fun(void *arg)
{
    int *pt;
    pt = (int *) arg;
    printf("worker thread %d:tid = %p\n",(int)pt,pthread_self());
}

int main(int argc, char const *argv[])
{
    pthread_t tid[NUM];
    int ret;
    int i,j;
    for ( i = 0; i < NUM; i++)
    {
        pthread_create(&tid[i],NULL,(void *(*))fun,(void *)i);
    }
    for ( j = 0; j < NUM; j++)
    {
        pthread_join(&tid[j],NULL);
    }
    printf("all finished \n");
    return 0;
}
