// same_as
#include <concepts>

struct Widget
{
    int m_value;
};

static_assert(std::same_as< decltype(Widget::m_value), int >);

int main()
{
    return 0;
}
