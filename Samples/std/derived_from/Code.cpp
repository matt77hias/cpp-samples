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

auto main()
	-> int
{
    //f(A{});
    f(B{});
    f(C{});

	return 0;
}
