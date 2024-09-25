// is_arithmetic_v, is_integral_v, is_fundamental_v
#include <type_traits>

enum UnscopedEnum
{};

static_assert(not std::is_arithmetic_v< UnscopedEnum >);
static_assert(not std::is_integral_v< UnscopedEnum >);
static_assert(not std::is_fundamental_v< UnscopedEnum >);

auto main()
    -> int
{
    return 0;
}
