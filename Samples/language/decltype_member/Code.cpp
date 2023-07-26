// same_as
#include <concepts>

struct Widget
{
    int m_value = {};

	static_assert(std::same_as< decltype(m_value), int >);
};

static_assert(std::same_as< decltype(Widget::m_value), int >);

auto main()
	-> int
{
    return 0;
}
