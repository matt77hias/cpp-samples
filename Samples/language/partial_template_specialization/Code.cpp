// std::array
#include <array>
// std::size_t
#include <cstddef>
// std::cout
// std::endl
#include <iostream>

template< typename T, std::size_t N, std::size_t A = alignof(T) >
struct alignas(A) Array : std::array< T, N > {};

template< typename T >
struct Widget;

template< typename T, std::size_t N, std::size_t A >
struct Widget< Array< T, N, A > >
{
    void print() const
    {
        std::cout << "Widget< Array< T, N, A > >::print()" << std::endl;
    }
};

auto main()
    -> int
{
    Widget< Array< int, 3 > > w;
    w.print();
    
    return 0;
}
