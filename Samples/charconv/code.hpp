#include <iostream>
#include <charconv>
 
int main() {
    const char* const strs[] = { "K", "10", "10K" };
    int results[std::size(strs)];
    std::from_chars_result parse_results[std::size(strs)];
        
    for (size_t i = 0; i < std::size(strs); ++i) {
        parse_results[i] = std::from_chars(strs[i], nullptr, results[i]);
    }
    
    for (size_t i = 0; i < std::size(strs); ++i) {
        std::cout << results[i] << std::endl;
    }
                               
    std::cout << std::endl;
                               
    for (size_t i = 0; i < std::size(strs); ++i) {
        std::cout << static_cast< size_t >(parse_results[i].ec) << std::endl;
    }
    
    std::cout << std::endl;
    
    for (size_t i = 0; i < std::size(strs); ++i) {
        std::cout << *parse_results[i].ptr << std::endl;
    }
}
