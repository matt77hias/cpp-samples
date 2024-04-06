export module Widget;

// Foo
import Foo;

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
