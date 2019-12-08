// cout, endl
#include <iostream>
// false_type, is_convertible_v, remove_const_t, true_type
#include <type_traits>
// declval
#include <utility>

template< typename FromT, typename ToT, typename = ToT >
struct is_static_castable 
    : public std::false_type
{};

template< typename FromT, typename ToT >
struct is_static_castable< FromT, ToT, 
decltype(static_cast< std::remove_const_t< ToT > >(std::declval< std::remove_const_t< FromT > >())) > 
    : public std::true_type
{};

template< typename FromT, typename ToT >
constexpr bool is_static_castable_v = is_static_castable< FromT, ToT >::value;

int main()
{
    std::cout << is_static_castable_v< float, unsigned int >;
    std::cout << is_static_castable_v< float, int >;
    std::cout << is_static_castable_v< unsigned int, float >;
    std::cout << is_static_castable_v< int, float >;
    
    std::cout << is_static_castable_v< float, const unsigned int >;
    std::cout << is_static_castable_v< float, const int >;
    std::cout << is_static_castable_v< unsigned int, const float >;
    std::cout << is_static_castable_v< int, const float >;
    
    std::cout << is_static_castable_v< const float, unsigned int >;
    std::cout << is_static_castable_v< const float, int >;
    std::cout << is_static_castable_v< const unsigned int, float >;
    std::cout << is_static_castable_v< const int, float >;

    std::cout << is_static_castable_v< const float, const unsigned int >;
    std::cout << is_static_castable_v< const float, const int >;
    std::cout << is_static_castable_v< const unsigned int, const float >;
    std::cout << is_static_castable_v< const int, const float >;
    
    std::cout << std::endl;
    
    std::cout << std::is_convertible_v< float, unsigned int >;
    std::cout << std::is_convertible_v< float, int >;
    std::cout << std::is_convertible_v< unsigned int, float >;
    std::cout << std::is_convertible_v< int, float >;
    
    std::cout << std::is_convertible_v< float, const unsigned int >;
    std::cout << std::is_convertible_v< float, const int >;
    std::cout << std::is_convertible_v< unsigned int, const float >;
    std::cout << std::is_convertible_v< int, const float >;
    
    std::cout << std::is_convertible_v< const float, unsigned int >;
    std::cout << std::is_convertible_v< const float, int >;
    std::cout << std::is_convertible_v< const unsigned int, float >;
    std::cout << std::is_convertible_v< const int, float >;

    std::cout << std::is_convertible_v< const float, const unsigned int >;
    std::cout << std::is_convertible_v< const float, const int >;
    std::cout << std::is_convertible_v< const unsigned int, const float >;
    std::cout << std::is_convertible_v< const int, const float >;
    
    return 0;
}
