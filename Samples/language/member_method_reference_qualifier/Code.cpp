// move
#include <utility>

struct Widget
{
    [[nodiscard]]
    constexpr auto f() &
        noexcept -> int
    {
        return 1;
    }

    [[nodiscard]]
    constexpr auto f() &&
        noexcept -> int
    {
        return 2;
    }

    [[nodiscard]]
    constexpr auto f() const &
        noexcept -> int
    {
        return 3;
    }

    [[nodiscard]]
    constexpr auto f() const &&
        noexcept -> int
    {
        return 4;
    }
   
    [[nodiscard]]
    constexpr auto g() &
        noexcept -> int
    {
        return f();
    }

    [[nodiscard]]
    constexpr auto g() &&
        noexcept -> int
    {
        return std::move(*this).f();
    }

    [[nodiscard]]
    constexpr auto g() const &
        noexcept -> int
    {
        return f();
    }

    [[nodiscard]]
    constexpr auto g() const &&
        noexcept -> int
    {
        return std::move(*this).f();
    }
};

auto main() -> int
{
    Widget widget{};
    
    return std::move(widget).g();
}
