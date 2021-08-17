struct Widget
{
    [[nodiscard]]
    Widget() noexcept
        : m_this(this)
    {}
    
    Widget(const Widget&) = delete;
    
    Widget(Widget&&) = delete;
    
    ~Widget() = default;
    
    Widget& operator=(const Widget&) = delete;
    
    Widget& operator=(Widget&&) = delete;

    Widget* m_this;
};

Widget Create()
{
    return Widget{};
}

int main()
{
    Widget w = Create();
    
    return &w == w.m_this;
}
