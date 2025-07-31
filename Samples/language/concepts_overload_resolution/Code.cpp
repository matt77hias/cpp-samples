// std::cout
#include <iostream>
// std::ranges::contiguous_range
// std::ranges::input_range
#include <ranges>
// std::vector
#include <vector>

constexpr auto generate()
    noexcept -> std::vector< int >
{
    return {};
}

template< std::ranges::input_range R >
void sink(R&&)
{
    std::cout << "input_range\n";
}

template< std::ranges::contiguous_range R >
void sink(const R&)
{
    std::cout << "contiguous_range\n";
}

auto main()
    -> int
{
    sink(generate());
    return 0;
}
