#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

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

template< typename T, std::size_t N >
struct A : std::array< T, N > {
    constexpr A() noexcept
        : std::array< T, N >{} {}
    constexpr explicit A(T v) noexcept
        : std::array< T, N >(replicate_value< T, N >(v)) {}
    
    // (-) no std::initializer_list
    // (-) implicit conversions are possible
    template< typename... U > 
    constexpr A(U... elements) noexcept
        : std::array< T, N >{ elements... } {}
    
    template< typename U >
    constexpr explicit A(const A< U, N >& a) noexcept 
        : std::array< T, N >(convert_array< T >(a)) {}
    
    constexpr A(const A& a) noexcept = default;
    constexpr A(A&& a) noexcept = default;
    ~A() = default;
    constexpr A& operator=(const A& a) noexcept = default;
    constexpr A& operator=(A&& a) noexcept = default;
};

int main() {
    constexpr A< float, 5 > a;
    for (auto i : a) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    
    constexpr A< float, 5 > b(5.5f);
    for (auto i : b) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    
    constexpr A< int, 5 > c(b);
    for (auto i : c) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    
    constexpr A< int, 5 > d = { 1, 2, 3 };
    for (auto i : d) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    
    // (-) not transparent compared to std::vector
    //
    //constexpr A< int, 5 > e = { 1 };
    //for (auto i : e) {
    //   std::cout << i << ' ';
    //}
    //std::cout << '\n';
    
    std::vector< int > v1(5,5);
    for (auto i : v1) {
        std::cout << i << ' ';
    }
    std::cout << '\n'; 
    
    std::vector< int > v2({5,5});
    for (auto i : v2) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}
