// std::cout
// std::endl
#include <iostream>
// std::is_nothrow_destructible_v
#include <type_traits>
// std::declval
#include <utility>

auto FuncA()
    -> int
{
    return 1;
}

auto FuncB()
    noexcept -> int
{
    return 1;
}

struct A
{
    ~A()
    {
        FuncA();
    }
};

struct B
{
    ~B()
    {
        FuncB();
    }
};

struct C
{
    ~C()
    {
        throw 10;
    }
};

struct D
{
    ~D() noexcept(false)
    {}
};

auto main()
    -> int
{
    std::cout << std::is_nothrow_destructible_v< A > << std::endl;
    std::cout << std::is_nothrow_destructible_v< B > << std::endl;
    std::cout << std::is_nothrow_destructible_v< C > << std::endl;
    std::cout << std::is_nothrow_destructible_v< D > << std::endl;

    return 0;
}
