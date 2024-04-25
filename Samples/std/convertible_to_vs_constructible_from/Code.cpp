// constructible_from, convertible_to
#include <concepts>

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

static_assert(std::constructible_from< A, Foo >);
static_assert(std::constructible_from< A, Bar >);
static_assert(not std::convertible_to< Foo, A >);
static_assert(std::convertible_to< Bar, A >);

static_assert(std::constructible_from< Foo, B >);
static_assert(std::constructible_from< Bar, B >);
static_assert(not std::convertible_to< B, Foo >);
static_assert(std::convertible_to< B, Bar >);

static_assert(std::constructible_from< A, B >);
static_assert(std::constructible_from< A, B >);
static_assert(not std::convertible_to< B, A >);
static_assert(not std::convertible_to< B, A >);

auto main()
	noexcept -> int
{
    return 0;
}
