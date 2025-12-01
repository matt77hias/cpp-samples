// std::size_t
#include <cstddef>
// std::forward
#include <utility>

template< typename T >
constexpr auto bar(const T*) -> int
{
    return 3;
}

template< typename T, std::size_t N >
constexpr auto bar(const T(&)[N]) -> int
{
    return 7;
}

template< typename T >
constexpr auto foo(T&& x) -> decltype(auto)
{
    return bar(std::forward< T >(x));
}

auto main() -> int
{
    int array[] = { 0, 0, 0 };
    return foo(array);
}
