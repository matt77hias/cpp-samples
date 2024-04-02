export module Widget;

export
namespace mage
{
	struct Foo
	{
		int m_value = {};
	};

	[[nodiscard]]
	constexpr auto operator ==(Foo lhs, Foo rhs)
		noexcept -> bool
	{
		return lhs.m_value == rhs.m_value;
	}

	struct Bar
	{
		[[nodiscard]]
		friend constexpr auto operator ==(Bar lhs, Bar rhs)
			noexcept -> bool = default;
		
		int m_value = {};
	};

	struct Baz
	{
		[[nodiscard]]
		constexpr auto operator ==(const Baz& rhs) const
			noexcept -> bool = default;

		int m_value = {};
	};
}
