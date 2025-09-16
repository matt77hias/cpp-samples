// std::size_t
#include <cstdint>
// std::ranges::range
#include <ranges>
// std::remove_cvref_t
// std::unsigned_integral
#include <type_traits>

template< typename T >
concept mdrange = 0u < std::remove_cvref_t< T >::ExtentCount;

template< mdrange R >
inline constexpr std::size_t ExtentCount = std::remove_cvref_t< R >::ExtentCount;

template< std::size_t ExtentCount >
struct Widget 
{
    template< std::size_t I = 0u, std::unsigned_integral... IndexTs >
    constexpr auto begin(IndexTs... indices)
        requires((I < ExtentCount) and (sizeof...(IndexTs) == ExtentCount - 1u))
    {
        return &m_value;
    }

    template< std::size_t I = 0u, std::unsigned_integral... IndexTs >
    constexpr auto end(IndexTs... indices)
        requires((I < ExtentCount) and (sizeof...(IndexTs) == ExtentCount - 1u))
    {
        return &m_value + 1;
    }

    int m_value = {};
};

auto main()
    -> int
{
    static_assert(std::ranges::range< Widget< 1u > >);
    static_assert(not std::ranges::range< Widget< 2u > >);
    static_assert(not std::ranges::range< Widget< 3u > >);
    
    return 0;
}
