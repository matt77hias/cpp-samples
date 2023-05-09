// uint16_t, uint8_t
#include <cstdint>
// has_unique_object_representations_v
#include <type_traits>

struct A
{
    std::uint8_t m_first = {};
};

static_assert(sizeof(A) == 1u);
static_assert(std::has_unique_object_representations_v< A >);

struct B
{
    std::uint8_t m_first = {};
    std::uint16_t m_second = {};
};

static_assert(sizeof(B) == 4u);
static_assert(not std::has_unique_object_representations_v< B >);

struct C
{
    B m_b = {};
};

static_assert(sizeof(C) == 4u);
static_assert(not std::has_unique_object_representations_v< C >);

struct D
{
    A m_a = {};
    B m_b = {};
};

static_assert(sizeof(D) == 6u);
static_assert(not std::has_unique_object_representations_v< D >);

auto main()
	-> int
{
    return 0;
}
