#include <array>
#include <iostream>

template< typename ActionT, typename T, size_t...I >
constexpr auto TransformArrayImpl(ActionT&& action, 
                                  const std::array< T, sizeof...(I) >& a, 
                                  std::index_sequence< I... >) {
    using ToT = decltype(std::declval< ActionT >()(std::declval< T >()));
    return std::array< ToT, sizeof...(I) >{ action(a[I])... };
}

template< typename ActionT, typename T, size_t N >
constexpr auto TransformArray(ActionT&& action, 
                              const std::array< T, N >& a) {
    return TransformArrayImpl(std::forward< ActionT >(action), a, 
                              std::make_index_sequence< N >());
}

template< typename T, std::size_t N >
std::ostream& operator<<(std::ostream& os, const std::array< T, N >& a) {
    for (auto i : a) { os << i << ' '; }
    return os << '\n';
}

int main() {
    constexpr std::array< float, 5 > a = { 1,2,3,4,5 };
    constexpr auto f = [](float x) { return x*x; };
    std::cout << TransformArray(f, a);
    
    return 0;
}
