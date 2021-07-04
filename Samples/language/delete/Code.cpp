// string
#include <string>
// cout, endl
#include <iostream>

struct Widget
{
    [[nodiscard]]
	Widget(const std::string&)
    {
        std::cout << "Widget(const std::string&)" << std::endl;
    }

    Widget(const std::string&&) = delete;
    //{
    //    std::cout << "Widget(const std::string&&)" << std::endl;
    //}
};

std::string Create()
{
    return "string";
}

int main()
{
    [[maybe_unused]] Widget w(Create());
    return 0;
}
