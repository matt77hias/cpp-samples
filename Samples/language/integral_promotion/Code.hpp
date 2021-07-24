// same_as
#include <concepts>

int main()
{
	unsigned short a = 0;
    unsigned short b = 1;
    auto c = a + b;
    
    // static_assert(std::same_as< decltype(c), unsigned short >);
    static_assert(std::same_as< decltype(c), int >);

    return 0;
}
