// array
#include <array>
// contiguous_range
#include <ranges>
// vector
#include <vector>

static_assert(std::ranges::contiguous_range< std::array< int, 5u > >);
static_assert(std::ranges::contiguous_range< std::vector< int > >);
static_assert(not std::ranges::contiguous_range< std::vector< bool > >);

auto main()
    -> int
{
    return 0;
}
