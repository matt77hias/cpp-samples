struct Widget
{
    [[nodiscard]]
    constexpr explicit Widget() noexcept = default;
};

int main()
{
	// Widget w = {};
    Widget w = Widget{};
    
    return 0;
}
