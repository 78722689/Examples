// Title: Friend function & Access protected member function
// Perpose: To access protected member function via friend function instead of via get() of public member function. 

#include <stdio.h>
#include <iostream>
#include <ostream>

class base
{
    friend std::ostream& operator << (std::ostream& stream, const base& b);
    
protected:
    virtual void calculate() const
    {
        printf("base::cacluate()\n");
    }

};

inline std::ostream& operator << (std::ostream& stream, const base& b)
{
    b.calculate();
    
    return stream;
}

class Derived : public base
{

protected:
    virtual void calculate() const
    {
        printf("Derived::calculate()\n");
    }
};


int main()
{
    
    Derived d;
    std::cout << d;

    getchar();
}