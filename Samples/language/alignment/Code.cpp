// cout, endl
#include <iostream>

struct A
{
    float m_data[3] = {};
};

int main()
{
    std::cout << alignof(A) << std::endl;
    std::cout <<  sizeof(A) << std::endl;

    return 0;
}
