// array
#include <array>
// cout, endl
#include <iostream>

using float4 = std::array< float, 4u >;

static_assert(sizeof(float4) == 16u);

struct float4A
{
    alignas(16u) float4 m_data = {};
};

static_assert(sizeof(float4A) == 16u);

struct A
{
    A() { std::cout << "A::A()" << std::endl; };
    
    float m_a = {};
    float4 m_b = {};
};

static_assert(sizeof(A) == 20u);

struct B
{
    B() { std::cout << "B::B()" << std::endl; };
    
    float4 m_a = {};
    float m_b = {};
};

static_assert(sizeof(B) == 20u);

struct C
{
    C() { std::cout << "C::C()" << std::endl; };
    
    float m_a = {};
    float4A m_b = {};
};

static_assert(sizeof(C) == 32u);

struct D
{
    D() { std::cout << "D::D()" << std::endl; };
    
    float4A m_a = {};
    float m_b = {};
};

static_assert(sizeof(D) == 32u);

int main()
{
   [[maybe_unused]] A a;
   [[maybe_unused]] B b;
   [[maybe_unused]] C c;
   [[maybe_unused]] D d;
   return 0;
}
