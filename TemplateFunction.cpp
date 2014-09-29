
// To show how to seperate the template of class member function from head(.h) and source file(.cpp).

#include "TemplateFunction.h"
using namespace templatetest; // if namespace used in header file, then it should be imported into source file.

template<typename T>
template<typename X>
void MyTemplate<T>::test1(T* t, void (T::*func)(const X&))
{
    (t->*func)(1238888);
}

template<typename T, typename X>
void TemplateMember::test1(T* t, void (T::*func)(const X&))
{
    (t->*func)(5656);
}


class A
{
public:
    void testTemplate1()
    {
        MyTemplate<A> tem;
        tem.test2(this, &A::print);
    }
    
    void testTemplate2()
    {
        TemplateMember tem;
        tem.test1(this, &A::print);
    }
    
    void print(const int& value)
    {
        printf("A::print(%d)\n", value);
    }
};

int main()
{
    A a;
    a.testTemplate1();
    a.testTemplate2();
}