// std::constructible_from
#include <concepts>
// std::is_lvalue_reference_v
// std::is_rvalue_reference_v
#include <type_traits>
// std::declval
#include <type_traits>

template< typename E >
struct A
{
    static void f(E&);
    static void f(E&&) = delete;

    template< typename T >
    A(T&& src)
        noexcept
        requires(std::convertible_to< T, E& > and requires { f(std::declval< T >()); })
    {}
};

template< typename E >
struct B
{
    template< typename T >
    B(T&& src)
        noexcept
        requires(std::convertible_to< T, E& > and not std::is_rvalue_reference_v< decltype(src) >)
    {}
};

template< typename E >
struct C
{
    template< typename T >
    C(T&& src)
        noexcept
        requires(std::convertible_to< T, E& > and std::is_lvalue_reference_v< decltype(src) >)
    {}
};

auto main()
    -> int
{
    static_assert(not std::constructible_from< A< int >, int >);
    static_assert(not std::constructible_from< A< int >, const int >);
    static_assert(std::constructible_from< A< int >, int& >);
    static_assert(not std::constructible_from< A< int >, const int& >);
    static_assert(not std::constructible_from< A< int >, int&& >);
    static_assert(not std::constructible_from< A< int >, const int&& >);

    static_assert(not std::constructible_from< A< const int >, int >);
    static_assert(not std::constructible_from< A< const int >, const int >);
    static_assert(std::constructible_from< A< const int >, int& >);
    static_assert(std::constructible_from< A< const int >, const int& >);
    static_assert(not std::constructible_from< A< const int >, int&& >);
    static_assert(not std::constructible_from< A< const int >, const int&& >);

    static_assert(not std::constructible_from< B< int >, int >);
    static_assert(not std::constructible_from< B< int >, const int >);
    static_assert(std::constructible_from< B< int >, int& >);
    static_assert(not std::constructible_from< B< int >, const int& >);
    static_assert(not std::constructible_from< B< int >, int&& >);
    static_assert(not std::constructible_from< B< int >, const int&& >);

    static_assert(not std::constructible_from< B< const int >, int >);
    static_assert(not std::constructible_from< B< const int >, const int >);
    static_assert(std::constructible_from< B< const int >, int& >);
    static_assert(std::constructible_from< B< const int >, const int& >);
    static_assert(not std::constructible_from< B< const int >, int&& >);
    static_assert(not std::constructible_from< B< const int >, const int&& >);

    static_assert(not std::constructible_from< C< int >, int >);
    static_assert(not std::constructible_from< C< int >, const int >);
    static_assert(std::constructible_from< C< int >, int& >);
    static_assert(not std::constructible_from< C< int >, const int& >);
    static_assert(not std::constructible_from< C< int >, int&& >);
    static_assert(not std::constructible_from< C< int >, const int&& >);

    static_assert(not std::constructible_from< C< const int >, int >);
    static_assert(not std::constructible_from< C< const int >, const int >);
    static_assert(std::constructible_from< C< const int >, int& >);
    static_assert(std::constructible_from< C< const int >, const int& >);
    static_assert(not std::constructible_from< C< const int >, int&& >);
    static_assert(not std::constructible_from< C< const int >, const int&& >);
    
    return 0;
}
