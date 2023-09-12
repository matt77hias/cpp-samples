// cout
#include <iostream>

[[nodiscard]]
constexpr auto f(int& i)
	noexcept -> int&
{ 
    return i; 
};

auto main()
    -> int
{
    int i = 5;
    auto j = f(i);
    j = 0;
    
    std::cout << i << ' ' << j;

    return 0;
}
