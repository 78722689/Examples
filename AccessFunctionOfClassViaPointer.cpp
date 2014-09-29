// A pointer which points the function/static function, and it is provided by clsss.
#include <stdio.h>


class A
{
public:
    virtual ~A(){}
    
    void handler(int i,int j)
    {
        printf("handler(%d, %d).\n", i, j);
    }
    
    static void handler(int i)
    {
        printf("static handler(%d)\n", i);
    }
};

typedef void (A::* HANDLER)(int, int);
typedef void (*STATIC_HANDLER)(int); // No class A for statck member of class

int main()
{
    HANDLER handle=&A::handler;
    STATIC_HANDLER static_handler = &A::handler;
    
    A a;    
    
    // call them via pointer
    (a.*handle)(100, 200);
    (*static_handler)(300);
    getchar();
    return 1;
}