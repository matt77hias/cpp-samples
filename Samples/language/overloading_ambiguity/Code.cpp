//[[nodiscard]]
//static constexpr auto f(int)
//    noexcept -> int
//{
//    return 1;
//}

[[nodiscard]]
static constexpr auto f(int&)
    noexcept -> int
{
    return 2;
}

[[nodiscard]]
static constexpr auto f(const int&)
    noexcept -> int
{
    return 3;
}

[[nodiscard]]
static constexpr auto f(int&&)
    noexcept -> int
{
    return 4;
}

[[nodiscard]]
static constexpr auto f(const int&&)
    noexcept -> int
{
    return 5;
}

auto main()
    -> int
{
    constexpr auto generate = []() -> int { return 0; };
    static_assert(f(generate()) == 4);
    
    return 0;
}
