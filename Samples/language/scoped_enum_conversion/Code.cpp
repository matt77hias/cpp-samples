// constructible_from, convertible_to
#include <concepts>

enum class A {};

auto main()
    -> int
{
    A a = {};
    static_assert(not std::constructible_from< int, A >);
    static_assert(not std::convertible_to< A, int >);

    return static_cast< int >(a);
}
