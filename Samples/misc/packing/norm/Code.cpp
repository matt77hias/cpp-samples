// std::clamp
#include <algorithm>
// std::int8_t
// std::uint32_t
// std::uint8_t
#include <cstdint>
// std::cout
// std::endl
#include <iostream>

using F32 = float;
using S8  = std::int8_t;
using U8  = std::uint8_t;
using U32 = std::uint32_t;

[[nodiscard]]
constexpr auto F32ToSNorm(F32 x)
	noexcept -> S8
{
    const auto nx = std::clamp(x, -1.0f, 1.0f);
    return S8(((nx >= 0.0f) ? 127.0f : 128.0f) * nx);
}

[[nodiscard]]
constexpr auto F32ToUNorm(F32 x)
	noexcept -> U8
{
    const auto nx = std::clamp(x, 0.0f, 1.0f);
    return U8(255.0f * nx);
}

[[nodiscard]]
constexpr auto F32ToSUNorm(F32 x)
	noexcept -> U8
{
    const auto nx = std::clamp(x, -1.0f, 1.0f);
    return U8(128.0f + ((nx >= 0) ? 127.0f : 128.0f) * nx);
}

[[nodiscard]]
constexpr auto SNormToF32(S8 x)
	noexcept -> F32
{
    return F32(x) / ((x >= 0) ? 127.0f : 128.0f);
}

[[nodiscard]]
constexpr auto UNormToF32(U8 x)
	noexcept -> F32
{
    return F32(x) / 255.0f;
}

[[nodiscard]]
constexpr auto SUNormToF32(U8 x)
	noexcept -> F32
{
    return (F32(x) - 128.0f) / ((x >= 127u) ? 127.0f : 128.0f);
}

auto main()
	-> int
{ 
    std::cout << (int) F32ToSNorm(-1.0f) << " , " << (int) F32ToSNorm(1.0f) << std::endl;
    std::cout << (int) F32ToUNorm( 0.0f) << " , " << (int) F32ToUNorm(1.0f) << std::endl;
    std::cout << (int)F32ToSUNorm(-1.0f) << " , " << (int)F32ToSUNorm(1.0f) << std::endl;
    
    std::cout <<  SNormToF32(S8(-128)) << " , " <<  SNormToF32(S8(127)) << std::endl;
    std::cout <<  UNormToF32(U8(0))    << " , " <<  UNormToF32(U8(255)) << std::endl;
    std::cout << SUNormToF32(U8(0))    << " , " << SUNormToF32(U8(255)) << std::endl;
    
    return 0;
}
