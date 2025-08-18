// std::size_t
#include <cstddef>
// std::cout
// std::endl
#include <iostream>
// std::ranges::iota_view
#include <ranges>

auto main()
	-> int
{
    constexpr std::ranges::iota_view< std::size_t, std::size_t > empty_range{};
    std::cout << *empty_range.begin() << std::endl; 
    std::cout << *empty_range.end()   << std::endl; 
    std::cout <<  empty_range.empty() << std::endl; 
    std::cout <<  empty_range.size()  << std::endl; 
    
    constexpr std::ranges::iota_view< std::size_t, std::size_t > range{ 1u, 10u };
    std::cout << *range.begin() << std::endl; 
    std::cout << *range.end()   << std::endl; 
    std::cout <<  range.empty() << std::endl; 
    std::cout <<  range.size()  << std::endl; 

    std::cout <<  sizeof(std::size_t)  << std::endl; 
    std::cout <<  sizeof(range)        << std::endl; 
    
    return 0;
}
