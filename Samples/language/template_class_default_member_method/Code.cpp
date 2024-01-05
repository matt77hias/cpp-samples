struct Foo
{
    [[nodiscard]]
    Foo() = default;

    Foo(const Foo&) = delete;
};

template< typename T >
struct Bar : Foo
{
    [[nodiscard]]
    Bar() = default;
    
    [[nodiscard]]
    Bar(const Bar&) = default;

    T m_value;
};

auto main()
    -> int
{
    [[maybe_unused]] Bar< Foo > a;
    
    return 0;
}
