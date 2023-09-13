struct alignas(4u) A
{};

static_assert(alignof(A)     == 4u);
static_assert(alignof(A[2u]) == 4u);
static_assert(alignof(A[])   == 4u);

auto main()
    -> int
{
    return 0;
}
