export module Widget;

// array
import <array>;
// size_t
import <cstddef>;

export
namespace mage
{
	template< typename T, std::size_t N >
	struct Array : std::array< T, N >
	{};
}
