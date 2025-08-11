// std::constructible_from
// std::convertible_to
#include <concepts>

template< typename SrcT, typename DstT >
concept StaticCastable = requires(SrcT src) { static_cast< DstT >(src); };

enum class A {};

auto main()
    -> int
{
    A a = {};
    static_assert(not std::constructible_from< A, int >);
    static_assert(not std::constructible_from< int, A >);
    static_assert(not std::convertible_to< A, int >);
    static_assert(not std::convertible_to< int, A >);
    static_assert(StaticCastable< A, int >);
    static_assert(StaticCastable< int, A >);

    static_assert(StaticCastable< A, void >);
    static_assert(StaticCastable< A*, void* >);

    return static_cast< int >(a);
}
