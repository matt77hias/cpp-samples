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
