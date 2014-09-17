#include <stdlib.h>
#include "../common.h"

#include <mqueue.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>

mqd_t mqd;

 
/*��ȡĳ��Ϣ����,��Ϣ������ͨ����������*/
/*������Ϣ���õ�ĳ���յĶ�����ʱ����SIGUSR1�ź�*/
int main(int argc, char *argv[])
{
    printf("%s; %s;%s\n", argv[0], argv[1], argv[2]);
    if(argc != 2)
    {
        printf("Usage: argc <2\n");
        exit(1);
    }
 
    /*ֻ��ģʽ����Ϣ����*/
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
 
