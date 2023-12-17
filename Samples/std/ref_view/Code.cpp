// declval
#include <ranges>
// vector
#include <vector>

auto main()
    -> int
{
    std::vector< int > v = {};
    std::ranges::ref_view< std::vector< int > > r(v);
    std::ranges::ref_view< std::ranges::ref_view< std::vector< int > > > rr(r);
    
    return 0;
}
