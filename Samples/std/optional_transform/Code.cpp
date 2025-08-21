// std::same_as
#include <concepts>
// std::optional
#include <optional>

auto main()
    -> int
{
    [[maybe_unused]] std::optional< const int > i = 7;
    constexpr auto function = [](int i) noexcept -> const float
    {
        return static_cast< float >(i);
    };
    [[maybe_unused]] auto f = i.transform(function);
    static_assert(std::same_as< decltype(f), std::optional< float > >);

    return 0;
}
