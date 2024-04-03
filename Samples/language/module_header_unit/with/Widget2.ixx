export module Widget2;

import Widget;

// size_t
import <cstddef>;

export
namespace mage
{
	template< typename T, std::size_t N >
	using ArrayAlias = Array< T, N >;
}
