#include <type_traits>

template< typename T >
using FloatingPoint = std::enable_if_t< std::is_floating_point_v< T >, T >;

template< typename T >
using Integral = std::enable_if_t< std::is_integral_v< T >, T >;

int main() {
    FloatingPoint< float > f2f = 1.0f;
    //FloatingPoint< int > i2f = 1; 
    //Integral< float > f2i = 1.0f;
    Integral< int > i2i = 1;
    return 0;
}
