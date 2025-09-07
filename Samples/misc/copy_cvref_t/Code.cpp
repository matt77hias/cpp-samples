// std::same_as
#include <concepts>
// std::conditional_t
// std::forward_like
// std::is_lvalue_reference_v
// std::remove_reference_t
#include <type_traits>
// std::declval
#include <utility>

template< bool IsRValue, typename T >
using apply_ref = std::conditional_t< IsRValue, T&&, T& >;

template< bool IsConst, typename T >
using apply_const = std::conditional_t< IsConst, T const, T >;

template< bool IsConst, bool IsRValue, typename T >
using apply_const_ref = apply_ref< IsRValue, apply_const< IsConst, T > >;

template< typename T, typename U >
using copy_cvref_t = apply_const_ref< std::is_const_v< std::remove_reference_t< T > >, !std::is_lvalue_reference_v< T >, U >;

template< typename T, typename U >
using forward_like_t = decltype(std::forward_like< T, U >(std::declval< U >()));

static_assert(std::same_as< copy_cvref_t< int, int >, int&& >);
static_assert(std::same_as< copy_cvref_t< const int, int >, const int&& >);
static_assert(std::same_as< copy_cvref_t< int&, int >, int& >);
static_assert(std::same_as< copy_cvref_t< const int&, int >, const int& >);

static_assert(std::same_as< copy_cvref_t< int, const int >, const int&& >);
static_assert(std::same_as< copy_cvref_t< const int, const int >, const int&& >);
static_assert(std::same_as< copy_cvref_t< int&, const int >, const int& >);
static_assert(std::same_as< copy_cvref_t< const int&, const int >, const int& >);

static_assert(std::same_as< forward_like_t< int, int >, int&& >);
static_assert(std::same_as< forward_like_t< const int, int >, const int&& >);
static_assert(std::same_as< forward_like_t< int&, int >, int& >);
static_assert(std::same_as< forward_like_t< const int&, int >, const int& >);

static_assert(std::same_as< forward_like_t< int, const int >, const int&& >);
static_assert(std::same_as< forward_like_t< const int, const int >, const int&& >);
static_assert(std::same_as< forward_like_t< int&, const int >, const int& >);
static_assert(std::same_as< forward_like_t< const int&, const int >, const int& >);

auto main()
    -> int
{
    return 0;
}
