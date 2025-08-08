// std::ranges::all_of
#include <algorithm>
// std::cout
// std::endl
#include <iostream>
// std::vector
#include <vector>

struct Widget
{
    [[nodiscard]]
    auto IsValid() const
        noexcept -> bool
    {
        std::cout << m_value << std::endl;

        return 0 < m_value;
    }

    int m_value = {};
};

auto main()
    -> int
{
	std::vector< Widget > widgets;
    widgets.push_back({ .m_value = 1 });
    widgets.push_back({ .m_value = 2 });

    [[maybe_unused]] const bool valid = std::ranges::all_of(widgets, &Widget::IsValid);
    
    return 0;
}
