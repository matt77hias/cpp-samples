struct Widget
{
    [[nodiscard]]
    constexpr explicit Widget()
        noexcept = default;
};

auto main()
   -> int
{
	// [[maybe_unused]] Widget w = {};
    [[maybe_unused]] Widget w = Widget{};
    
    return 0;
}
