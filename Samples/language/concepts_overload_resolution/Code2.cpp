// integral
#include <concepts>

template< std::floating_point T >
auto f(T x)
    noexcept -> int
{
    return 1;
}
template< std::floating_point T >
auto f(T x)
    noexcept -> int
    requires(std::same_as< float, T >)
{
    return 2;
}

auto main()
    -> int
{
    return f(1.0f);
}
