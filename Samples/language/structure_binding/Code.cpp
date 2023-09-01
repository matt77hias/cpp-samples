// array
#include <array>
// size_t
#include <cstddef>
// cout, endl
#include <iostream>
// tuple_element, tuple_size 
#include <tuple>
// integral_constant
#include <type_traits>

template< typename T, std::size_t N, std::size_t A = alignof(T) >
struct alignas(A) Array : std::array< T, N >
{};

namespace std
{
	template< typename T, size_t N, size_t A >
	struct tuple_size< Array< T, N, A > >
		: integral_constant< size_t, N >
	{};

	template< size_t I, typename T, size_t N, size_t A >
	struct tuple_element< I, Array< T, N, A > >
	{
		using type = T;
	};
}

auto main()
	-> int
{
    constexpr std::array< int, 3u > a = { 1, 2, 3 };
    constexpr Array< int, 3u > b      = { 4, 5, 6 };
    
    const auto [ax, ay, az] = a;
    std::cout << ax << ay << az << std::endl;
    const auto [bx, by, bz] = b;
    std::cout << bx << by << bz << std::endl;
    
    return 0;
}
