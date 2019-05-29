#include <iostream>
#include <limits>

int main() {
    std::cout << std::numeric_limits< float >::epsilon() << std::endl;
    std::cout << std::numeric_limits< int >::epsilon()   << std::endl;
    return 0;
}
