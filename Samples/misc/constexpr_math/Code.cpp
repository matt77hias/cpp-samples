// size_t
#include <cstddef>
// cout, endl
#include <iostream>
// enable_if_t, is_floating_point_v, is_unsigned_v
#include <type_traits>

namespace internal
{
    template< typename T, 
              typename = std::enable_if_t< std::is_unsigned_v< T > > >
    struct Factorial
	{
        [[nodiscard]]
		constexpr auto operator ()(T x) const
			noexcept -> T
		{
            T result{ 1u };
            for (T n = 2u; n <= x; ++n)
			{
                result *= n;
            }
            return result;
        }
    };
    
    template< typename T >
    [[nodiscard]]
	constexpr auto factorial(T x)
	    noexcept -> T
	{
        return Factorial< T >()(x);
    }
    
    template< typename T, typename E,
              typename = std::enable_if_t< std::is_unsigned_v< E > > >
    struct Power
	{
        [[nodiscard]]
		constexpr auto operator ()(T x, E e) const 
			noexcept -> T
		{
            T result{ 1u };
            for (std::size_t n = 0u; n < e; ++n)
			{
                result *= x;
            }
            return result;
        }
    };
    
    template< typename T, typename E >
    [[nodiscard]]
	constexpr auto power(T x, E e)
		noexcept -> T
	{
        return Power< T, E >()(x, e);
    }
	
    template< typename T, std::size_t N, 
              typename = std::enable_if_t< std::is_floating_point_v< T > > >
    struct Sine
	{
		[[nodiscard]]
		constexpr auto operator ()(T x) const
			noexcept -> T
		{
            T result = {};
            for (std::size_t n = 0u; n < N; ++n)
			{
                result += power(-1, n) * power(x, 2u * n + 1u) / factorial(2u * n + 1u);        
            }
            return result;
        }
    };
    
    template< typename T, std::size_t N >
    [[nodiscard]]
	constexpr T sin(T x) noexcept
	{
        return Sine< T, N >()(x);
    }
    
    template< typename T, std::size_t N, 
              typename = std::enable_if_t< std::is_floating_point_v< T > > >
    struct Cosine
	{
        [[nodiscard]]
		constexpr auto operator ()(T x) const
			noexcept -> T
		{
            T result = {};
            for (std::size_t n = 0u; n < N; ++n)
			{
                result += power(-1, n) * power(x, 2u * n) / factorial(2u * n);        
            }
            return result;
        }
    };
    
    template< typename T, std::size_t N >
    [[nodiscard]]
	constexpr auto cos(T x)
	    noexcept -> T
	{
        return Cosine< T, N >()(x);
    }
}

// x!
template< typename T >
[[nodiscard]]
constexpr auto factorial(T x)
    noexcept -> T
{
    return internal::factorial(x);
}

// x^e
template< typename T, typename E >
[[nodiscard]]
constexpr auto power(T x, E e)
    noexcept -> T
{
    return internal::power(x, e);
}

// sin(x)
template< typename T, std::size_t N = 10 >
[[nodiscard]]
constexpr auto sin(T x)
    noexcept -> T
{
    return internal::sin< T, N >(x);
}

// cos(x)
template< typename T, std::size_t N = 10 >
[[nodiscard]]
constexpr auto cos(T x)
    noexcept -> T
{
    return internal::cos< T, N >(x);
}

auto main()
	-> int
{
    constexpr auto sin_0  = sin(0.0);
    constexpr auto cos_0  = cos(0.0);
    constexpr auto sin_pi = sin(3.14159265359);
    constexpr auto cos_pi = cos(3.14159265359);
    
    std::cout << sin_0  << std::endl;
    std::cout << cos_0  << std::endl;
    std::cout << sin_pi << std::endl;
    std::cout << cos_pi << std::endl;
    
    return 0;
}
