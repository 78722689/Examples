#include <stdio.h>

namespace templatetest
{

// Template member and struct
template<typename T>
struct MyTemplate
{
    
    template<typename X>
    void test1(T* t, void (T::*func)(const X&));
};

// Only template member
struct TemplateMember
{
    template<typename T, typename X>
    void test1(T* t, void (T::*func)(const X&));
};

}