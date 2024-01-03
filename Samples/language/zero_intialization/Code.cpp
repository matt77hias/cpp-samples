struct A
{
    [[nodiscard]]
    constexpr auto get() const
        noexcept -> int
    { 
        return m_a;
    }
    
    int m_a = 5;
};

struct B
{

public:

    constexpr B()
        : m_b(7)
    {}

    [[nodiscard]]
    constexpr auto get() const
        noexcept -> int
    { 
        return m_b;
    }
    
private:

    int m_b;
};

struct C
{
    A m_a;
    B m_b;
};

auto main()
    -> int
{
    constexpr C default_init;
    constexpr C zero_init{};

    static_assert(default_init.m_a.get() + default_init.m_b.get() == 12);
    static_assert(zero_init.m_a.get()    + zero_init.m_b.get()    == 12);

    return 0;
}
