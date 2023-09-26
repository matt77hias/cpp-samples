// numeric_limits
#include <limits>
// remove_cv_t
#include <type_traits>

template< typename T >
concept Arithmetic = requires
{
	std::numeric_limits< std::remove_cv_t< T > >{};
};

enum A : int {};
enum class B : int{};

static_assert(Arithmetic< A >);
static_assert(Arithmetic< B >);

auto main()
	-> int
{
	return 0;
}
