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
    mqd = mq_open(argv[1], O_RDONLY | O_CREAT);
    if(mqd == (mqd_t)-1)
    {
        printf("%d\n", errno);
        perror("mq_open");
        exit(1);
    }
 
    // 取得消息队列属性，根据mq_msgsize动态申请内存
    rc = mq_getattr(mqd, &attr);
    if(rc < 0)
    {
        perror("取得消息队列属性失败");
        exit(1);
    }
 
    /*动态申请保证能存放单条消息的内存*/
    ptr = (char*)calloc(attr.mq_msgsize, sizeof(char));
    if(NULL == ptr)
    {
        printf("动态申请内存失败\n");
        mq_close(mqd);
        exit(1);
    }
 
    //注册信号函数
    signal(SIGUSR1, sig_usr1);
    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = SIGUSR1;
 
    //注册通知
    rc = mq_notify(mqd, &sigev); // 读取前需要再次注册
    if(rc < 0)
    {
        perror("通知注册失败");
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
    rc = mq_notify(mqd, &sigev); // 读取前需要再次注册
    if(rc < 0)
    {
        perror("通知注册失败");
        mq_close(mqd);
        free(ptr);
        exit(1);
    }
 
    printf("mq_notify 2 done\n");
    /*接收一条消息*/
    n = mq_receive(mqd, ptr, attr.mq_msgsize, &prio);
    if(n < 0)
    {
        perror("读取失败");
        mq_close(mqd);
        free(ptr);
        exit(1);
    }
    printf("Read: %ld byte\n context:%s\n proid: %u\n", (long)n, ptr, prio);
}