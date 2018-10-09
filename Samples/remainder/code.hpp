#include <cmath>
#include <iostream>

float Mod(float angle) noexcept {
    return angle - 360.0f * round(angle / 360.0f);
}

int main() {
    std::cout << Mod(-181.0f) << std::endl;
    std::cout << Mod(-180.0f) << std::endl;
    std::cout << Mod( 180.0f) << std::endl;
    std::cout << Mod( 181.0f) << std::endl;

    std::cout << std::remainder(-181.0f, 360.0f) << std::endl;
    std::cout << std::remainder(-180.0f, 360.0f) << std::endl;
    std::cout << std::remainder( 180.0f, 360.0f) << std::endl;
    std::cout << std::remainder( 181.0f, 360.0f) << std::endl;
	
    return 0;
}
