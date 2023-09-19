struct Widget
{
    [[nodiscard]]
    Widget() noexcept
        : m_this(this)
    {}
    
    Widget(const Widget&) = delete;
    
    Widget(Widget&&) = delete;
    
    ~Widget() = default;
    
    auto operator =(const Widget&)
        -> Widget& = delete;

    auto operator =(const Widget&&)
        -> Widget& = delete;

    Widget* m_this;
};

auto Create()
    -> Widget
{
    return Widget{};
}

auto main()
    -> int
{
    Widget w = Create();
    
    return &w == w.m_this;
}
