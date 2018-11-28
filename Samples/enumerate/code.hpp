// Source: http://www.reedbeta.com/blog/python-like-enumerate-in-cpp17/

#include <array>
#include <iostream>
#include <tuple>

template <typename T,
          typename TIter = decltype(std::begin(std::declval< T >())),
          typename       = decltype(std::end(  std::declval< T >()))>
constexpr auto enumerate(T&& iterable) {
    
    struct iterator {
        size_t i;
        TIter iter;
        bool operator!=(const iterator& rhs) const { return iter != rhs.iter; }
        void operator++ () { ++i; ++iter; }
        auto operator* () const { return std::tie(i, *iter); }
    };
    
    struct iterable_wrapper {
        T iterable;
        auto begin() { return iterator{ 0u, std::begin(iterable) }; }
        auto end()   { return iterator{ 0u, std::end(  iterable) }; }
    };
    
    return iterable_wrapper{ std::forward< T >(iterable) };
}

int main() {
    std::array< float, 5u > data = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
    for (auto [i, datum] : enumerate(data)) {
        std::cout << '(' << i << " , " << datum << ')' << std::endl;
    }
    
    return 0;
}
