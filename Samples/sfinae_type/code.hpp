#include <type_traits>

template< typename T >
using Float = std::enable_if_t< std::is_floating_point_v< T >, T >;

int main() {
    Float< float > f = 1.0f;
    //Float< int > i = 1; 
    return 0;
}
