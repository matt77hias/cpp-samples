// std::cout
// std::endl
#include <iostream>
// std::from_chars
// std::from_chars_result
#include <charconv>
// std::size_t
#include <cstddef>
// std::size
#include <iterator>
// std::string_view
#include <string_view>
 
auto main()
    -> int
{
    constexpr std::string_view strs[] = { "K", "10", "10K" };
    int results[std::size(strs)];
    std::from_chars_result parse_results[std::size(strs)];
        
    for (std::size_t i = 0u; i < std::size(strs); ++i)
    {
        const auto first = strs[i].data();
		const auto last  = strs[i].data() + strs[i].size();
        parse_results[i] = std::from_chars(first, last, results[i]);
    
        std::cout << "Input:  " << strs[i] << std::endl;
        std::cout << "Result: " << results[i] << std::endl;
        std::cout << "Error:  " << static_cast< int >(parse_results[i].ec) << std::endl;
        std::cout << "Ptr:    " << *parse_results[i].ptr << std::endl;
        std::cout << std::endl;
    }
}
