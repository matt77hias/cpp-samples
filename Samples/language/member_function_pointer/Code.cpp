// all_of
#include <algorithm>
// cout, endl
#include <iostream>
// vector
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

    const bool valid = std::ranges::all_of(widgets, &Widget::IsValid);
    
    return 0;
}
