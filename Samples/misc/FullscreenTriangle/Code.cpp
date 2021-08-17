// cout, endl
#include <iostream>

using uint = unsigned int;

[[nodiscard]]
constexpr float getX(uint i) noexcept
{
    return ((i & 2u) << 1u) - 1.0f;
}

[[nodiscard]]
constexpr float getY(uint i) noexcept
{
    return ((i & 1u) << 2u) - 1.0f;
}

int main()
{
    for (uint i = 0u; i < 3u; ++i)
    {
        std::cout << getX(i) << "," << getY(i) << std::endl;
    }
}
