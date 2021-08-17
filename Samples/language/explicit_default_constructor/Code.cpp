struct Widget
{
    [[nodiscard]]
    constexpr explicit Widget() noexcept = default;
};

int main()
{
	// [[maybe_unused]] Widget w = {};
    [[maybe_unused]] Widget w = Widget{};
    
    return 0;
}
