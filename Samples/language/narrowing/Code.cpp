// std::bitset
#include <bitset>
// std::int16_t
// std::int8_t
// std::uint16_t
// std::uint8_t
#include <cstdint>
// std::cout
#include <iostream>

auto main()
    -> int
{
    {
        constexpr std::int16_t src = -3;
        const std::bitset< 16u > src_bits(src);
        std::cout << src_bits << '\n';

        constexpr std::uint16_t dst = src;
        const std::bitset< 16u > dst_bits(dst);
        std::cout << dst_bits << '\n';
    }
    {
        constexpr std::uint16_t src = -3;
        const std::bitset< 16u > src_bits(src);
        std::cout << src_bits << '\n';

        constexpr std::int16_t dst = src;
        const std::bitset< 16u > dst_bits(dst);
        std::cout << dst_bits << '\n';
    }
    
    {
        constexpr std::int16_t src = -3;
        const std::bitset< 16u > src_bits(src);
        std::cout << src_bits << '\n';

        constexpr std::uint8_t dst = src;
        const std::bitset< 8u > dst_bits(dst);
        std::cout << "........" << dst_bits << '\n';
    }
    {
        constexpr std::uint16_t src = -3;
        const std::bitset< 16u > src_bits(src);
        std::cout << src_bits << '\n';

        constexpr std::int8_t dst = src;
        const std::bitset< 8u > dst_bits(dst);
        std::cout << "........" << dst_bits << '\n';
    }
   
    return 0;
}
