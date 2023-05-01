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

auto main()
	-> int
{
    //f(A{});
    f(B{});
    f(C{});
}
