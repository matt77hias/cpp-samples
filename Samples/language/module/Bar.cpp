module Bar;

import Foo;

namespace bar
{
	[[nodiscard]]
	auto Test()
		noexcept -> int
	{
		return foo::Test1();
	}
}
