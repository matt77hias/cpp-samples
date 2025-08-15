// std::ranges::construct_at
#include <memory>

[[nodiscard]]
constexpr auto f()
    -> int
{
    int i = {};
    const int* ip = &i;
    std::ranges::construct_at(ip, 5);
    return i;
}

auto main()
	noexcept -> int
{
    constexpr auto result = f();
    
    return result;
}
