// std::clamp
#include <algorithm>
// std::size_t
#include <cstddef>
// std::uint32_t
#include <cstdint>
// std::cout
// std::endl
#include <iostream>

using F32 = float;
using U32 = std::uint32_t;

template< std::size_t QuantumSize >
[[nodiscard]]
constexpr auto QuantizeSNorm(F32 x)
    noexcept -> F32
{
    static_assert(QuantumSize <= 16u);
    constexpr U32 mx = 1u << (QuantumSize - 1u);
    const F32 nx = std::clamp(x + 0.5f / mx, -1.0f, 1.0f);
    const U32 ux = U32(((nx >= 0.0) ? mx - 1u : mx) * nx + mx);
    return (F32(ux) - mx) / ((ux >= mx - 1u) ? mx - 1u : mx);
}

template< std::size_t QuantumSize >
[[nodiscard]]
constexpr auto QuantizeUNorm(F32 x)
    noexcept -> F32
{
    static_assert(QuantumSize <= 16u);
    constexpr U32 mx = 1u << QuantumSize;
    const F32 nx = std::clamp(x + 0.5f / mx, 0.0f, 1.0f);
    const U32 ux = U32((mx - 1u) * nx);
    return F32(ux) / (mx - 1u);
}

auto main()
	-> int
{
    std::cout << QuantizeUNorm< 8u >( 0.0f) << " , ";
    std::cout << QuantizeUNorm< 8u >( 0.5f) << " , ";
    std::cout << QuantizeUNorm< 8u >( 1.0f) << std::endl;
    
    std::cout << QuantizeSNorm< 8u >(-1.0f) << " , "; 
    std::cout << QuantizeSNorm< 8u >(-0.5f) << " , ";
    std::cout << QuantizeSNorm< 8u >( 0.0f) << " , ";
    std::cout << QuantizeSNorm< 8u >( 0.5f) << " , ";
    std::cout << QuantizeSNorm< 8u >( 1.0f) << std::endl;
    
    return 0;
}
