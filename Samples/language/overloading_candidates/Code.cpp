// same_as
#include <concepts>
// cout
#include <iostream>

void f(int)
{
    std::cout << "non-template function" << std::endl;
}

template< std::same_as< int > T >
void f(T)
{
    std::cout << "template function" << std::endl;
}

auto main()
   -> int
{
   f(1);
   f<>(1);
   
   return 0;
}
