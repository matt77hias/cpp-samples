#include <type_traits>

struct Foo
{
    constexpr Foo() noexcept = default;
};

static_assert(std::is_trivially_default_constructible_v< Foo > == true);

struct Bar
{
    constexpr Bar() noexcept;
};

constexpr Bar::Bar() noexcept = default;

static_assert(std::is_trivially_default_constructible_v< Bar > == false);

auto main()
    -> int
{
    return 0;
}
