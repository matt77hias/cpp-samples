// for_each
#include <algorithm>
// _1, bind
#include <functional>
// cout, endl
#include <iostream>
// vector
#include <vector>

struct Widget
{
    void Print(int value) const
		noexcept
    {
        std::cout << value << std::endl;
    }
};

quto main()
	-> int
{
	std::vector< int > values = { 1, 2 };

    Widget w;
    std::ranges::for_each(values, std::bind(&Widget::Print, &w, std::placeholders::_1));
    
    return 0;
}
