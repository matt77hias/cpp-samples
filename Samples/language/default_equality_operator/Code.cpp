// strong_ordering
#include <compare>

struct Widget
{
    [[nodiscard]]
    constexpr auto operator <=>(const Widget& rhs) const
        noexcept -> std::strong_ordering = default;

    int m_value = {};
};

auto main()
    -> int
{
    static_assert(Widget{} == Widget{});
    
    return 0;
}
