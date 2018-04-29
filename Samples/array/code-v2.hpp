#include <algorithm>
#include <array>
#include <iostream>
#include <tuple>

template< typename T, size_t...I >
constexpr decltype(auto) replicate_value_impl(T value, std::index_sequence< I... >) {
    return std::array< T, sizeof...(I) >{ (static_cast< void >(I), value)... };
}
template< typename T, size_t N >
constexpr decltype(auto) replicate_value(T value) {
    return replicate_value_impl(value, std::make_index_sequence< N >());
}

template< typename ToT, typename FromT, size_t...I >
constexpr decltype(auto) convert_array_impl(const std::array< FromT, sizeof...(I) >& arr, 
                                            std::index_sequence< I... >) {
    
    return std::array< ToT, sizeof...(I) >{ static_cast< ToT >(arr[I])... };
}
template< typename ToT, typename FromT, size_t N >
constexpr decltype(auto) convert_array(const std::array< FromT, N >& arr) {
    return convert_array_impl< ToT >(arr, std::make_index_sequence< N >());
}

template< typename T, size_t ToN, size_t...I >
constexpr decltype(auto) extend_array_impl(const std::array< T, sizeof...(I) >& arr, 
                                           std::index_sequence< I... >) {
    
    return std::array< T, ToN >{ arr[I]... };
}
template< typename T, size_t ToN, size_t FromN >
constexpr decltype(auto) extend_array(const std::array< T, FromN >& arr) {
    return extend_array_impl< T, ToN >(arr, std::make_index_sequence< FromN >());
}

template< typename... Ts >
constexpr decltype(auto) args_to_tuple(Ts&&... elements) {
    return std::make_tuple(std::forward< Ts >(elements)...);
}
template< typename T, size_t...I >
constexpr decltype(auto) array_to_tuple_impl(const std::array< T, sizeof...(I) >& a, std::index_sequence< I... >) {
    return std::make_tuple(a[I]...);
}
template< typename T, size_t N >
constexpr decltype(auto) array_to_tuple(const std::array< T, N >& a) {
    return array_to_tuple_impl(a, std::make_index_sequence< N >()); 
}
template< typename T, typename TupleT, std::size_t... I >
constexpr decltype(auto) tuple_to_array_impl(const TupleT& t, std::index_sequence< I... >) {
    return std::array< T, sizeof...(I) >{ std::get< I >(t)... };
}
template< typename T, typename... Ts >
constexpr decltype(auto) tuple_to_array(const std::tuple< T, Ts... >& t) {
    constexpr auto N = sizeof...(Ts) + 1;
    return tuple_to_array_impl< T >(t, std::make_index_sequence< N >());
}

template< typename T, std::size_t N, typename = std::enable_if_t< (N != 1) > >
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
        : std::array< T, N >{ std::forward< Ts >(elements)... } {}

    template< std::size_t N2, typename = std::enable_if_t< (N2 < N) > >
    constexpr A(const A< T, N2 >& a) noexcept
        : std::array< T, N >(extend_array< T, N, N2 >(a)) {}
    
    template< std::size_t N2, typename... Ts, typename = std::enable_if_t< (N2 < N && (N2 + sizeof...(Ts)) == N ) > >
    constexpr A(const A< T, N2 >& a, Ts&&... elements) noexcept 
        : std::array< T, N >(tuple_to_array(std::tuple_cat(array_to_tuple(a), args_to_tuple(std::forward< Ts >(elements)...)))) {}
    
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
