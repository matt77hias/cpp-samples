inline constexpr auto Alignment = 4u;

struct alignas(Alignment) Widget
{};

static_assert(alignof(Widget)     == Alignment);
static_assert(alignof(Widget[2u]) == Alignment);
static_assert(alignof(Widget[])   == Alignment);

auto main()
    -> int
{
    return 0;
}
