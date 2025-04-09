module;

#define TEST_VALUE 7

export module Baz;
import Bar;

export
namespace test
{
	auto g() -> int
	{
		return f< int >();
	}
}
