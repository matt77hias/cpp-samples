struct A
{};
struct B : A
{};

[[nodiscard]]
constexpr auto f(const A&)
    noexcept -> int
{
    return 1;
}
[[nodiscard]]
constexpr auto f(A&&)
    noexcept -> int
{
    return 2;
}
[[nodiscard]]
constexpr auto f(const B&)
    noexcept -> int
{
    return 3;
}
[[nodiscard]]
constexpr auto f(B&&)
    noexcept -> int
{
    return 4;
}

auto main()
    -> int
{
    const A a = {};
    
    return f(static_cast< const A&& >(a));
}
