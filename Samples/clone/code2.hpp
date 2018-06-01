#include <iostream>
#include <memory>

struct Base {

    virtual ~Base() = default;
    
    std::shared_ptr< Base > Clone() const {
        std::cout << "Base::Clone\n";
        return CloneImplementation();
    }

private:

    virtual std::shared_ptr< Base > CloneImplementation() const {
        std::cout << "Base::CloneImplementation\n";
        return std::shared_ptr< Base >(new Base(*this));
    }
};
struct Derived : public Base {

    std::shared_ptr< Derived > Clone() const {
        std::cout << "Derived::Clone\n";
        return std::static_pointer_cast< Derived >(CloneImplementation());
    }

private:

    virtual std::shared_ptr< Base > CloneImplementation() const override {
        std::cout << "Derived::CloneImplementation\n";
        return std::shared_ptr< Derived >(new Derived(*this));
    }
};

int main() {
    Base *b = new Derived;
    b->Clone();
    return 0;
}
