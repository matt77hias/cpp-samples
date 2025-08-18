// std::constructible_from
// std::convertible_to
#include <concepts>
// std::initializer_list
#include <initializer_list>
// std::cout
// std::endl
#include <iostream>
// std::string
#include <string>
// std::vector
#include <vector>

struct String
{
    String(const char* str)
    {
        std::cout << str << std::endl;
    }
    String(const String&)
    {
        std::cout << "copy" << std::endl;
    }
};

template< typename T >
struct Vector
{
    template< std::convertible_to< T > SrcT >
    Vector(std::initializer_list< SrcT >)
    {
        std::cout << "initializer_list" << std::endl;
    }
};

auto main()
	noexcept -> int
{
    [[maybe_unused]] std::vector< std::string > v1 = { "Foo", "Bar", "Baz" };
    static_assert(std::constructible_from< std::vector< std::string >, std::initializer_list< std::string > >);
    static_assert(not std::constructible_from< std::vector< std::string >, std::initializer_list< const char* > >);

    [[maybe_unused]] std::vector< String > v2 = { "Foo", "Bar", "Baz" };
    static_assert(std::constructible_from< std::vector< String >, std::initializer_list< String > >);
    static_assert(not std::constructible_from< std::vector< String >, std::initializer_list< const char* > >);

    [[maybe_unused]] Vector< String > v3 = { "Foo", "Bar", "Baz" };
    static_assert(std::constructible_from< Vector< String >, std::initializer_list< String > >);
    static_assert(std::constructible_from< Vector< String >, std::initializer_list< const char* > >);
    
    return 0;
}
