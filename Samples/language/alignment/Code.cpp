// std::cout
// std::endl
#include <iostream>

struct A
{
    float m_data[3] = {};
};

auto main()
    -> int
{
    std::cout << alignof(A) << std::endl;
    std::cout <<  sizeof(A) << std::endl;

    return 0;
}
