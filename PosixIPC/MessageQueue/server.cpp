#include <stdlib.h>
#include "../common.h"

#include <mqueue.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>

mqd_t mqd;
struct mq_attr attr;
struct sigevent sigev;
char *ptr;
unsigned int prio;
size_t n;
int rc;
 
void sig_usr1(int signo);
 
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
    mqd = mq_open(argv[1], O_RDONLY | O_CREAT);
    if(mqd == (mqd_t)-1)
    {
        printf("%d\n", errno);
        perror("mq_open");
        exit(1);
    }
 
    // ȡ����Ϣ�������ԣ�����mq_msgsize��̬�����ڴ�
    rc = mq_getattr(mqd, &attr);
    if(rc < 0)
    {
        perror("ȡ����Ϣ��������ʧ��");
        exit(1);
    }
 
    /*��̬���뱣֤�ܴ�ŵ�����Ϣ���ڴ�*/
    ptr = (char*)calloc(attr.mq_msgsize, sizeof(char));
    if(NULL == ptr)
    {
        printf("��̬�����ڴ�ʧ��\n");
        mq_close(mqd);
        exit(1);
    }
 
    //ע���źź���
    signal(SIGUSR1, sig_usr1);
    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = SIGUSR1;
 
    //ע��֪ͨ
    rc = mq_notify(mqd, &sigev); // ��ȡǰ��Ҫ�ٴ�ע��
    if(rc < 0)
    {
        perror("֪ͨע��ʧ��");
        mq_close(mqd);
        free(ptr);
        exit(1);
    }
    printf("mq_notify 1 done\n");
    for(;;)
    {
        printf("pause\n");
        pause();
    }
 
    return 0;
}
 
void sig_usr1(int signo)
{
    rc = mq_notify(mqd, &sigev); // ��ȡǰ��Ҫ�ٴ�ע��
    if(rc < 0)
    {
        perror("֪ͨע��ʧ��");
        mq_close(mqd);
        free(ptr);
        exit(1);
    }
 
    printf("mq_notify 2 done\n");
    /*����һ����Ϣ*/
    n = mq_receive(mqd, ptr, attr.mq_msgsize, &prio);
    if(n < 0)
    {
        perror("��ȡʧ��");
        mq_close(mqd);
        free(ptr);
        exit(1);
    }
    printf("Read: %ld byte\n context:%s\n proid: %u\n", (long)n, ptr, prio);
}