// cout, endl
#include <iostream>

using uint = unsigned int;

[[nodiscard]]
constexpr auto getX(uint i)
	noexcept -> float
{
    return ((i & 2u) << 1u) - 1.0f;
}

[[nodiscard]]
constexpr auto getY(uint i)
	noexcept -> float
{
    return ((i & 1u) << 2u) - 1.0f;
}

auto main()
   -> int
{
    for (uint i = 0u; i < 3u; ++i)
    {
        std::cout << getX(i) << "," << getY(i) << std::endl;
    }

	return 0;
}
