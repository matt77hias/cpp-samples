// initializer_list
#include <initializer_list>
// cout, endl
#include <iostream>

struct Widget
{
    int m_value = {};
};

struct Container
{

public:

    void test()
    {
        push_back({ .m_value = 5 });
        push_back({});
    }

    void push_back(const Widget&)
    {
        std::cout << "push_back(const Widget&)" << std::endl;
    }

    void push_back(const Widget&&)
    {
        std::cout << "push_back(Widget&&)" << std::endl;
    }

private:

    //void push_back(std::initializer_list< int >)
    //{
    //    std::cout << "push_back(std::initializer_list< int >)" << std::endl;
    //}
};

void test()
{
    Container c;
    c.test();
    c.push_back({ .m_value = 5 });
    c.push_back({});
}

auto main()
    -> int
{
    test();
    
    return 0;
}
