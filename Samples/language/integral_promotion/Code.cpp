// same_as
#include <concepts>

auto main()
   -> int
{
	[[maybe_unused]] unsigned short a = 0;
    [[maybe_unused]] unsigned short b = 1;
    [[maybe_unused]] auto c = a + b;
    
    // static_assert(std::same_as< decltype(c), unsigned short >);
    static_assert(std::same_as< decltype(c), int >);

    return 0;
}
