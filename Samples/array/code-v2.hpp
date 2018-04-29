#include <algorithm>
#include <array>
#include <iostream>

template< typename T, size_t...Is >
constexpr std::array< T, sizeof...(Is) > 
    replicate_value_impl(T value, std::index_sequence< Is... >) {
    
    return { (static_cast< void >(Is), value)... };
}
template< typename T, size_t N >
constexpr std::array< T, N > replicate_value(T value) {
    return replicate_value_impl(value, std::make_index_sequence< N >());
}

template< typename ToT, typename FromT, size_t...Is >
constexpr std::array< ToT, sizeof...(Is) > 
    convert_array_impl(const std::array< FromT, sizeof...(Is) >& arr, 
                       std::index_sequence< Is... >) {
    
    return { static_cast< ToT >(arr[Is])... };
}
template< typename ToT, typename FromT, size_t N >
constexpr std::array< ToT, N > 
    convert_array(const std::array< FromT, N >& arr) {
    
    return convert_array_impl< ToT >(arr, std::make_index_sequence< N >());
}

template< typename T, size_t ToN, size_t...Is >
constexpr std::array< T, ToN > 
    extend_array_impl(const std::array< T, sizeof...(Is) >& arr, 
                      std::index_sequence< Is... >) {
    
    return { arr[Is]... };
}
template< typename T, size_t ToN, size_t FromN >
constexpr std::array< T, ToN > 
    extend_array(const std::array< T, FromN >& arr) {
    
    return extend_array_impl< T, ToN >(arr, std::make_index_sequence< FromN >());
}

template< typename T, std::size_t N >
struct A : std::array< T, N > {
    
    constexpr A() noexcept
        : std::array< T, N >{} {}
    
    template< typename U >
    constexpr explicit A(const A< U, N >& a) noexcept 
        : std::array< T, N >(convert_array< T >(a)) {}
    
    constexpr A(const A& a) noexcept = default;
    constexpr A(A&& a) noexcept = default;
   
    template< typename... Ts, typename = std::enable_if_t< (N == sizeof...(Ts)) > >
    constexpr A(Ts&&... elements) noexcept
        : std::array< T, N >{ std::move(elements)... } {}

    template< std::size_t N2, typename = std::enable_if_t< (N2 < N ) > >
    constexpr A(const A< T, N2 >& a) noexcept
        : std::array< T, N >(extend_array< T, N, N2 >(a)) {}
    
    template< std::size_t N2, typename... Ts, typename = std::enable_if_t< (N2 < N && (N2 + sizeof...(Ts)) == N ) > >
    constexpr A(const A< T, N2 >& a, Ts&&... elements) noexcept
        : std::array< T, N >(extend_array< T, N, N2 >(a)) {}
    
    ~A() = default;
    constexpr A& operator=(const A& a) noexcept = default;
    constexpr A& operator=(A&& a) noexcept = default;
};

template< typename T, std::size_t N >
std::ostream& operator<<(std::ostream& os, const A< T, N >& a) {
    for (auto i : a) { os << i << ' '; }
    return os << '\n';
}

int main() {
    constexpr A< float, 5 > a;
    std::cout << a;
    
    constexpr A< int, 5 > b(a);
    std::cout << b;
    
    constexpr A< int, 5 > c = { 1, 2, 3, 4, 5 };
    std::cout << c;
    
    constexpr A< int, 6 > d(c);
    std::cout << d;
    
    constexpr A< int, 6 > e(c, 6);
    std::cout << e;
    
    return 0;
}
