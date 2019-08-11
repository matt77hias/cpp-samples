// array
#include <array>
// cout, endl
#include <iostream>
// get, tuple, tuple_cat
#include <tuple>
 
int main()
{
    constexpr std::array< int, 2u > a = { 1, 2 };
    constexpr std::tuple< int, int > t = std::tuple_cat(a);
    std::cout << std::get< 0u >(t) << ' ' << std::get< 1u >(t) << std::endl;
    
    return 0;
}
