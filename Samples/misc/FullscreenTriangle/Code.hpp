// cout, endl
#include <iostream>

using uint = unsigned int;

float getX(uint i)
{
    return ((i & 2u) << 1u) - 1.0f;
}
float getY(uint i)
{
    return ((i & 1u) << 2u) - 1.0f;
}

int main()
{
    for (uint i = 0u; i < 3u; ++i)
    {
        std::cout << getX(i) << "," << getY(i) << std::endl;
    }
}
