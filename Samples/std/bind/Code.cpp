// std::ranges::for_each
#include <algorithm>
// std::bind
// std::placeholders::_1
#include <functional>
// std::cout
// std::endl
#include <iostream>
// std::vector
#include <vector>

struct Widget
{
    void Print(int value) const
		noexcept
    {
        std::cout << value << std::endl;
    }
};

auto main()
	-> int
{
	std::vector< int > values = { 1, 2 };

    Widget w;
    std::ranges::for_each(values, std::bind(&Widget::Print, &w, std::placeholders::_1));
    
    return 0;
}
