// Reference to std::vector's implementation for placement new operator

#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <new>

void* operator new(std::size_t size, int value)
{
    std::cout << "operator new size "<< size << std::endl;
    return std::malloc(size);
}

template<class _Ty> inline
_Ty* _Allocate(size_t count, _Ty *)
{
    return (_Ty*)::operator new(count*sizeof(_Ty));
}

struct X {/*
    static void* operator new(std::size_t sz)
    {
        std::cout << "custom new for size " << sz << '\n';
        return ::operator new(sz);
    }
    static void* operator new[](std::size_t sz)
    {
        std::cout << "custom new for size " << sz << '\n';
        return ::operator new(sz);
    }*/
    int i;
};

int main()
{
    /*X* x=new(123) X;
    x->i=100;
    std::cout<<x->i<<std::endl;
    */
    
    int *y=new int[100];
    for(int i =100; i<200; ++i)
    {
        y[i%100]=i;
        std::cout<<"y["<<i%100<<"]"<<"="<<y[i%100];
    }
    std::cout<<std::endl;

    // Copy data from heap to stack
    int *x = new int[100];

    int *first=x;
    int *last = x+100;
    _Allocate(10, (int*)0);
    
    for(; first!=last;++first, ++y)
    {
        new (&(*first)) int(*y);
        //new (&(*x)) int(*y);
        std::cout << *x << "---";
    }

    return 1;
}