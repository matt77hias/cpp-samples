export module Widget;

// std::array
import <array>;
// std::size_t
import <cstddef>;

export
namespace mage
{
	template< typename T, std::size_t N >
	struct Array : std::array< T, N >
	{};
}
