// std::cout
// std::endl
#include <iostream>
// std::source_location
#include <source_location>

struct Diagnostics1
{
    std::source_location m_source_location = {};
};

void f1(Diagnostics1 d = { .m_source_location = std::source_location::current() })
{
    std::cout << d.m_source_location.function_name() << std::endl;
    std::cout << d.m_source_location.line() << std::endl;
}

struct Diagnostics2
{
    std::source_location m_source_location = std::source_location::current();
};

void f2(Diagnostics2 d = {})
{
    std::cout << d.m_source_location.function_name() << std::endl;
    std::cout << d.m_source_location.line() << std::endl;
}

auto main()
    -> int
{
    f1();
    f2();

    return 0;
}
