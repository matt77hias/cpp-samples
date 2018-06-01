#include <array>
#include <iostream>

template< typename T, size_t N, size_t A = alignof(T) >
struct alignas(A) Array : std::array< T, N > {};

template< typename T >
struct Widget;

template< typename T, size_t N, size_t A >
struct Widget< Array< T, N, A > > {
    void print() const {
        std::cout << "Widget< Array< T, N, A > >::print()" << std::endl;
    }
};

int main() {
    Widget< Array< int, 3 > > w;
    w.print();
    
    return 0;
}
