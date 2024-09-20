// default_initializable
#include <concepts>

static_assert(std::default_initializable< int >);
static_assert(not std::default_initializable< const int >);

struct Foo
{
    Foo()
    {}
};

static_assert(std::default_initializable< Foo >);
static_assert(std::default_initializable< const Foo >);

auto main()
    -> int
{
    return 0;
}
