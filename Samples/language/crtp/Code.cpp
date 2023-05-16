// derived_from, integral
#include <concepts>
// declval
#include <utility>

template< typename T >
using type_t = T::type;

template< typename VectorT >
struct Vector
{
    //using type = VectorT::type;
    //using type = type_t< VectorT >;
    //using type = decltype(std::declval< VectorT >().f());

    constexpr auto f() const
        noexcept -> decltype(auto)
        requires(requires (VectorT v) { { v.f() } -> std::integral; })
    {
        return static_cast< const VectorT& >(*this).f();
    };
};

template< typename T >
struct DenseVector : Vector< DenseVector< T > >
{
    using type = int;

    constexpr auto f() const
        noexcept -> type
    {
        return 7;
    };
};

auto main()
	-> int
{
    DenseVector< int > dv;
    const Vector< DenseVector< int > >& v = dv;

    return v.f();
}
