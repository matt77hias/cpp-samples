// std::cout
// std::endl
#include <iostream>

struct A
{
    virtual void f(int) = 0;
    template< typename T >
    void f()
    {
        std::cout << "f<T>()" << std::endl;
        f(0);
    }
};

struct B : A
{
    using A::f;
    
    void f(int) override
    {
        std::cout << "f(int)" << std::endl;
    }
};

auto main()
	noexcept -> int
{
    B b;
    b.f(5);
    b.f< int >();

    return 0;
}
