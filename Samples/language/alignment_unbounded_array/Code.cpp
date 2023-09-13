inline constexpr auto Alignment = 4u;

struct alignas(Alignment) A
{};

static_assert(alignof(A)     == Alignment);
static_assert(alignof(A[2u]) == Alignment);
static_assert(alignof(A[])   == Alignment);

auto main()
    -> int
{
    return 0;
}
