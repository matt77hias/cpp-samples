// std::size_t
#include <cstddef>

template< typename T, std::size_t A = alignof(T) >
struct Alignment
{
    static constexpr auto s_alignment = A;
};

template< typename T, std::size_t A >
struct Alignment< T[], A >
{
    static constexpr auto s_alignment = A;
};

auto main()
    -> int
{
    return static_cast< int >(Alignment< char[] >::s_alignment);
}
