// std::cout
// std::endl
#include <iostream>

struct Base
{
    virtual ~Base() = default;
    
	[[nodiscard]]
    virtual auto Clone() const
		-> Base*
    {
        std::cout << "Base::Clone" << std::endl;
        return new Base(*this);
    }
};

struct Derived : public Base
{
	[[nodiscard]]
	auto Clone() const
		-> Derived* override
    {
        std::cout << "Derived::Clone" << std::endl;
        return new Derived(*this);
    }
};

auto main()
	-> int
{
    Base* b = new Derived;
    Base* clone = b->Clone();
    delete b;
	delete clone;

    return 0;
}
