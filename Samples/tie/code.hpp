#include <iostream>
#include <tuple>

int main() {
    int a = 1;
    int b = 2;
    
    auto [ra, rb] = std::tie(a, b);
    //auto&  [ra, rb] = std::tie(a, b); // error
    //auto&& [ra, rb] = std::tie(a, b);
    
    ra = 3;
    rb = 4;
    
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    
    return 0;
}
