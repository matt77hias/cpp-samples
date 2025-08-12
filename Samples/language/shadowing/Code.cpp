// std::floating_point
#include <concepts>
// std::cout
#include <iostream>

template< typename T  >
void test()
{
    std::cout << "test< T >()";
}

namespace inner
{
    template< std::floating_point F >
    void test()
    {
        std::cout << "inner::test< F >()";
    }

    void main()
    {
        test< float >();
        // test< int >(); shawdowed
    }
}

auto main()
    -> int
{
    inner::main();

    return 0;
}
