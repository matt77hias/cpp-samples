// std::array
#include <array>
// std::size_t
#include <cstddef>

template< typename T, std::size_t N  >
struct Vector
{
    Vector(const std::array< T, N >&)
    {}
};

auto main()
    -> int
{
    [[maybe_unused]] Vector v1 = std::array{ 1, 2, 3 };
    [[maybe_unused]] Vector< int, 3u > v2 = { { 1, 2, 3 } };

    return 0;
}
