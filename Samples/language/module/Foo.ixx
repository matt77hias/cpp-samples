export module Foo;

import Bar;

export namespace foo
{
	static_assert(sizeof(float) == 4u);
	
	template< typename T >
	constexpr int g_value = 3;
	
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

	struct Struct
	{
		template< typename T >
		[[nodiscard]]
		constexpr auto Test() const
			noexcept -> int;
	};
}

namespace foo
{
	template<>
	constexpr int g_value< int > = 5;
	
	[[nodiscard]]
	constexpr auto Test3()
		noexcept -> int;
}

#include "Foo.inl"
