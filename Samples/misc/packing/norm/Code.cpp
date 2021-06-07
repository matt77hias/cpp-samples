// clamp
#include <algorithm>
// int8_t, uint32_t, uint8_t
#include <cstdint>
// cout, endl
#include <iostream>

using F32 = float;
using S8  = std::int8_t;
using U8  = std::uint8_t;
using U32 = std::uint32_t;

constexpr S8 F32ToSNorm(F32 x) noexcept
{
    const auto nx = std::clamp(x, -1.0f, 1.0f);
    return S8(((nx >= 0.0f) ? 127.0f : 128.0f) * nx);
}

constexpr U8 F32ToUNorm(F32 x) noexcept
{
    const auto nx = std::clamp(x, 0.0f, 1.0f);
    return U8(255.0f * nx);
}

constexpr U8 F32ToSUNorm(F32 x) noexcept
{
    const auto nx = std::clamp(x, -1.0f, 1.0f);
    return U8(128.0f + ((nx >= 0) ? 127.0f : 128.0f) * nx);
}

constexpr F32 SNormToF32(S8 x) noexcept
{
    return F32(x) / ((x >= 0) ? 127.0f : 128.0f);
}

constexpr F32 UNormToF32(U8 x) noexcept
{
    return F32(x) / 255.0f;
}

constexpr F32 SUNormToF32(U8 x) noexcept
{
    return (F32(x) - 128.0f) / ((x >= 127u) ? 127.0f : 128.0f);
}

int main()
{ 
    std::cout << (int) F32ToSNorm(-1.0f) << " , " << (int) F32ToSNorm(1.0f) << std::endl;
    std::cout << (int) F32ToUNorm( 0.0f) << " , " << (int) F32ToUNorm(1.0f) << std::endl;
    std::cout << (int)F32ToSUNorm(-1.0f) << " , " << (int)F32ToSUNorm(1.0f) << std::endl;
    
    std::cout <<  SNormToF32(S8(-128)) << " , " <<  SNormToF32(S8(127)) << std::endl;
    std::cout <<  UNormToF32(U8(0))    << " , " <<  UNormToF32(U8(255)) << std::endl;
    std::cout << SUNormToF32(U8(0))    << " , " << SUNormToF32(U8(255)) << std::endl;
    
    return 0;
}
