struct alignas(4u) A
{};

auto main() -> int
{
    return static_cast< int >(alignof(A[]));
}
