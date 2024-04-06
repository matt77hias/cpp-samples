module;

// Foo
#include "Foo.hpp"

module Widget;

namespace w
{
	[[nodiscard]]
	auto Baz()
		noexcept-> int
	{
		return Foo();
	}
}
