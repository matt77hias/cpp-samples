// std::array
#include <array>
// std::cout
// std::endl
#include <iostream>
// std::get
// std::tuple
// std::tuple_cat
#include <tuple>
 
auto main()
	-> int
{
    constexpr std::array< int, 2u > a = { 1, 2 };
    constexpr std::tuple< int, int > t = std::tuple_cat(a);
    std::cout << std::get< 0u >(t) << ' ' << std::get< 1u >(t) << std::endl;
    
    return 0;
}
