// uint16_t, uint8_t
#include <cstdint>

int main()
{
    constexpr std::uint16_t src = 0b11111111'01010101u;
    constexpr std::uint8_t  dst = 0b01010101u;
    
    static_assert(dst == static_cast< std::uint8_t >(src));
    
    return 0;
}
