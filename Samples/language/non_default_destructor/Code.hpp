// cout, endl
#include <iostream>

struct A
{
    ~A() { std::cout << "A::~A()" << std::endl; }
};

struct B
{
    ~B() { std::cout << "B::~B()" << std::endl; }
    A m_a;
};

int main()
{
    B b;
	
    return 0;
}
