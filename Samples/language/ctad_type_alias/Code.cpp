// size_t
#include <cstddef>
// dynamic_extent, span
#include <span>

template< typename T, std::size_t N = std::dynamic_extent >
using Span = std::span< T, N >;

auto main() -> int
{
    int array[2u] = {};

    [[maybe_unused]] Span span = array;
    
    return 0;
}
