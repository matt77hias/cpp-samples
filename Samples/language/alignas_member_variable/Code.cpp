// byte
#include <cstddef>
// declval
#include <utility>

struct A
{
    std::byte m_value = {};
};

static_assert(sizeof(A) == 1u);

struct B
{
    alignas(16u) A m_a = {};
};

static_assert(sizeof(B) == 16u);
static_assert(sizeof(std::declval< B >().m_a) == 1u);
static_assert(sizeof(decltype(std::declval< B >().m_a)) == 1u);

auto main()
    -> int
{
    return 0;
}
