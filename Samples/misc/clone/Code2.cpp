// cout, endl
#include <iostream>
// shared_ptr, static_pointer_cast
#include <memory>

struct Base
{
    virtual ~Base() = default;
    
	[[nodiscard]]
    auto Clone() const
		-> std::shared_ptr< Base >
    {
        std::cout << "Base::Clone" << std::endl;
        return CloneImplementation();
    }

private:

	[[nodiscard]]
    virtual auto CloneImplementation() const
		-> std::shared_ptr< Base >
    {
        std::cout << "Base::CloneImplementation" << std::endl;
        return std::shared_ptr< Base >(new Base(*this));
    }
};

struct Derived : public Base
{
	[[nodiscard]]
    auto Clone() const
		-> std::shared_ptr< Derived >
    {
        std::cout << "Derived::Clone" << std::endl;
        return std::static_pointer_cast< Derived >(CloneImplementation());
    }

private:

	[[nodiscard]]
    auto CloneImplementation() const
		-> std::shared_ptr< Base > override
    {
        std::cout << "Derived::CloneImplementation" << std::endl;
        return std::shared_ptr< Derived >(new Derived(*this));
    }
};

auto main()
	-> int
{
    Base* b = new Derived;
    [[maybe_unused]] std::shared_ptr< Base > clone = b->Clone();
    delete b;

    return 0;
}
