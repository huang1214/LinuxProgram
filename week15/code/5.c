// 版本1，buf满了之后就唤醒消费者，消费者，生产者都为1
// 版本2，有三个消费者
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 5 
#define TCOUNT      5 
#define COUNT_LIMIT 10 

int count = 0;
int thread_ids[5] = {0,1,2,3,4};
pthread_mutex_t count_mutex;
pthread_cond_t  count_threshold_cv;

void *inc_count(void *idp)
{
    int i = 0;
    int taskid = 0;
    int *my_id = (int*)idp;

    for (i=0; i<TCOUNT; i++) {
        pthread_mutex_lock(&count_mutex);
        taskid = count;
        count++;

        /*
          唤醒一个阻塞在该条件变量到线程
          如果没有线程被阻塞在条件变量上，那么调用pthread_cond_signal()将没有作用
        */
        pthread_cond_signal(&count_threshold_cv);

        printf("inc_count(): thread %d, count = %d, unlocking mutex\n", *my_id, count);
        pthread_mutex_unlock(&count_mutex);
        sleep(1);
    }
    printf("inc_count(): thread %d, Threshold reached.\n", *my_id);

    pthread_exit(NULL);
}

void *producer(void *p)
{
    int *my_id = (int *)p;
	while(1)
	{
		printf("Producer  %d ---------\n",*my_id);
		pthread_mutex_lock(&count_mutex);
        // 处理库存count.+1,模拟生产产品
        while (count < 5)
        {
            count++;
            printf("producer count: %d\n",count);
            pthread_cond_signal(&count_threshold_cv);
        }
		pthread_mutex_unlock(&count_mutex);
		//pthread_cond_signal(&count_threshold_cv);
		sleep(rand() % 5);
	}
	pthread_exit(NULL);
}

void *consumer(void *p)
{
	int *my_id = (int *)p;
	while(1)
	{
        printf("Consumer %d --------\n",*my_id);
		pthread_mutex_lock(&count_mutex);
		while(count == 0)
			pthread_cond_wait(&count_threshold_cv,&count_mutex);
        count--;
        printf("consumer count: %d\n",count);
		pthread_mutex_unlock(&count_mutex);
		
		sleep(rand() % 5);
	}
	pthread_exit(NULL);
}

void *watch_count(void *idp)
{
    int *my_id = (int*)idp;
    printf("Starting watch_count(): thread %d\n", *my_id);
    pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
    int i, rc;
    pthread_t threads[5];
    pthread_attr_t attr;

    /* Initialize mutex and condition variable objects */
    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init (&count_threshold_cv, NULL);

    /* For portability, explicitly create threads in a joinable state */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threads[0], &attr, producer,   (void *)&thread_ids[0]);
    pthread_create(&threads[1], &attr, consumer,   (void *)&thread_ids[1]);
    pthread_create(&threads[2], &attr, consumer, (void *)&thread_ids[2]);
    pthread_create(&threads[3], &attr, consumer, (void *)&thread_ids[3]);
    //pthread_create(&threads[4], &attr, watch_count, (void *)&thread_ids[4]);

    /* Wait for all threads to complete */
    for (i=0; i<NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf ("Main(): Waited on %d  threads. Done.\n", NUM_THREADS);

    /* Clean up and exit */
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold_cv);
    pthread_exit(NULL);

    return 0;
}