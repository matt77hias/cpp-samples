// declval
#include <ranges>
// vector
#include <vector>

auto main()
    -> int
{
    [[maybe_unused]] std::vector< int > v = {};
    [[maybe_unused]] std::ranges::ref_view< std::vector< int > > r(v);
    [[maybe_unused]] std::ranges::ref_view< std::ranges::ref_view< std::vector< int > > > rr(r);
    
    return 0;
}
