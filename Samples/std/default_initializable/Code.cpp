// default_initializable
#include <concepts>
// is_default_constructible_v
#include <type_traits>

static_assert(std::default_initializable< int >);
static_assert(not std::default_initializable< const int >);

static_assert(std::is_default_constructible_v< int >);
static_assert(std::is_default_constructible_v< const int >);

struct Foo
{
    Foo()
    {}
};

static_assert(std::default_initializable< Foo >);
static_assert(std::default_initializable< const Foo >);

static_assert(std::is_default_constructible_v< Foo >);
static_assert(std::is_default_constructible_v< const Foo >);

auto main()
    -> int
{
    return 0;
}
