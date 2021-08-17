// derived_from
#include <concepts>
 
struct A
{};
 
struct B : A
{};
 
struct C : B
{};

template< std::derived_from< B > T >
void f(T t)
{

}

int main() 
{
    //f(A{});
    f(B{});
    f(C{});
}
