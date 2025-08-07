// std::cout
// std::endl
#include <iostream>

struct Widget
{
    [[nodiscard]]
	Widget()
	{
		std::cout << "Widget::Widget()" << std::endl;
	};

    Widget(const Widget&) = delete;

    Widget(const Widget&&) = delete;

    ~Widget()
    {
		std::cout << "Widget::~Widget()" << std::endl;
	};

    auto operator =(const Widget&)
        -> Widget& = delete;

    auto operator =(const Widget&&)
        -> Widget& = delete;
};

[[nodiscard]]
auto make_widget()
    -> Widget
{
    std::cout << "make_widget" << std::endl;
    return {};
}

[[nodiscard]]
auto make_const_widget()
    -> const Widget
{
    std::cout << "make_const_widget" << std::endl;
    return {};
}

auto main()
    -> int
{
    [[maybe_unused]] const Widget w0 = make_widget();
    [[maybe_unused]] const Widget w1 = make_const_widget();

    return 0;
}
