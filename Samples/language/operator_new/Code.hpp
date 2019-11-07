// size_t
#include <cstddef>
// cout, endl
#include <iostream>

struct A 
{};

struct B
{
    int i;
};

B g_b;

[[nodiscard]]
void* operator new(std::size_t size, A)
{
    std::cout << "Called: void* operator new(std::size_t size, A)" << std::endl;
    std::cout << "Size: " << size << std::endl;
    return &g_b;
}

[[nodiscard]]
void* operator new[](std::size_t size, A)
{
    std::cout << "Called: void* operator new(std::size_t size, A)" << std::endl;
    std::cout << "Size: " << size << std::endl;
    return &g_b;
}

int main()
{
   A a;
   const auto b1 = new (a) B;
   const auto b2 = new (a) B[5];
   return 0;
}
