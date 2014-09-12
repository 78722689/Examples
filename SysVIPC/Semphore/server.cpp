// Purpose: An example for learning SysV semphore APIs
// Author: ggdou@163.com

#include "common.h"
#include <errno.h>


void init_sem(int semId, int semnum, int initValue)
{
    semun sem_val;

    sem_val.val = initValue;
    if (-1 == semctl(semId, semnum, SETVAL, sem_val))
        perror("semctl");
    
}

// Require one resource
void P(int semId)
{
    sembuf sem_op;
    
    sem_op.sem_num=0;
    sem_op.sem_op=-1;
    sem_op.sem_flg=0;
    
    semop(semId, &sem_op, 1);
}

int main()
{
    int sem_id = -1;
    key_t msg_key = -1;
    
    msg_key = ftok("/btsom/LTE_CHE1/lxj", 'a');
    if (-1 == msg_key)
    {
        perror("ftok");
        return 0;
    }

    sem_id = semget(msg_key, 1, IPC_CREAT | RW_USER_GROUP_OTHER);
    if (-1 == sem_id)
    {
        perror("shmget");
        return 0;
    }
   
    init_sem(sem_id, 0, 0);
    
    // wait sem get ready.
    P(sem_id);
    printf("P over...\n");
    
    // remove sem from kernel.
    semun sem_val;
    semctl(sem_id, 0, IPC_RMID, sem_val);
    return 1;
}
