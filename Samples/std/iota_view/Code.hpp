// cout, endl
#include <iostream>
// iota_view
#include <ranges>

int main()
{
    auto range = std::ranges::iota_view{1, 10};
    std::cout << *range.begin() << std::endl; 
    std::cout << *range.end()   << std::endl; 
    std::cout <<  range.empty() << std::endl; 
    std::cout <<  range.size()  << std::endl; 
    return sizeof(range);
}
