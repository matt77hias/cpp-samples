export module Foo;

export
namespace w
{
	[[nodiscard]]
	constexpr auto Foo()
		noexcept-> int
	{
		return 3;
	}
}
