// std::remainder
// std::round
#include <cmath>
// std::cout
// std::endl
#include <iostream>

[[nodiscard]]
auto Mod(float angle)
	noexcept -> float
{
    return angle - 360.0f * std::round(angle / 360.0f);
}

auto main()
	-> int
{
    std::cout << Mod(-181.0f) << std::endl;
    std::cout << Mod(-180.0f) << std::endl;
    std::cout << Mod( 180.0f) << std::endl;
    std::cout << Mod( 181.0f) << std::endl;

    std::cout << std::endl;

    std::cout << std::remainder(-181.0f, 360.0f) << std::endl;
    std::cout << std::remainder(-180.0f, 360.0f) << std::endl;
    std::cout << std::remainder( 180.0f, 360.0f) << std::endl;
    std::cout << std::remainder( 181.0f, 360.0f) << std::endl;
	
    return 0;
}
