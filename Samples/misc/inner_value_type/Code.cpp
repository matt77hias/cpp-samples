// array
#include <array>
// conditional_t, is_same_v
#include <type_traits>

template< typename T, typename = void >
struct inner_value
{
    using type = T;
};

template< typename T >
struct inner_value< T, std::conditional_t< false, typename T::value_type, void > >
{
    using type = typename inner_value< typename T::value_type >::type;
};

template< typename T >
using inner_value_t = typename inner_value< T >::type;

auto main()
    -> int
{
    using type1d = unsigned int;
    using type2d = std::array< type1d, 1u >;
    using type3d = std::array< type2d, 1u >;
   
    static_assert(std::is_same_v< inner_value_t< type1d >, type1d > == true);
    static_assert(std::is_same_v< inner_value_t< type2d >, type1d > == true);
    static_assert(std::is_same_v< inner_value_t< type3d >, type1d > == true);

    static_assert(std::is_same_v< inner_value_t< type2d >, type2d > == false);
    static_assert(std::is_same_v< inner_value_t< type3d >, type3d > == false);

    return 0;
}
