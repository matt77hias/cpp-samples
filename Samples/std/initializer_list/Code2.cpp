// std::same_as
#include <concepts>
// std::initializer_list
#include <initializer_list>
// std::cout
// std::endl
#include <iostream>

struct A
{
    A()
    {
        std::cout << "default" << std::endl;
    }
    
    template< typename T = int >
    A(std::initializer_list< T >)
    {
        if constexpr (std::same_as< T, int >)
        {
            std::cout << "initializer_list int" << std::endl;
        }
        else
        {
            std::cout << "initializer_list" << std::endl;
        }
    }
};

auto main()
	noexcept -> int
{
    [[maybe_unused]] A a0 = {};
    [[maybe_unused]]A a1 = { 1.0f };
    [[maybe_unused]]A a2 = { {} };

    return 0;
}
