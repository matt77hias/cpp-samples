// cout, endl
#include <iostream>

struct Widget
{
    [[nodiscard]]
	Widget() { std::cout << "Widget::Widget()" << std::endl; };
    Widget(const Widget&) = delete;
    Widget(const Widget&&) = delete;
    ~Widget() { std::cout << "Widget::~Widget()" << std::endl; };
    Widget &operator=(const Widget&) = delete;
    Widget &operator=(const Widget&&) = delete;
};

[[nodiscard]]
Widget make_widget()
{
    std::cout << "f_non_const" << std::endl;
    return Widget();
}

[[nodiscard]]
const Widget make_const_widget()
{
    std::cout << "f_const" << std::endl;
    return Widget();
}

auto main()
    -> int
{
    const Widget w0 = make_widget();
    const Widget w1 = make_const_widget();

    return 0;
}
