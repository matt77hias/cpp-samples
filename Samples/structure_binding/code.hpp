#include <array>
#include <iostream>

template< typename T, size_t N, size_t A = alignof(T) >
struct alignas(A) Array : std::array< T, N > {};

namespace std {

    template< typename T, size_t N, size_t A >
    class tuple_size< Array< T, N, A > > : public integral_constant< size_t, N > {};

    template< size_t I, typename T, size_t N, size_t A >
    class tuple_element< I, Array< T, N, A > > {
    public:
        using type = T;
    };
}

int main() {
    constexpr std::array< int, 3 > a = {{ 9, 8, 7 }};
    constexpr Array< int, 3 > b      = {{ 9, 8, 7 }};
    
    const auto [ax, ay, az] = a;
    std::cout << ax << ay << az;
    const auto [bx, by, bz] = b;
    std::cout << bx << by << bz;
    
    return 0;
}
