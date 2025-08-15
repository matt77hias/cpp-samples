// std::copy_constructible
#include <concepts>
// std::nullptr_t
#include <cstddef>

static_assert(std::copy_constructible< std::nullptr_t >);

auto main()
	-> int
{
	return 0;
}
