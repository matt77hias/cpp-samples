// std::cout
// std::endl
#include <iostream>

struct Base
{
    virtual ~Base() = default;
};

struct Derived : private Base
{
    auto GetBase()
        -> Base*
    {
        return this;
    }
    
    static void test()
    {
        Derived d;
        Base* base = d.GetBase();

        if (dynamic_cast< Derived* >(base))
        {
            std::cout << "It worked (we must be using public inheritance)." << std::endl;
        }
        else
        {
            std::cout << "It failed (we must be using protected/private inheritance)." << std::endl;
        }
    }
};

auto main()
    -> int
{
    Derived::test();
    return 0;
}
