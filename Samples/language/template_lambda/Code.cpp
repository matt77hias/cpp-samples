// integral
#include <concepts>

void f()
{
    constexpr auto test = []< typename T >() consteval
        noexcept -> bool
    {
        return std::integral< T >;
    };

    static_assert(test.operator()< int >());
    static_assert(test.operator()< const int >());
}

auto main()
    -> int
{
    return 0;
}
