// Purpose: An example for learning POSIX sharing memory APIs
// Author: ggdou@163.com

#include "../common.h"

int main()
{
    int fd = -1, ret = -1;
    char *shmptr = NULL, *buffer = NULL;
    key_t shm_key =-1;

    fd = shm_open("POSIXSM", O_RDWR | O_CREAT, RW_USER_GROUP_OTHER);
    if (fd < 0)
    {
        perror("shm_open");
        return 0;
    }

    // Set memory size of sharing 
    if (-1 ==ftruncate(fd, SHARED_MEMORY_SIZE))
    {
        shm_unlink("POSIXSM");
        return 0;
    }
    
    shmptr = (char*)mmap(0, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (MAP_FAILED == shmptr)
    {
        perror("mmap");
        shm_unlink("POSIXSM");
        return 0;
    }
    
    memset(shmptr, 0, SHARED_MEMORY_SIZE);
    buffer = shmptr;
    
    char context[SHARED_MEMORY_SIZE] = {'\0'};
    while (0 != strcmp(context, "quit\n"))
    {
        sleep(1);
        memcpy(context, buffer, SHARED_MEMORY_SIZE);
        printf("Read characets %s\n", context);
    }
    
    if (-1 == munmap(shmptr, SHARED_MEMORY_SIZE))
    {
        perror("munmap");
    }
    if (-1 == shm_unlink("POSIXSM"))
    {
        perror("shm_unlink");
    }
    buffer=shmptr=NULL;
    
    return 1;
}