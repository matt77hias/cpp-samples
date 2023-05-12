// lower_bound
#include <algorithm>
// less
#include <functional>
// pair
#include <utility>
// vector
#include <vector>

struct Widget
{
    [[nodiscard]]
    constexpr auto operator <=>(const Widget& rhs) const noexcept = default;
};

auto main()
	-> int
{
    using key_type   = Widget;
    using Container  = std::vector< std::pair< Widget, int > >;
    using value_type = Container::value_type;

    constexpr auto project = [](const value_type& value) noexcept -> const key_type&
    {
        return value.first;
    };

    Container map;
    const auto it = std::ranges::lower_bound(map, Widget{}, std::ranges::less{}, project);

    return it != map.end();
}
