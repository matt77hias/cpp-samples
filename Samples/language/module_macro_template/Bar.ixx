module;

#define TEST_VALUE 3

export module Bar;

export
namespace test
{
	template< typename T >
	auto f() -> int
	{
		return TEST_VALUE;
	}
}
