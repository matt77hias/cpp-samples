// std::string
#include <string>
// std::cout
// std::endl
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

auto Create()
    -> std::string
{
    return "string";
}

auto main()
    -> int
{
    [[maybe_unused]] Widget w(Create());
    return 0;
}
