export module Widget;

export
namespace mage
{
	consteval auto A()
		-> int;

	template< typename T >
	consteval auto B()
		-> int;

	constexpr auto C()
		-> int;

	template< typename T >
	constexpr auto D()
		-> int;

	inline auto E()
		-> int;

	template< typename T >
	inline auto F()
		-> int;
}

namespace mage
{
	consteval auto A()
		-> int
	{
		return 1;
	}

	template< typename T >
	consteval auto B()
		-> int
	{
		return 2;
	}

	constexpr auto C()
		-> int
	{
		return 3;
	}

	template< typename T >
	constexpr auto D()
		-> int
	{
		return 4;
	}

	inline auto E()
		-> int
	{
		return 5;
	}

	template< typename T >
	inline auto F()
		-> int
	{
		return 6;
	}
}
