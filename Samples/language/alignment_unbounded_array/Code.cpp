struct alignas(4u) Widget
{};

static_assert(alignof(Widget)     == 4u);
static_assert(alignof(Widget[2u]) == 4u);
static_assert(alignof(Widget[])   == 4u);

auto main()
    -> int
{
    return 0;
}
