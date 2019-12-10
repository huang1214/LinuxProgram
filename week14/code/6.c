#include "my.h"
#define NUM_THREADS 8
char *message[NUM_THREADS];
struct thread_data
{
    int thread_id;
    int sum;
    char *message;
};
struct thread_data thread_array[NUM_THREADS];
void *PrintHello(void *threadarg){
    int taskid,sum;
    char *hello_msg;
    struct thread_data *my_data;
    sleep(1);
    my_data = (struct thread_data *) threadarg;
    taskid = my_data->thread_id;
    sum = my_data->sum;
    hello_msg = my_data->message;
    printf("Tread %d:%s sum=%d\n",taskid,hello_msg,sum);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc,t,sum;
    sum = 0;
    message[0] = "Hello world";    
    message[1] = "中文 你好世界";
    message[2] = "法语不会";
    message[3] = "德语不会";
    message[4] = "日语不会";
    message[5] = "韩语不会";
    message[6] = "西班牙语不会";
    message[7] = "蒙古语不会";
    for ( t = 0; t < NUM_THREADS; t++)
    {
        sum = sum + t;
        thread_array[t].thread_id = t;
        thread_array[t].sum = sum;
        thread_array[t].message = message[t];
        printf("create thread %d\n",t);
        rc = pthread_create(&threads[t],NULL,PrintHello,(void *)&thread_array[t]);
        if (rc)
        {   
            perror("错误");
            exit(-1);
        }
        
    }
    pthread_exit(NULL);
}

