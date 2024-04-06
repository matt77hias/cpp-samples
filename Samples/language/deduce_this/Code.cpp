struct Widget
{
    template< int N, typename SelfT >
    constexpr auto f(this SelfT&& self)
        -> int
    {
        return N;
    }
};

auto main()
    -> int
{
    Widget w;
    
    return w.f< 5 >();
}
