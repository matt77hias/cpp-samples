export module Foo;

import Bar;

export namespace foo
{
	[[nodiscard]]
	constexpr auto Test1()
		noexcept -> int
	{
		return 7;
	}

	[[nodiscard]]
	inline auto Test2()
		noexcept -> int
	{
		return bar::Test();
	}
}

// Not exported
namespace foo
{
	[[nodiscard]]
	constexpr auto Test3()
		noexcept -> int;
}

#include "Foo.inl"
