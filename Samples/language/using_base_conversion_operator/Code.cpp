struct Base
{
    [[nodiscard]]
	explicit operator int () const
		noexcept
	{
		return 7;
	}
};

struct Derived : Base
{
    using Base::operator int;
};

auto main()
    -> int
{
    return static_cast< int >(Derived{});
}
