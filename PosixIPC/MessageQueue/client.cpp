#include <stdlib.h>
#include "../common.h"

#include <mqueue.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>

mqd_t mqd;

 
/*读取某消息队列,消息队列名通过参数传递*/
/*当有消息放置到某个空的队列中时产生SIGUSR1信号*/
int main(int argc, char *argv[])
{
    printf("%s; %s;%s\n", argv[0], argv[1], argv[2]);
    if(argc != 2)
    {
        printf("Usage: argc <2\n");
        exit(1);
    }
 
    /*只读模式打开消息队列*/
    mqd = mq_open(argv[1], O_WRONLY);
    if(mqd == (mqd_t)-1)
    {
        printf("%d\n", errno);
        perror("mq_open");
        exit(1);
    }

    char message[128] = {'\0'};
    
    while (fgets(message, 128, stdin) && 0 != strcmp(message, "quit\n"))
    {
        if (-1 == mq_send(mqd, message, strlen(message)+1, 10))
        {
            perror("mq_send");
            break;
        }
    }

    mq_close(mqd);

    return 0;
}
 
