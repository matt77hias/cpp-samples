#include <iostream>
#include <type_traits>

template< typename T >
using FloatingPoint = std::enable_if_t< std::is_floating_point_v< T >, T >;

template< typename T >
using Integral = std::enable_if_t< std::is_integral_v< T >, T >;

template< typename T >
void f(T f, [[maybe_unused]] FloatingPoint< T > c = T(0)) {
    std::cout << "FloatingPoint: " << f << std::endl;
}

template< typename T >
void f(T f, [[maybe_unused]] Integral< T > c = T(0)) {
    std::cout << "Integral: " << f << std::endl;
}

int main() {
    FloatingPoint< float > f2f = 2.0f;
    //FloatingPoint< int > i2f = 2; 
    //Integral< float > f2i = 2.0f;
    Integral< int > i2i = 2;
    
    f(f2f);
    f(i2i);
    
    return 0;
}
