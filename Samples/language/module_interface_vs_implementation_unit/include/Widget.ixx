module;

// Foo
#include "Foo.hpp"

export module Widget;

export
namespace w
{
	[[nodiscard]]
	constexpr auto Bar()
		noexcept-> int
	{
		return Foo();
	}

	[[nodiscard]]
	auto Baz()
		noexcept-> int;
}
