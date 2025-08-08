module;

// std::array
#include <array>
// std::size_t
#include <cstddef>

export module Widget;

export
namespace mage
{
	template< typename T, std::size_t N >
	struct Array : std::array< T, N >
	{};
}
