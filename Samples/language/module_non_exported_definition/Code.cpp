import Widget;

auto main()
	noexcept -> int
{
	using namespace mage;
	
	return A() + B< void >() + C() + D< void >() + E() + F< void >();
}
