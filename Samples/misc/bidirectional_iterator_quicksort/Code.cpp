// partition
#include <algorithm>
// cout, endl
#include <iostream>
// bidirectional_iterator, distance, iter_swap, next, prev, sentinel_for
#include <iterator>
// list
#include <list>
// less
#include <ranges>
// move
#include <utility>

template< std::bidirectional_iterator I, typename CompareT >
void QuickSort(I first, I last, CompareT compare)
{
    const auto count = std::ranges::distance(first, last);
    if (count < 2)
    {
        return;
    }

    const auto prev_last = std::ranges::prev(last);
    auto middle = std::ranges::next(first, count / 2);
    
    // Store the pivot.
    std::ranges::iter_swap(middle, prev_last);

    const auto compare_proxy
        = [compare, prev_last](const auto& value)
            noexcept -> bool
    {
        return compare(value, *prev_last);
    };

    middle = std::partition(first, prev_last, compare_proxy);

    // Restore the pivot.
    std::ranges::iter_swap(middle, prev_last);

    QuickSort(first, middle, compare);
    QuickSort(std::ranges::next(middle), last, compare);
}

auto main() -> int
{
    std::list values = { 5, 4, 3, 2, 1, 3 };
    for (const auto value : values)
    {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    QuickSort(values.begin(), values.end(), std::ranges::less{});
    for (const auto value : values)
    {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    return 0;
}
