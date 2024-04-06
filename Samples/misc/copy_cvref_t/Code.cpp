// same_as
#include <concepts>
// conditional_t, forward_like, is_lvalue_reference_v, remove_reference_t
#include <type_traits>
// declval
#include <utility>

template <bool RV, typename T>
using apply_ref = std::conditional_t< RV, T&&, T& >;

template <bool C, typename T>
using apply_const = std::conditional_t< C, T const, T >;

template <bool C, bool RV, typename T>
using apply_const_ref = apply_ref< RV, apply_const< C, T > >;

template <typename T, typename U>
using copy_cvref_t = apply_const_ref< std::is_const_v< std::remove_reference_t<T> >, !std::is_lvalue_reference_v< T >, U >;

template< typename T, typename U >
using copy_cvref2_t = decltype(std::forward_like< T, U >(std::declval< U >()));

static_assert(std::same_as< copy_cvref_t< int, int >, int&& >);
static_assert(std::same_as< copy_cvref_t< const int, int >, const int&& >);
static_assert(std::same_as< copy_cvref_t< int&, int >, int& >);
static_assert(std::same_as< copy_cvref_t< const int&, int >, const int& >);

static_assert(std::same_as< copy_cvref_t< int, const int >, const int&& >);
static_assert(std::same_as< copy_cvref_t< const int, const int >, const int&& >);
static_assert(std::same_as< copy_cvref_t< int&, const int >, const int& >);
static_assert(std::same_as< copy_cvref_t< const int&, const int >, const int& >);

static_assert(std::same_as< copy_cvref2_t< int, int >, int&& >);
static_assert(std::same_as< copy_cvref2_t< const int, int >, const int&& >);
static_assert(std::same_as< copy_cvref2_t< int&, int >, int& >);
static_assert(std::same_as< copy_cvref2_t< const int&, int >, const int& >);

static_assert(std::same_as< copy_cvref2_t< int, const int >, const int&& >);
static_assert(std::same_as< copy_cvref2_t< const int, const int >, const int&& >);
static_assert(std::same_as< copy_cvref2_t< int&, const int >, const int& >);
static_assert(std::same_as< copy_cvref2_t< const int&, const int >, const int& >);

auto main()
    -> int
{
    return 0;
}
