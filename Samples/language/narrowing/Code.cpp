// bitset
#include <bitset>
// int16_t, int8_t, uint16_t, uint8_t
#include <cstdint>
// cout
#include <iostream>

int main()
{
    {
        std::int16_t src = -3;
        std::bitset< 16u > src_bits(src);
        std::cout << src_bits << '\n';

        std::uint16_t dst = src;
        std::bitset< 16u > dst_bits(dst);
        std::cout << dst_bits << '\n';
    }
    {
        std::uint16_t src = -3;
        std::bitset< 16u > src_bits(src);
        std::cout << src_bits << '\n';

        std::int16_t dst = src;
        std::bitset< 16u > dst_bits(dst);
        std::cout << dst_bits << '\n';
    }
    
    {
        std::int16_t src = -3;
        std::bitset< 16u > src_bits(src);
        std::cout << src_bits << '\n';

        std::uint8_t dst = src;
        std::bitset< 8u > dst_bits(dst);
        std::cout << "........" << dst_bits << '\n';
    }
    {
        std::uint16_t src = -3;
        std::bitset< 16u > src_bits(src);
        std::cout << src_bits << '\n';

        std::int8_t dst = src;
        std::bitset< 8u > dst_bits(dst);
        std::cout << "........" << dst_bits << '\n';
    }
   
    return 0;
}
