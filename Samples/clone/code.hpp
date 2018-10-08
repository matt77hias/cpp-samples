#include <iostream>

struct Base {
    virtual ~Base() = default;
    
    virtual Base* Clone() const {
        std::cout << "Base::Clone\n";
        return new Base(*this);
    }
};

struct Derived : public Base {
    virtual Derived* Clone() const override {
        std::cout << "Derived::Clone\n";
        return new Derived(*this);
    }
};

int main() {
    Base* b = new Derived;
    b->Clone();
	delete b;
    return 0;
}
