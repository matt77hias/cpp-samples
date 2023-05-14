template< typename T >
struct A
{
    using type = T;
};

template< typename T >
struct B : A< T >
{};

template< typename T >
constexpr void f(typename T::type value)
{}

auto main()
	-> int
{
    A< int >::type a = {};
    B< int >::type b = {};

    f< A< int > >({});
    f< B< int > >({});
    return 0;
}
