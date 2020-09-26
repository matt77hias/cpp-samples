// strong_ordering
#include <compare>

struct Widget
{
    [[nodiscard]]
    constexpr std::strong_ordering
        operator<=>(const Widget& rhs) const noexcept = default;

    int m_value = {};
};

int main()
{
    static_assert(Widget{} == Widget{});
    
    return 0;
}
