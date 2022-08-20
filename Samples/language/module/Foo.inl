pragma once

namespace foo
{
	template<>
	[[nodiscard]]
	constexpr auto Struct
		::Test< int >() const
		noexcept -> int
	{
		return 21;
	}
	
	[[nodiscard]]
	constexpr auto Test3()
		noexcept -> int
	{
		return 13;
	}
}
