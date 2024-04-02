import Widget2;

auto main()
	noexcept -> int
{
	using namespace mage;

	FooType lhs_foo;
	FooType rhs_foo;

	BarType lhs_bar;
	BarType rhs_bar;

	BazType lhs_baz;
	BazType rhs_baz;
	
	return (lhs_foo == rhs_foo)
		and (lhs_bar == rhs_bar)
		and (lhs_baz == rhs_baz);
}
