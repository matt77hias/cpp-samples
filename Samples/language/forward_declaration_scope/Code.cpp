// same_as
#include <concepts>

template< typename T >
struct Foo
{};

template< typename T >
struct Outer
{
    using Inner = Foo< struct Bar >;
};

static_assert(std::same_as< Outer< int >::Inner, Outer< float >::Inner >);

auto main()
    -> int
{
	return 0;
}
