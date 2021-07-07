// cout, endl
#include <iostream>

class A
{

public:
    
	[[nodiscard]]
    explicit A(int a) noexcept
        : m_a(a)
    {
        std::cout << "A::A()" << std::endl;
    }

    virtual ~A() = default;

    int m_a;
};

class B : public virtual A
{
    
public:
    
	[[nodiscard]]
    explicit B(int a) noexcept
        : A(a)
    {
        std::cout << "B::B()" << std::endl;
    }

    virtual ~B() = default;
};

class C : public virtual A
{

public:
    
	[[nodiscard]]
    explicit C(int a) noexcept
        : A(a)
    {
        std::cout << "C::C()" << std::endl;
    }

    virtual ~C() = default;
};

class D : public C, public B
{

public:
    
	[[nodiscard]]
    D() noexcept
        : A(1), C(3), B(2)
    {
        std::cout << "D::D()" << std::endl;
    }

    virtual ~D() = default;
};

int main()
{
    D d;
    std::cout << d.m_a;

    return 0;
}
