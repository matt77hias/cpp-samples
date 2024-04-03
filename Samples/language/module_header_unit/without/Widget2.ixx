module;

// size_t
#include <cstddef>

export module Widget2;

import Widget;

export
namespace mage
{
	template< typename T, std::size_t N >
	using ArrayAlias = Array< T, N >;
}
