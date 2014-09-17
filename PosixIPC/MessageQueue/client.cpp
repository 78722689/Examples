#include <stdlib.h>
#include <mqueue.h>
#include <signal.h>
#include "../common.h"


int main(int argc, char *argv[])
{
    mqd_t mqd;
    if(argc != 2)
    {
        printf("Usage: argc <2\n");
        exit(1);
    }
 
    mqd = mq_open(argv[1], O_WRONLY);
    if(mqd == (mqd_t)-1)
    {
        perror("mq_open");
        exit(1);
    }

    char message[128] = {'\0'};
    
    while (fgets(message, 128, stdin))
    {
        if (-1 == mq_send(mqd, message, strlen(message)+1, 10))
        {
            perror("mq_send");
            break;
        }
        if (0 == strcmp(message, "quit\n")) break;
    }

    mq_close(mqd);

    return 0;
}
 
