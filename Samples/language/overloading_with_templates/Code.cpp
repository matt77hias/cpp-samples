// cout, endl
#include <iostream>

struct A
{};

template< typename T >
struct B : A
{};

void f(A)
{
    std::cout << "void f(A)" << std::endl;
}

template< typename T >
void f(B< T > b)
{
    std::cout << "void f(B< T >)" << std::endl;
    f(static_cast< A >(b));
}

int main()
{
	f(B< int >{});
    
    return 0;
}
