// convertible_to
#include <concepts>
 
struct A
{};
 
struct B : A
{};
 
struct C : B
{};

template< std::convertible_to< B > T >
void f(T t)
{

}

int main() 
{
    //f(A{});
    f(B{});
    f(C{});
}
