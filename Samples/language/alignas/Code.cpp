// std::array
#include <array>

using float4 = std::array< float, 4u >;

static_assert(sizeof(float4) == 16u);

struct float4A
{
    alignas(16u) float4 m_data = {};
};

static_assert(sizeof(float4A) == 16u);

struct A
{
    float m_a = {};
    float4 m_b = {};
};

static_assert(sizeof(A) == 20u);

struct B
{
    float4 m_a = {};
    float m_b = {};
};

static_assert(sizeof(B) == 20u);

struct C
{
    float m_a = {};
    float4A m_b = {};
};

static_assert(sizeof(C) == 32u);

struct D
{
    float4A m_a = {};
    float m_b = {};
};

static_assert(sizeof(D) == 32u);

auto main()
	-> int
{
   return 0;
}
