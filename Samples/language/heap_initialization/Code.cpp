// cout, endl
#include <iostream>

auto main()
    -> int
{
    const auto x = new int;
    const auto y = new int();
    const auto z = new int{};

    const auto a = new int[2];
    const auto b = new int[2]();
    const auto c = new int[2]{};

    std::cout << *x << std::endl;
    std::cout << *y << std::endl;
    std::cout << *z << std::endl;

    std::cout << a[0u] << ' ' << a[1u] << std::endl;
    std::cout << b[0u] << ' ' << b[1u] << std::endl;
    std::cout << c[0u] << ' ' << c[1u] << std::endl;
    
    return 0;
}
