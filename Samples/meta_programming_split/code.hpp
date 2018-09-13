// Source: https://stackoverflow.com/a/24971386/1731200

#include <iostream>
#include <type_traits>
#include <utility>
#include <string>
#include <algorithm>
#include <functional>

// Sequences

template< bool... > 
struct BoolSequence {};

template< char... > 
struct CharSequence {};

// Contains

template< typename T, char Match > 
struct Contains;

template< char C, char... Cs, char Match >
struct Contains< CharSequence< C, Cs... >, Match > 
    : public Contains< CharSequence< Cs... >, Match > {};

template< char C, char... Cs >
struct Contains< CharSequence< C, Cs... >, C > 
    : public std::true_type {};

template< char Match >
struct Contains< CharSequence<>, Match > 
    : public std::false_type {};

// MakeSequence

template< size_t Index, typename T, typename Delims > 
struct MakeSequence;

template< size_t Index, bool... Bs, typename Delims > 
struct MakeSequence< Index, BoolSequence< Bs... >, Delims > 
    : public MakeSequence< Index-1, BoolSequence< Contains< Delims, Index-1 >::value, Bs... >, Delims > {};

template< bool... Bs, typename Delims > 
struct MakeSequence< 0, BoolSequence< Bs... >, Delims > {
	using type = BoolSequence< Bs... >;
};

template< typename T > 
struct BoolASCIITable;

template< bool... Bs > 
struct BoolASCIITable< BoolSequence< Bs... > > {
    using argument_type = char; 
    
	constexpr bool operator()(const argument_type c) const noexcept {
		constexpr bool table[256] = { Bs... };
		return table[static_cast< size_t >(c)];
	}
};

using Delims = CharSequence< '.', ',' ,' ' ,'-' ,'\n' >;
using Table  = BoolASCIITable< typename MakeSequence< 256, BoolSequence<>, Delims >::type >;

template< typename T_It >
std::pair< T_It, T_It > getNextToken(T_It begin,T_It end) {
	const auto first  = std::find_if(begin, end, std::not1(Table{}));
	const auto second = std::find_if(first, end, Table{});
	return std::make_pair(first,second);
}

int main() {
	std::string s{"Some people, excluding those present, have been compile time constants - since puberty."};
	for (auto it = std::begin(s); it != std::end(s); ){
		const auto token = getNextToken(it, std::end(s));
		std::cout << std::string(token.first, token.second) << std::endl;
		it = token.second;
	}
    
	return 0;
}
