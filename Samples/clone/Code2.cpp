// cout, endl
#include <iostream>
// shared_ptr
#include <memory>

struct Base
{
    virtual ~Base() = default;
    
	[[nodiscard]]
    std::shared_ptr< Base > Clone() const
    {
        std::cout << "Base::Clone" << std::endl;
        return CloneImplementation();
    }

private:

	[[nodiscard]]
    virtual std::shared_ptr< Base > CloneImplementation() const
    {
        std::cout << "Base::CloneImplementation" << std::endl;
        return std::shared_ptr< Base >(new Base(*this));
    }
};

struct Derived : public Base
{
	[[nodiscard]]
    std::shared_ptr< Derived > Clone() const
    {
        std::cout << "Derived::Clone" << std::endl;
        return std::static_pointer_cast< Derived >(CloneImplementation());
    }

private:

	[[nodiscard]]
    virtual std::shared_ptr< Base > CloneImplementation() const override
    {
        std::cout << "Derived::CloneImplementation" << std::endl;
        return std::shared_ptr< Derived >(new Derived(*this));
    }
};

int main()
{
    Base* b = new Derived;
    std::shared_ptr< Base > clone = b->Clone();
    delete b;

    return 0;
}
