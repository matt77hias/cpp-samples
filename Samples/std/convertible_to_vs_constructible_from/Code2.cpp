// std::is_constructible_v
// std::is_convertible_v
#include <type_traits>

struct Foo
{};
struct Bar
{};

struct A
{
    explicit A(Foo)
    {}
    A(Bar)
    {}
};

struct B
{
    explicit operator Foo() const
    {
        return {};
    }
    operator Bar() const
    {
        return {};
    }
};

static_assert(std::is_constructible_v< A, Foo >);
static_assert(std::is_constructible_v< A, Bar >);
static_assert(not std::is_convertible_v< Foo, A >);
static_assert(std::is_convertible_v< Bar, A >);

static_assert(std::is_constructible_v< Foo, B >);
static_assert(std::is_constructible_v< Bar, B >);
static_assert(not std::is_convertible_v< B, Foo >);
static_assert(std::is_convertible_v< B, Bar >);

static_assert(std::is_constructible_v< A, B >);
static_assert(std::is_constructible_v< A, B >);
static_assert(not std::is_convertible_v< B, A >);
static_assert(not std::is_convertible_v< B, A >);

auto main()
	noexcept -> int
{
    return 0;
}
