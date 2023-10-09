// move
#include <utility>

struct Base
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
};

struct Widget : Base
{
    [[nodiscard]]
    constexpr auto g() &
        noexcept -> int
    {
        return Base::f();
    }

    [[nodiscard]]
    constexpr auto g() &&
        noexcept -> int
    {
        return std::move(*this).Base::f();
    }

    [[nodiscard]]
    constexpr auto g() const &
        noexcept -> int
    {
        return Base::f();
    }

    [[nodiscard]]
    constexpr auto g() const &&
        noexcept -> int
    {
        return std::move(*this).Base::f();
    }
};

auto main()
    -> int
{
    Widget widget{};
    
    return std::move(widget).g();
}
