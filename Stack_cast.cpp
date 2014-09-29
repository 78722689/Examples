// Multi-inherit, invoke interface via base-class.
#include <stdio.h>

class receiver;

void test_static_cast(receiver& r);

class IA
{
public:
    virtual ~IA(){}
    
    virtual void handler(int i,int j)=0;
};

class IB
{
public:
    virtual ~IB(){}
    
    virtual void handler(int i)=0;
};

class receiver : public IB, public IA
{
public:
    receiver()
    {}
    virtual ~receiver()
    {}
    
    virtual void handler(int i)
    {
        test_static_cast(*this);
        printf("receiver::handler()\n");
    }
    
    IB& get() {return *this;}
};

class adapter: public receiver
{
public:
    adapter()
    {}
    virtual ~adapter()
    {}

    virtual void handler(int i, int j)
    {
        printf("adapter::handler()\n");
    }
};

void test_static_cast(receiver& r)
{
    static_cast<IA *>(&r)->handler(1, 100);
}

int main()
{
    adapter a;
    a.get().handler(12);
    
    getchar();
    return 1;
}