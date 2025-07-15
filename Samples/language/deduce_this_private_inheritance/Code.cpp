// forward_like
#include <type_traits>
// declval
#include <utility>

template< typename T, typename U >
using like_t = decltype(std::forward_like< T, U >(std::declval< U >()));

template< typename T >
class B
{

    int i = 5;

public:

    template <typename Self>
    constexpr auto get(this Self&& self)
        noexcept -> decltype(auto);
};

template< typename T >
template< typename SelfT >
constexpr auto B< T >
    ::get(this SelfT&& self)
    noexcept -> decltype(auto)
{
    using Base = like_t< SelfT, B >;

    return ((Base&&)self).i;
}

class D : private B< int >
{
    double i = 7.0;

public:

    using B::get;
};

auto main() -> int
{
    return D().get(); // now ok, and returns B::i
}
