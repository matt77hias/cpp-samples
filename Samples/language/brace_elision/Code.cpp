// array
#include <array>
// size_t
#include <cstddef>

template< typename T, std::size_t N, std::size_t A = alignof(T) >
struct alignas(A) StaticArray : std::array< T, N >
{};

template< typename T, typename... Ts >
StaticArray(T, Ts...) -> StaticArray< T, 1u + sizeof...(Ts) >;

auto main()
    -> int
{
    // 1D
    
    [[maybe_unused]] int a0[2u] = { 1, 2 };
    
    [[maybe_unused]] std::array< int, 2u > aa0 = { 1, 2 }; // Brace elision
    [[maybe_unused]] std::array< int, 2u > aa1 = { { 1, 2 } };
    
    [[maybe_unused]] StaticArray< int, 2u > aaa0 = { 1, 2 }; // Brace elision
    [[maybe_unused]] StaticArray< int, 2u > aaa1 = { { 1, 2 } };
    [[maybe_unused]] StaticArray< int, 2u > aaa2 = { { { 1, 2 } } };

    // 2D

    [[maybe_unused]] int b0[2u][2u] = { 1, 2, 3, 4 }; // Brace elision
    [[maybe_unused]] int b1[2u][2u] = { { 1, 2 },  { 3, 4 } };

    [[maybe_unused]] std::array< std::array< int, 2u >, 2u > bb0 = { 1, 2, 3, 4 }; // Brace elision
    [[maybe_unused]] std::array< std::array< int, 2u >, 2u > bb1 = { { { { 1, 2 } }, { { 3, 4 } } } };

    [[maybe_unused]] StaticArray< StaticArray< int, 2u >, 2u > bbb0 = { 1, 2, 3, 4 }; // Brace elision
    [[maybe_unused]] StaticArray< StaticArray< int, 2u >, 2u > bbb1 = { { { { { { 1, 2 } } }, { { { 3, 4 } } } } } };

    // CTAD

    [[maybe_unused]] int c0[] = { 1, 2 };

    [[maybe_unused]] std::array cc0 = { 1, 2 };

    [[maybe_unused]] StaticArray ccc1 = { 1, 2 };

    return 0;
}
