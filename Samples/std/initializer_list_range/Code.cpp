// std::initializer_list
#include <initializer_list>
// std::cout
#include <iostream>
// std::range
#include <ranges>

template< std::ranges::range R >
constexpr void test(R&& range)
    noexcept
{
    std::cout << "1";
}

constexpr void test(std::initializer_list< int > range)
    noexcept
{
    std::cout << "0";
    // test< const std::initializer_list< int >& >(range);
}

auto main()
  -> int
{
    std::initializer_list< int > il = { 1, 2, 3, 4 };
    auto& ref = il;
    const std::initializer_list< int > cil = { 1, 2, 3, 4 };
    const auto& cref = cil;

    test({ 1, 2, 3, 4 });
    test(il);
    test(ref);
    test(cil);
    test(cref);
    
    return 0;
}
