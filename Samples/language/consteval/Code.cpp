[[nodiscard]]
consteval auto Foo()
	noexcept -> int
{
    return 1;
}

auto main()
	-> int
{
   int bar = 2;
   int baz = bar + Foo();

   return baz;
}
