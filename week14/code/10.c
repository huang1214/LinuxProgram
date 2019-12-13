#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_function(void *arg);
int run_now = 1;
pthread_mutex_t work_mutex; // 定义互斥量

void *thread_function(void *arg){
    int print_count2 = 0;
    sleep(1);
    if (pthread_mutex_lock(&work_mutex))
    {
        perror("lock failed\n");
        exit(1);
    }
    else
    {
        printf("function lock\n");
    }
    while (print_count2++<5)
    {
        if (run_now==2)
        {
            printf("function thread is run\n");
            run_now = 1;
        }
        else
        {
            printf("function thread is sleep\n");
            sleep(1);
        }
    }
    if (pthread_mutex_unlock(&work_mutex))
    {
        perror("unlock failed\n");
        exit(1);
    }
    else
    {
        printf("function unlock\n");
    }
    pthread_exit(NULL);
    
}
int main(int argc, char const *argv[])
{
    int res;
    int print_count1 = 0;
    pthread_t a_thread;
    if (pthread_mutex_init(&work_mutex,NULL))
    {
        perror("mutex  init failed\n");
        exit(1);
    }
    if (pthread_create(&a_thread,NULL,thread_function,NULL))
    {
        perror("Thread create failed\n");
        exit(1);
    }
    if (pthread_mutex_lock(&work_mutex))
    {
        perror("Lock failed\n");
        exit(1);
    }
    else
    {
        printf("main lock\n");
    }
    while (print_count1++<5)
    {
        if (run_now == 1)
        {
            printf("main thread is run\n");
            run_now = 2;
        }
        else
        {
            printf("main thread is sleep\n");
            sleep(1);
        }
    }
    if (pthread_mutex_unlock(&work_mutex))
    {
        perror("unlock failed\n");
        exit(1);
    }
    else
    {
        printf("main unlock\n");
    }
    pthread_mutex_destroy(&work_mutex);
    pthread_join(a_thread,NULL);
    exit(0);

}