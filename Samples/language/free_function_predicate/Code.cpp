// find_if
#include <algorithm>
// cout, endl
#include <iostream>
// vector
#include <vector>

[[nodiscard]]
constexpr auto predicate(int x)
    noexcept -> bool
{
    return x == 2;
}

auto main()
    -> int
{
    const std::vector v = { 1, 2, 3, 4 };
    std::cout << (std::find_if(v.begin(), v.end(), predicate) != v.end()) << std::endl;
    return 0;
}
