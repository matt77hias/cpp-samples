#include <algorithm>
#include <array>
#include <iostream>
#include <tuple>

//-----------------------------------------------------------------------------
// The idea is to replace mage::Vector2, mage::Vector3, mage::Vector4, 
// mage::Vector2A, mage::Vector3A, mage::Vector4A with a std::array wrapper.
// Only (primitive) integral values should be uses which do not require dynamic
// memory allocation. If this is not the case, not all 'noexcept' occurences 
// will be appropriate.
//-----------------------------------------------------------------------------

template< typename T, size_t...I >
constexpr decltype(auto) replicate_value_impl(T value, std::index_sequence< I... >) noexcept {
    return std::array< T, sizeof...(I) >{ (static_cast< void >(I), value)... };
}
template< typename T, size_t N >
constexpr decltype(auto) replicate_value(T value) noexcept {
    return replicate_value_impl(value, std::make_index_sequence< N >());
}

template< typename ToT, typename FromT, size_t...I >
constexpr decltype(auto) convert_array_impl(const std::array< FromT, sizeof...(I) >& arr, 
                                            std::index_sequence< I... >) noexcept {
    
    return std::array< ToT, sizeof...(I) >{ static_cast< ToT >(arr[I])... };
}
template< typename ToT, typename FromT, size_t N >
constexpr decltype(auto) convert_array(const std::array< FromT, N >& arr) noexcept {
    return convert_array_impl< ToT >(arr, std::make_index_sequence< N >());
}

template< typename T, size_t ToN, size_t...I >
constexpr decltype(auto) extend_array_impl(const std::array< T, sizeof...(I) >& arr, 
                                           std::index_sequence< I... >) noexcept {
    
    return std::array< T, ToN >{ arr[I]... };
}
template< typename T, size_t ToN, size_t FromN >
constexpr decltype(auto) extend_array(const std::array< T, FromN >& arr) noexcept {
    return extend_array_impl< T, ToN >(arr, std::make_index_sequence< FromN >());
}

template< typename... Ts >
constexpr decltype(auto) args_to_tuple(Ts&&... elements) noexcept {
    return std::make_tuple(std::forward< Ts >(elements)...);
}
template< typename T, size_t...I >
constexpr decltype(auto) array_to_tuple_impl(const std::array< T, sizeof...(I) >& a, std::index_sequence< I... >) noexcept {
    return std::make_tuple(a[I]...);
}
template< typename T, size_t N >
constexpr decltype(auto) array_to_tuple(const std::array< T, N >& a) noexcept {
    return array_to_tuple_impl(a, std::make_index_sequence< N >()); 
}
template< typename T, typename TupleT, std::size_t... I >
constexpr decltype(auto) tuple_to_array_impl(const TupleT& t, std::index_sequence< I... >) noexcept {
    return std::array< T, sizeof...(I) >{ std::get< I >(t)... };
}
template< typename T, typename... Ts >
constexpr decltype(auto) tuple_to_array(const std::tuple< T, Ts... >& t) noexcept {
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
        : std::array< T, N >(tuple_to_array(std::tuple_cat(array_to_tuple(a), 
                                                           args_to_tuple(std::forward< Ts >(elements)...)))) {}
    
    ~A() = default;
    constexpr A& operator=(const A& a) noexcept = default;
    constexpr A& operator=(A&& a) noexcept = default;
};

template< typename T, std::size_t N >
std::ostream& operator<<(std::ostream& os, const A< T, N >& a) {
    for (const auto& i : a) { os << i << ' '; }
    return os << '\n';
}

int main() {

    constexpr A< float, 5 > a;
    std::cout << a;
    
    constexpr A< float, 5 > b = { 1.5f, 2.5f, 3.5f, 4.5f, 5.5f };
    std::cout << b;
    
    constexpr A< int, 5 > c(b);
    std::cout << c;
    
    constexpr A< int, 6 > d(c);
    std::cout << d;
    
    constexpr A< int, 6 > e(c, 6);
    std::cout << e;
    
    return 0;
}
