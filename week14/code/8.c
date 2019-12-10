#include "my.h"

extern int get_user_cmd();

enum command {
    QUIT = 0, WORK/*,..*/};

struct thread {
    int no;
    enum command cmd;
};

void thread_func(struct thread *);

enum command get_usr_cmd() {
    int cmd;
    printf("Please enter a command number(0-9\n");
    scanf("%d", &cmd);
    return (enum command) cmd;
}

int main(void) {
    pthread_t tid;
    int rv, cmd, k = 0;
    struct thread *last_thread, *tp;e

    while (1) {
        cmd = get_user_cmd();
        if (cmd == QUIT) {
            printf("Inite thread will finish soon \n");
            pthread_exit((void *) NULL);
        }
        tp = (struct thread *) malloc(sizeof(struct thread));
        tp->no = k++;
        tp->cmd = cmd;
        rv = pthread_create(&tid, NULL, (void *(*)()) thread_func, (void *) tp);
        printf("create thread %d\n");
        rv = pthread_detach(tid);
    }
}

void thread_fun(struct thread *thread_p)
{
    printf("\nThread %d created with command number %d is running\n",thread_p->no,thread_p->cmd);
    sleep(thread_p->cmd);
    printf("\n Thread %d finished\n",thread_p->no);
    pthread_exit(NULL);
}