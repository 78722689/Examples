#include <stdio.h>

#pragma pack(4) // force 4 bits of memory assignment
int main()
{
    int x = 101;
    int y = 1099;
    int &z = x;
    
    printf("&x=0x%x, &y=0x%x, &z=0x%x, &y-1=0x%x, *(&y-1)=%d \n",
            &x, &y, &z, &y-1, *(&y-1));
    
    return 1;
}