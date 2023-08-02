// Source: https://stackoverflow.com/a/24971386/1731200

// find_if
#include <algorithm>
// size_t
#include <cstddef>
// not1
#include <functional>
// cout, endl
#include <iostream>
// string
#include <string>
// false_type, true_type
#include <type_traits>
// make_pair, pair
#include <utility>

// Sequences

template< bool... > 
struct BoolSequence
{};

template< char... > 
struct CharSequence
{};

// Contains

template< typename T, char Match > 
struct Contains;

template< char C, char... Cs, char Match >
struct Contains< CharSequence< C, Cs... >, Match > 
    : Contains< CharSequence< Cs... >, Match >
{};

template< char C, char... Cs >
struct Contains< CharSequence< C, Cs... >, C > 
    : std::true_type
{};

template< char Match >
struct Contains< CharSequence<>, Match > 
    : std::false_type
{};

// MakeSequence

template< std::size_t Index, typename T, typename Delims > 
struct MakeSequence;

template< std::size_t Index, bool... Bs, typename Delims > 
struct MakeSequence< Index, BoolSequence< Bs... >, Delims > 
    : MakeSequence< Index - 1u, BoolSequence< Contains< Delims, Index - 1u >::value, Bs... >, Delims >
{};

template< bool... Bs, typename Delims > 
struct MakeSequence< 0u, BoolSequence< Bs... >, Delims >
{
	using type = BoolSequence< Bs... >;
};

template< typename T > 
struct BoolASCIITable;

template< bool... Bs > 
struct BoolASCIITable< BoolSequence< Bs... > >
{
    using argument_type = char; 
    
	[[nodiscard]]
	constexpr auto operator ()(const argument_type c) const
		noexcept -> bool
	{
		static constexpr bool table[256u] = { Bs... };
		return table[static_cast< std::size_t >(c)];
	}
};

using Delims = CharSequence< '.', ',' ,' ' ,'-' ,'\n' >;
using Table  = BoolASCIITable< typename MakeSequence< 256u, BoolSequence<>, Delims >::type >;

template< typename I >
[[nodiscard]]
constexpr auto getNextToken(I begin, I end)
	noexcept -> std::pair< I, I >
{
	const auto first  = std::find_if(begin, end, std::not1(Table{}));
	const auto second = std::find_if(first, end, Table{});
	
	return std::make_pair(first,second);
}

auto main()
	-> int
{
	std::string s{"Some people, excluding those present, have been compile time constants - since puberty."};
	
	for (auto it = s.begin(); it != s.end();)
	{
		const auto token = getNextToken(it, s.end());
		std::cout << std::string(token.first, token.second) << std::endl;
		it = token.second;
	}
    
	return 0;
}
