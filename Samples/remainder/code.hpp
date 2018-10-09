#include <cmath>
#include <iostream>

int main() {
    std::cout << std::remainder(-181.0f, 360.0f) << std::endl;
    std::cout << std::remainder(-180.0f, 360.0f) << std::endl;
    std::cout << std::remainder( 180.0f, 360.0f) << std::endl;
    std::cout << std::remainder( 181.0f, 360.0f) << std::endl;
    return 0;
}
