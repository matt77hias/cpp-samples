// cout, endl
#include <iostream>

struct Base
{
    virtual ~Base() = default;
    
	[[nodiscard]]
    virtual Base* Clone() const
    {
        std::cout << "Base::Clone" << std::endl;
        return new Base(*this);
    }
};

struct Derived : public Base
{
	[[nodiscard]]
	virtual Derived* Clone() const override
    {
        std::cout << "Derived::Clone" << std::endl;
        return new Derived(*this);
    }
};

int main()
{
    Base* b = new Derived;
    Base* clone = b->Clone();
    delete b;
	delete clone;

    return 0;
}
