#include <array>
#include <iostream>
#include <tuple>
 
int main()
{
    std::array< int, 2u > a = { 1, 2 };
    std::tuple< int, int > t = std::tuple_cat(a);
    std::cout << std::get< 0u >(t);
    std::cout << ' ';
    std::cout << std::get< 1u >(t);
    return 0;
}
