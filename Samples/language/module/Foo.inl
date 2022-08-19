#pragma once

namespace foo
{
	[[nodiscard]]
	constexpr auto Test3()
		noexcept -> int
	{
		return 13;
	}
}
