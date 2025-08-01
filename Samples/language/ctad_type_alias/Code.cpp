// std::size_t
#include <cstddef>
// std::dynamic_extent
// std::span
#include <span>

template< typename T, std::size_t N = std::dynamic_extent >
using Span = std::span< T, N >;

auto main()
	-> int
{
    int array[2u] = {};

    Span span = array;
    
    return span.front();
}
