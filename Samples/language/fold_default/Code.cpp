template< bool... Bs >
struct Pack
{
    // X and true == X
    static_assert((Bs and ...) == true);
    static_assert((... and Bs) == true);

    // X or false == X
    static_assert((Bs or ...) == false);
    static_assert((... or Bs) == false);
};

auto main()
	-> int
{
    [[maybe_unused]] Pack<> p;

    return 0;
}
