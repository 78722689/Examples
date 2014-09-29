#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <signal.h>
#include "../common.h"

// NOTE(mq_notify): 
// 1. At any time, only one process may be registered for notification by a specific message queue.
// 2. When the notification is sent to the registered process, its registration is removed, and the message queue is then be available for registration.

int main(int argc, char *argv[])
{
    mqd_t mqd;
    struct mq_attr attr;
    struct sigevent sigev;
    char *ptr;
    sigset_t newmask = {'\0'};
    int signo = -1;
    unsigned int prio;
    
    printf("Arg1: %s; Arg2: %s\n", argv[0], argv[1]);
    if(argc != 2)
    {
        printf("Please at least input 1 argument\n");
        exit(1);
    }
 
    mqd = mq_open(argv[1], O_RDONLY | O_CREAT);
    if(mqd == (mqd_t)-1)
    {
        perror("mq_open");
        exit(1);
    }
 
    // Read property from message queue and allocate the memory from achiving attribute.
    if(mq_getattr(mqd, &attr) < 0)
    {
        perror("get attr failure");
        exit(1);
    }

    ptr = (char*)calloc(attr.mq_msgsize, sizeof(char));
    if(NULL == ptr)
    {
        printf("allocate memory failure\n");
        mq_close(mqd);
        exit(1);
    }
 
    // reset sigset and fill the mask with SIGUSR1
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &newmask, NULL);

    // Register notification.
    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = SIGUSR1;
    if(mq_notify(mqd, &sigev) < 0) // 
    {
        perror("Register failure.");
        mq_close(mqd);
        free(ptr);
        exit(1);
    }

    size_t ret = -1;
    for(;;)
    {
        // Waiting the singal with the queue changing from empty to non-empty
        sigwait(&newmask, &signo);
        if (SIGUSR1 == signo)
        {
            // Register again after signal arrived.
            mq_notify(mqd, &sigev);
            
            if ((ret = mq_receive(mqd, ptr, attr.mq_msgsize, &prio)) < 0)
            {
                perror("mq_receive");
                break;
            }
            
            printf(" Received: %ld bytes\n context: %s proid:%u\n", (long)ret, ptr, prio);
            
            if (0 == strcmp(ptr, "quit\n")) break;
        }
    }
    
    mq_close(mqd);
    free(ptr);
 
    return 0;
}
 