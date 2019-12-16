#include "my.h"
#define SIZE 100
int a[SIZE],b[SIZE];
int max = 0;
pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
void *max_fun(void *arg)
{
    int *ap = (int *)arg;
    int i = 0;
    int lmax = 0;
    for ( i = 0; i < SIZE; i++)
    {
        if (ap[i] > lmax)
        {
            lmax = ap[i];
        }
    }
    pthread_mutex_lock(&mutex);
    if (lmax > max)
    {
        max = lmax;
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
    
}

int main(int argc, char const *argv[])
{
    pthread_t tid1,tid2;
    int i,rv;
    for ( i = 0; i < SIZE; i++)
    {
        a[i] = rand()%5000;
        b[i] = rand()%5000;
    }
    rv = pthread_create(&tid1,NULL,max_fun,a);
    if (rv)
    {
        perror("线程1创建失败\n");
        exit(1);
    }
    rv = pthread_create(&tid2,NULL,max_fun,b);
    if (rv)
    {
        perror("线程2创建失败\n");
        exit(2);
    }
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    printf("max values :%d\n",max);
    return 0;
}
