// all_of
#include <algorithm>
// cout, endl
#include <iostream>
// vector
#include <vector>

struct Widget
{
    [[nodiscard]]
    bool IsValid() const noexcept
    {
        std::cout << m_value << std::endl;
        
        return 0 < m_value;
    }

    int m_value = {};
};

int main()
{
	std::vector< Widget > widgets;
    widgets.push_back({ .m_value = 1 });
    widgets.push_back({ .m_value = 2 });

    const bool valid = std::ranges::all_of(widgets, &Widget::IsValid);
    
    return 0;
}
