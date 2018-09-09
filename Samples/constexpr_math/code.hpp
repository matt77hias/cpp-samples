#include <cstddef>
#include <type_traits>

namespace details {
    
    template< typename T, 
              typename = std::enable_if_t< std::is_unsigned_v< T > > >
    struct Factorial {
    
        constexpr T operator()(T x) noexcept {
            T result = 1u;
            for (T n = 2u; n <= x; ++n) {
                result *= n;
            }
            return result;
        }
    };
    
    template< typename T >
    constexpr T factorial(T x) noexcept {
        return Factorial< T >()(x);
    }
    
    template< typename T, typename E,
              typename = std::enable_if_t< std::is_unsigned_v< E > > >
    struct Power {
    
        constexpr T operator()(T x, E e) noexcept {
            T result = 1u;
            for (std::size_t n = 0u; n < e; ++n) {
                result *= x;
            }
            return result;
        }
    };
    
    template< typename T, typename E >
    constexpr T power(T x, E e) noexcept {
        return Power< T, E >()(x, e);
    }
    
    template< typename T, std::size_t N, 
              typename = std::enable_if_t< std::is_floating_point_v< T > > >
    struct Sine {
        
        constexpr T operator()(T x) noexcept {
            T result = 0u;
            for (std::size_t n = 0u; n < N; ++n) {
                result += power(-1, n) * power(x, 2u * n + 1u) / factorial(2u * n + 1u);        
            }
            return result;
        }
    };
    
    template< typename T, std::size_t N >
    constexpr T sin(T x) noexcept {
        return Sine< T, N >()(x);
    }
    
    template< typename T, std::size_t N, 
              typename = std::enable_if_t< std::is_floating_point_v< T > > >
    struct Cosine {
        
        constexpr T operator()(T x) noexcept {
            T result = 0u;
            for (std::size_t n = 0u; n < N; ++n) {
                result += power(-1, n) * power(x, 2u * n) / factorial(2u * n);        
            }
            return result;
        }
    };
    
    template< typename T, std::size_t N >
    constexpr T cos(T x) noexcept {
        return Cosine< T, N >()(x);
    }
}

// x!
template< typename T >
constexpr T factorial(T x) noexcept {
    return details::factorial(x);
}

// x^e
template< typename T, typename E >
constexpr T power(T x, E e) noexcept {
    return details::power(x, e);
}

// sin(x)
template< typename T, std::size_t N = 10 >
constexpr T sin(T x) noexcept {
    return details::sin< T, N >(x);
}

// cos(x)
template< typename T, std::size_t N = 10 >
constexpr T cos(T x) noexcept {
    return details::cos< T, N >(x);
}

#include <iostream>

int main() {
    constexpr auto sin_0  = sin(0.0);
    constexpr auto cos_0  = cos(0.0);
    constexpr auto sin_pi = sin(3.14159265359);
    constexpr auto cos_pi = cos(3.14159265359);
    
    std::cout << sin_0  << std::endl;
    std::cout << cos_0  << std::endl;
    std::cout << sin_pi << std::endl;
    std::cout << cos_pi << std::endl;
    
    return 0;
}
