#include "my.h"

int main(int argc, char const *argv[])
{
    sigset_t base_mask,waiting_mask,oldmask;
    int sig;
    sigemptyset(&base_mask);
    sigaddset(&base_mask,SIGINT);
    if (sigprocmask(SIG_BLOCK,&base_mask,&oldmask)<0)
    {
        err_exit("SIG_BLOCK error");
    }
    printf("")
        
    return 0;
}
