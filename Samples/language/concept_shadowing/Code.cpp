// std::integral
#include <concepts>

template< typename T >
concept Scalar = true;

template< typename T >
struct Vector
{
    using Scalar = T;

    constexpr auto operator +=(const Scalar& rhs)
        noexcept -> Vector
        requires(std::integral< Scalar >);
};

template< typename T >
constexpr auto Vector< T >
    ::operator +=(const Scalar& rhs)
    noexcept -> Vector
    requires(std::integral< Scalar >)
{
    return *this;
}

auto main()
    -> int
{
    return 0;
}
