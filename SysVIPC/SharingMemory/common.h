// Purpose: Macros and SysV headers
// Author: ggdou@163.com

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <error.h>
#include <unistd.h>
#include <string.h>

//SHM_R 0200
//SHM_W 0400
#define RW_USER (SHM_R | SHM_W)
#define RW_GROUP (SHM_R >> 3 | SHM_W >> 3)
#define RW_OTHER (SHM_R >> 6 | SHM_W >> 6)

// Read&Write of permission to user&group&other process
#define RW_USER_GROUP_OTHER (RW_USER | RW_GROUP | RW_OTHER)   // 0666 

// The chunk of shared memory size
#define SHARED_MEMORY_SIZE 1024