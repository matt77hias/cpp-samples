// assert
#include <cassert>
// abort
#include <cstdlib>

[[nodiscard]]
constexpr auto test(bool value)
    noexcept -> bool
{
    if consteval
    {
        // Compile-time assert
        if (!value)
        {
            std::abort(); // Something to break compilation.
        }
    }
    else
    {
        // Runtime assert
        assert(value);
    }

    return value;
};

auto main() -> int
{ 
    [[maybe_unused]]
    constexpr auto t1 = test(true);
    //constexpr auto t2 = test(false);

    return 0;
}
