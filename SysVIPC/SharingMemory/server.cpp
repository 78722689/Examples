// Purpose: An example for learning SysV IPC APIs
// Author: ggdou@163.com

#include "common.h"

int main()
{
    char *shmptr = NULL, *buffer = NULL;
    key_t shm_key =-1;
    int shm_id = -1;

    shm_key = ftok("/tmp", 'a');
    if (-1 == shm_key)
    {
        perror("ftok");
        return 0;
    }
    
    shm_id = shmget(shm_key, SHARED_MEMORY_SIZE, IPC_CREAT| RW_USER_GROUP_OTHER);
    if (-1 == shm_id)
    {
        perror("shmget");
        return 0;
    }

    // attach memory to current process space.
    if ((shmptr = (char*)shmat(shm_id, 0, 0)) == (char *)-1)
    {
        perror("shmat");
        return 0;
    }
    
    memset(shmptr, 0, SHARED_MEMORY_SIZE);
    buffer = shmptr;
    
    char temp = '\0';
    while ('q' != *buffer)
    {
        sleep(1);
        if (temp == *buffer) continue;

        printf("Read characet %c\n", *buffer);
        temp = *buffer;
    }
    
    shmid_ds ds = {'\0'};
    if (0!= shmdt(shmptr) && 0 != shmctl(shm_id, IPC_RMID, &ds))
    {
        perror("shmdt && shmctl");
    }
    buffer=shmptr=NULL;
    
    return 1;
}