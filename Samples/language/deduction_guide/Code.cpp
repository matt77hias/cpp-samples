template< typename T >
struct A
{
    template< typename SrcT >
    A(int, const SrcT&)
    {}
};

template< typename SrcT >
A(int, const SrcT&) -> A< SrcT >;

auto main()
    -> int
{
    [[maybe_unused]] constexpr unsigned int u = 1u;
    [[maybe_unused]] A a(u, u);
    
    return 0;
}
