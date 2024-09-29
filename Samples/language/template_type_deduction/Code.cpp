// same_as
#include <concepts>

template< typename T >
void f(T x)
{
    static_assert(std::same_as< int, T >);
}

auto main()
    -> int
{
    int i = {};
    f(i);
    const int ci = {};
    f(ci);
    
    return 0;
}
