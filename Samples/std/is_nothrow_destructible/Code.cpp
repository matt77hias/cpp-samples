// cout, endl
#include <iostream>
// is_nothrow_destructible_v
#include <type_traits>
// declval
#include <utility>

int FuncA()
{
    return 1;
}

int FuncB() noexcept
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

auto main() -> int
{
    std::cout << std::is_nothrow_destructible_v< A > << std::endl;
    std::cout << std::is_nothrow_destructible_v< B > << std::endl;
    std::cout << std::is_nothrow_destructible_v< C > << std::endl;
    std::cout << std::is_nothrow_destructible_v< D > << std::endl;
    return 0;
}
