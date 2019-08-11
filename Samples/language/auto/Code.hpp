// cout
#include <iostream>

[[nodiscard]]
constexpr int& f(int& i) noexcept
{ 
    return i; 
};

int main()
{
    int i = 5;
    auto j = f(i);
    j = 0;
    
    std::cout << i << ' ' << j;

    return 0;
}
