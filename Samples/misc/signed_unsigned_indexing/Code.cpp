// std::signed_integral
#include <concepts>
// std::size_t
#include <cstddef>

struct Vector
{
    constexpr auto operator [](std::size_t index) const
        -> int
    {
        return 3;
    }

    template< std::signed_integral S >
    constexpr auto operator [](S index) const
        -> int
    {
        return 5;
    }
};

auto main()
    -> int
{
    const Vector v;
    
    return v[0];
}
