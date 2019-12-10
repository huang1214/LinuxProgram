#include "my.h"

#define SIZE 16
int a[SIZE],b[SIZE];

void check_error(return_val,msg){ 
    if (return_val!=0)
    {
        fprintf(stderr,"%s :%s\n",msg,strerror(return_val));
        exit(-1);
    }
}

void max_fun(int *arg)
{
    
    int *ap = arg;
    int rv,i,k;
    k = 0;
    for ( i = 0; i < SIZE; i++)
    {
        if (ap[i] > ap[k])
        {
            k = i;
        }
    }
    pthread_exit((void *)&ap[k]);
    
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    pthread_t tid1,tid2;
    int i,rv,**ptr1,**ptr2;
    for ( i = 0; i < SIZE; i++)
    {
        a[i] = rand();
        b[i] = rand();
    }
    rv = pthread_create(&tid1,NULL,(void*(*)())max_fun,a);
    check_error(rv,"failed thread tid1");
    rv = pthread_create(&tid2,NULL,(void*(*)())max_fun,b);
    check_error(rv,"failed thread tid2");
    pthread_join(tid1,(void **)&ptr1);
    pthread_join(tid2,(void **)&ptr2);
    printf("thread1 max value is %d\n",*ptr1);
    printf("thread2 max value is %d\n",*ptr2);
    printf("max value is %d\n",(*ptr1)>(*ptr2)?(*ptr1):(*ptr2));
    exit(0);
}
