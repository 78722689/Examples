// Purpose: An example for learning SysV message queue APIs
// Author: ggdou@163.com

#include "common.h"
#include <errno.h>

int main()
{
    stBuffer buffer = {'\0'};
    buffer.mType = 1;
    int msg_id = -1;
    key_t msg_key = -1;
    
    msg_key = ftok("/btsom/LTE_CHE1/lxj", 'a');
    if (-1 == msg_key)
    {
        perror("ftok");
        return 0;
    }

    msg_id = msgget(msg_key, IPC_CREAT | RW_USER_GROUP_OTHER);
    if (-1 == msg_id)
    {
        perror("shmget");
        return 0;
    }
    
    memset(buffer.context, 0, BUFFER_SIZE);
   
    char input[BUFFER_SIZE] = {'\0'};
    int length = sizeof(stBuffer)-sizeof(long);

    while (1)
    {
        if ((-1 == msgrcv(msg_id, &buffer, length, 0, 0)))
        {
            printf("errno=%d\n", errno);
            perror("msgrcv");
            return 0;
        }
        printf("msgrcv sucess: %s.\n", buffer.context);
    }
    
    msgctl(msg_id, IPC_RMID, 0);
    return 1;
}
