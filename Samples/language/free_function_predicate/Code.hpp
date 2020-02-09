// find_if
#include <algorithm>
// cout, endl
#include <iostream>
// vector
#include <vector>

[[nodiscard]]
constexpr bool predicate(int x)
{
    return x == 2;
}

int main()
{
    const std::vector v = { 1, 2, 3, 4 };
    std::cout << (std::find_if(v.begin(), v.end(), predicate) != v.end()) << std::endl;
    return 0;
}
