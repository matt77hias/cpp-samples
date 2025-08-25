// std::convertible_to
#include <concepts>
// std::is_arithmetic_v
// std::is_integral_v
// std::is_fundamental_v
#include <type_traits>

static_assert(std::is_arithmetic_v< int >);
static_assert(std::is_integral_v< int >);
static_assert(std::is_fundamental_v< int >);

enum UnscopedEnum : int
{};

static_assert(not std::is_arithmetic_v< UnscopedEnum >);
static_assert(not std::is_integral_v< UnscopedEnum >);
static_assert(not std::is_fundamental_v< UnscopedEnum >);

static_assert(std::convertible_to< UnscopedEnum, int >);

auto main()
    -> int
{
    return 0;
}
