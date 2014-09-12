#include <stdio.h>

//�ڴ������Ҫ���ǵ����أ�
//1. ��Ա����=min(��Ա�������С), offset�����ǡ���Ա���롱��ֵ�ı���
//2. �������ʱ��Ҫ��������Ա�����أ� �������=min(max(��Ա1����Ա2������)�� �����С)�� 
// ���յĴ�С�����ǡ�������롱��ֵ�ı���

#pragma pack(8)

// ��Ա����
struct A
{               // 1 byte assignment                            4 byte assignment
    int a;      // 4 > 1����1�ֽڶ��룬offset=0~3       4 = 4����4�ֽڶ��룬offset=0~3
    char b;     // 1 = 1����1�ֽڶ��룬offset=4         1 < 4����1�ֽڶ��룬offset=4
    short c;    // 2 > 1, ��1�ֽڶ��룬offset=5~6       2 < 4, ��2�ֽڶ��룬offset=6~7
    char d;     // 1 = 1, ��1�ֽڶ��룬offset=7         1 > 4����1�ֽڶ��룬offset=8
}; 

// ��Ա����
struct B
{               // 1 byte assignment                            4 byte assignment
    A a;        // 8 > 1, ��1�ֽڶ��룬8offset=0~7      12 > 4����4�ֽڶ��룬offset=0~11
    int b;      // 4 > 1, ��1�ֽڶ��룬offset=8~11      4 = 4����4�ֽڶ��룬offset=12~15
    char c;     // 1 = 1, ��1�ֽڶ��룬offset=12        1 < 4����1�ֽڶ��룬offset=16
    double d;   // 8 > 1, ��1�ֽڶ��룬offset=13~20     8 > 4����4�ֽڶ��룬offset=20~27
    char e[10]; // 1 = 1, ��1�ֽڶ��룬offset=21~30     1 < 4����1�ֽڶ��룬offset=28~37
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
    printf("sizeof(S3)=%d \n", sizeof(s3));  // ������ݽṹ
    printf("sizeof(U)=%d \n", sizeof(u));  // union
    printf("sizeof(US)=%d \n", sizeof(us));  // union��Ͻṹ
    return 1;
}

/* 1byte ������*/
// �����
// sizeof(A)=8 
// sizeof(B)=31
// sizeof(C)=13
// sizeof(S3)=21

/* 4byte������*/
// �����
// sizeof(A)=12
// sizeof(B)=40
// sizeof(C)=16
// sizeof(S3)=22