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

int main()
{
    Bar< Foo > a;
    
    return 0;
}
