template< bool... Bs >
struct Pack
{
    // X and true == X
    static_assert((Bs && ...) == true);
    static_assert((... && Bs) == true);

    // X or false == X
    static_assert((Bs || ...) == false);
    static_assert((... || Bs) == false);
};

auto main()
	-> int
{
    [[maybe_unused]] Pack<> p;

    return 0;
}
