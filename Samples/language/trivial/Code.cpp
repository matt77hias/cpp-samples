// std::is_trivially_default_constructible_v
#include <type_traits>

struct Foo
{
    [[nodiscard]]
    constexpr Foo()
        noexcept = default;
};

static_assert(std::is_trivially_default_constructible_v< Foo > == true);

struct Bar
{
    [[nodiscard]]
    constexpr Bar()
        noexcept;
};

[[nodiscard]]
constexpr Bar::Bar()
    noexcept = default;

static_assert(std::is_trivially_default_constructible_v< Bar > == false);

auto main()
    -> int
{
    return 0;
}
