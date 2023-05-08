// derived_from
#include <concepts>

struct A
{};

struct B : private A
{
    friend struct C;
};

struct C
{
    static_assert(not std::derived_from< B, A >);
};

auto main()
	-> int
{
    return 0;
}
