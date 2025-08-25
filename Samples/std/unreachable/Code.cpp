// std::unreachable
#include <utility>

[[nodiscard]]
auto test(bool flag)
	noexcept -> int
{
    if (true)
    {
        return 5;
    }
    else
    {
        std::unreachable();
        return {};
    }
}

auto main()
	-> int
{
    return test(true);
}
