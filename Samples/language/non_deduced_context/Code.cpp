// std::size_t
#include <cstddef>
// std::same_as
#include <concepts>
// std::tuple_element
// std::tuple_size
#include <tuple>
// std::integral_constant
#include <type_traits>

template< typename T >
struct Outer
{
    using value_type = T;

    struct Inner
    {
        using value_type = typename Outer::value_type;

        int m_first  = {};
        int m_second = {};
    };
};

namespace std
{
  template< typename T >
  requires(std::same_as< T, typename ::Outer< typename T::value_type >::Inner >)
  class tuple_size< T > : public integral_constant< size_t, 2u >
  {};

  template< typename T >
  requires(std::same_as< T, typename ::Outer< typename T::value_type >::Inner >)
  struct tuple_element< 0u, T >
  {
      using type = int;
  };

  template< typename T >
  requires(std::same_as< T, typename ::Outer< typename T::value_type >::Inner >)
  struct tuple_element< 1u, T >
  {
      using type = int;
  };
}

template< std::size_t I, typename T >
requires(std::same_as< T, typename Outer< typename T::value_type >::Inner >)
[[nodiscard]]
inline auto get(T& src)
    -> std::tuple_element_t< I, T >&
{
    if constexpr (I == 0u)
    {
        return src.m_first;
    }
    if constexpr (I == 1u)
    {
        return src.m_second;
    }
}

template< std::size_t I, typename T >
requires(std::same_as< T, typename Outer< typename T::value_type >::Inner >)
[[nodiscard]]
inline auto get(const T& src)
    -> const std::tuple_element_t< I, T >&
{
    if constexpr (I == 0u)
    {
        return src.m_first;
    }
    if constexpr (I == 1u)
    {
        return src.m_second;
    }
}

template< std::size_t I, typename T >
requires(std::same_as< T, typename Outer< typename T::value_type >::Inner >)
[[nodiscard]]
inline auto get(T&& src)
    -> std::tuple_element_t< I, T >&&
{
    if constexpr (I == 0u)
    {
        return src.m_first;
    }
    if constexpr (I == 1u)
    {
        return src.m_second;
    }
}

template< std::size_t I, typename T >
requires(std::same_as< T, typename Outer< typename T::value_type >::Inner >)
[[nodiscard]]
inline auto get(const T&& src)
    -> const std::tuple_element_t< I, T >&&
{
    if constexpr (I == 0u)
    {
        return src.m_first;
    }
    if constexpr (I == 1u)
    {
        return src.m_second;
    }
}

auto main()
    -> int
{
    Outer< int >::Inner ref;
    auto& [f, s] = ref;
    f = 3; s = 5;
    
    return ref.m_first + ref.m_second;
}
