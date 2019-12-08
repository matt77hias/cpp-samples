// bitset
#include <bitset>
// cout, endl
#include <iostream>

int main()
{
    constexpr auto a = 27u;
    constexpr auto b = 7u; // versus 0u
    
    std::bitset< 32u > c1(  !b);
    std::bitset< 32u > c2( !!b);
    std::bitset< 32u > c3(-!!b);
    
    std::cout << c1 << std::endl;
    std::cout << c2 << std::endl;
    std::cout << c3 << std::endl;
    
    std::cout << (a & -!!b) << std::endl;
    return 0;
}
