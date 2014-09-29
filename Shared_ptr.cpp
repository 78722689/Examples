// Shared_ptr & std::list & std::auto_ptr

#include <stdio.h>
#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"

#include <memory>
#include <list>

class A
{
public:
    A(int i) : i_(i)
    {
        printf("A(%d)\n", i_);
    }
    ~A()
    {
        printf("~A(%d)\n", i_);
    }
    
private:
    int i_;
};

//typedef std::list<std::auto_ptr<A> > A_LIST;
    
void test_smartptr_release_with_list()
{
    //A_LIST alist;
    
    for (int i = 0; i < 10; ++i)
    {
        ;//alist.push_back(std::auto_ptr<A>(i));
    }
}

int main()
{

    test_smartptr_release_with_list();
    
    getchar();
    return 1;
}