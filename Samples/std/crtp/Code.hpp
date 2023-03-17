// derived_from
#include <concepts>

template< typename VectorT >
struct Vector
{
    //static_assert(std::derived_from< VectorT, Vector< VectorT > >);
};

template< typename T >
struct DenseVector : Vector< DenseVector< T > >
{

};

auto main() -> int
{
    static_assert(std::derived_from< DenseVector< int >, Vector< DenseVector< int > > >);

    return 0;
}
