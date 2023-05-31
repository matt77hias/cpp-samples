// array
#include <array>
// size_t
#include <cstddef>
// cout, endl, ostream
#include <iostream>
// declval, forward, index_sequence, make_index_sequence
#include <utility>

template< typename ActionT, typename T, std::size_t... Is >
[[nodiscard]]
constexpr auto TransformArrayImpl(ActionT&& action, 
                                  const std::array< T, sizeof...(Is) >& a, 
                                  std::index_sequence< Is... >)
{
    using ToT = decltype(std::declval< ActionT >()(std::declval< T >()));
    return std::array< ToT, sizeof...(Is) >{ action(a[Is])... };
}

template< typename ActionT, typename T, std::size_t N >
[[nodiscard]]
constexpr auto TransformArray(ActionT&& action, 
                              const std::array< T, N >& a)
{
    return TransformArrayImpl(std::forward< ActionT >(action),
                              a, 
                              std::make_index_sequence< N >());
}

template< typename T, std::size_t N >
auto operator <<(std::ostream& os, const std::array< T, N >& a)
	-> std::ostream&
{
    for (auto i : a)
    {
        os << i << ' ';
    }

    return os << '\n';
}

auto main()
	-> int
{
    constexpr std::array< float, 5u > a = { 1, 2, 3, 4, 5 };
    constexpr auto f = [](float x) { return x * x; };
    std::cout << TransformArray(f, a);
    
    return 0;
}
