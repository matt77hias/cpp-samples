// std::is_constructible_v
// std::is_convertible_v
#include <type_traits>

struct Foo
{};

struct Bar
{
    [[nodiscard]]
    constexpr operator Foo()
        noexcept
    {
        return {};
    }
};

static_assert(std::is_constructible_v< Foo, Bar >);
static_assert(std::is_convertible_v< Bar, Foo >);

auto main()
   -> int
{
    return 0;
}
