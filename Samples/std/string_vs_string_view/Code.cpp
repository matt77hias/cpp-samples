// std::string
#include <string>
// std::string_view
#include <string_view>

static_assert(not std::convertible_to< std::string_view, std::string >);

auto main()
	noexcept -> int
{
    [[maybe_unused]] std::string src = "";
    [[maybe_unused]] std::string_view src_view = src;
    [[maybe_unused]] std::string dst{ src_view };

    return 0;
}
