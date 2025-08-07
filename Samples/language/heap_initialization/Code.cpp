// std::cout
// std::endl
#include <iostream>

auto main()
    -> int
{
    const auto x = new int;
    const auto y = new int();
    const auto z = new int{};

    const auto a = new int[2u];
    const auto b = new int[2u]();
    const auto c = new int[2u]{};

    std::cout << *x << std::endl;
    std::cout << *y << std::endl;
    std::cout << *z << std::endl;

    std::cout << a[0] << ' ' << a[1] << std::endl;
    std::cout << b[0] << ' ' << b[1] << std::endl;
    std::cout << c[0] << ' ' << c[1] << std::endl;
    
    return 0;
}
