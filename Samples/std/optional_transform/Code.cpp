// same_as
#include <concepts>
// optional
#include <optional>

auto main() -> int
{
    std::optional< const int > i = 7;
    constexpr auto function = [](int i) noexcept -> const float
    {
        return static_cast< float >(i);
    };
    auto f = i.transform(function);
    static_assert(std::same_as< decltype(f), std::optional< float > >);

    return 0;
}
