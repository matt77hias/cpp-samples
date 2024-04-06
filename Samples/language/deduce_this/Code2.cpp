struct Widget
{
    template< int N, typename SelfT = Widget >
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
