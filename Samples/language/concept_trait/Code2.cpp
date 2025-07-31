// std::ranges::random_access_range
#include <ranges>

template< std::ranges::random_access_range T >
inline constexpr bool IsVector = false;

template< typename T >
concept Vector = IsVector< T >;

//static_assert(not IsVector< int >);
static_assert(not Vector< int >);

auto main()
    -> int
{
    return 0;
}
