// is_base_of_v
#include <type_traits>

struct A
{};
struct B : private A
{};
struct C : private B
{};

static_assert(std::is_base_of_v< A, C >);

struct D : public B
{};

static_assert(std::is_base_of_v< A, D >);

auto main() -> int
{
    return 0;
}
