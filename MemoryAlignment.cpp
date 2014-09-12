#include <stdio.h>

//内存对齐需要考虑的因素：
//1. 成员对齐=min(成员，对齐大小), offset必须是“成员对齐”的值的倍数
//2. 整体对齐时需要考虑最大成员的因素， 整体对齐=min(max(成员1，成员2，，，)， 对齐大小)， 
// 最终的大小必须是“整体对齐”的值的倍数

#pragma pack(8)

// 成员对齐
struct A
{               // 1 byte assignment                            4 byte assignment
    int a;      // 4 > 1，按1字节对齐，offset=0~3       4 = 4，按4字节对齐，offset=0~3
    char b;     // 1 = 1，按1字节对齐，offset=4         1 < 4，按1字节对齐，offset=4
    short c;    // 2 > 1, 按1字节对齐，offset=5~6       2 < 4, 按2字节对齐，offset=6~7
    char d;     // 1 = 1, 按1字节对齐，offset=7         1 > 4，按1字节对齐，offset=8
}; 

// 成员对齐
struct B
{               // 1 byte assignment                            4 byte assignment
    A a;        // 8 > 1, 按1字节对齐，8offset=0~7      12 > 4，按4字节对齐，offset=0~11
    int b;      // 4 > 1, 按1字节对齐，offset=8~11      4 = 4，按4字节对齐，offset=12~15
    char c;     // 1 = 1, 按1字节对齐，offset=12        1 < 4，按1字节对齐，offset=16
    double d;   // 8 > 1, 按1字节对齐，offset=13~20     8 > 4，按4字节对齐，offset=20~27
    char e[10]; // 1 = 1, 按1字节对齐，offset=21~30     1 < 4，按1字节对齐，offset=28~37
};

struct C
{
    char a;
    double b;
    int c;
};

struct s1
{
    short a[8];  // 0~15
    short x;       // 16~17
    short y;       // 18 ~ 19
}; //20byte

struct s3
{
    s1 s;   // 0~19
    char a; //20
};

union u
{
    char a;
    int i[5];
    double b;
};

struct us
{
    char a;
    int i;
    u uu;
    double d;
};
int main()
{
    printf("sizeof(A)=%d \n", sizeof(A));
    printf("sizeof(B)=%d \n", sizeof(B));
    printf("sizeof(C)=%d \n", sizeof(C));
    printf("sizeof(S3)=%d \n", sizeof(s3));  // 混合数据结构
    printf("sizeof(U)=%d \n", sizeof(u));  // union
    printf("sizeof(US)=%d \n", sizeof(us));  // union混合结构
    return 1;
}

/* 1byte 对齐结果*/
// 输出：
// sizeof(A)=8 
// sizeof(B)=31
// sizeof(C)=13
// sizeof(S3)=21

/* 4byte对齐结果*/
// 输出：
// sizeof(A)=12
// sizeof(B)=40
// sizeof(C)=16
// sizeof(S3)=22