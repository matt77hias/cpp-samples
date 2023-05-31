// bitset
#include <bitset>
// uint32_t
#include <cstdint>
// cout, endl
#include <iostream>

// even integer: 2a   -> (2a)^2   = 4a^2          -> even integer
//  odd integer: 2a+1 -> (2a+1)^2 = 4a^2 + 4a + 1 -> odd integer

// (2a)^n   = 2^n a^n      = [a^n << n]
// (2a+1)^n = (2a+1)(2b+1) = 4ab + 2(a+b) + 1 = [ab << 2] + [(a+b) << 1] + 1

[[nodiscard]]
auto IsEven(std::uint32_t x)
	noexcept -> bool
{
    std::cout << std::bitset< 32u >(x) << std::endl;
	
	switch (x)
    {
		case 0u:
			return true;
		case 1u:
			return false;
		default:
			return IsEven(x * x);
	}
}

auto main()
	-> int
{
    std::cout << std::boolalpha;
    
    std::cout << "Is 3 even?" << std::endl;
    const auto result3 = IsEven(3u);
	std::cout << result3 << std::endl;
    
    std::cout << "Is 4 even?" << std::endl;
    const auto result4 = IsEven(4u);
	std::cout << result4 << std::endl;

	return 0;
}
