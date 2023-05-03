// array
#include <array>
// contiguous_range
#include <ranges>
// vector
#include <vector>

static_assert(std::ranges::contiguous_range< std::array< int, 5u > >);
static_assert(std::ranges::contiguous_range< std::vector< int > >);
static_assert(std::ranges::contiguous_range< std::vector< bool > > == false);

auto main() -> int
{
    return 0;
}
