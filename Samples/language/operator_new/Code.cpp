// size_t
#include <cstddef>
// cout, endl
#include <iostream>
// logic_error
#include <stdexcept>

struct A 
{};

struct B
{
   B()
   {
   	   throw std::logic_error("Called: B::B()");
   }

   B(int i)
   : m_i(i)
   {}

   int m_i = {};
};

B g_b(0);

[[nodiscard]]
auto operator new(std::size_t size, A)
   -> void*
{
    std::cout << "Called: void* operator new(std::size_t size, A)" << std::endl;
    std::cout << "Size: " << size << std::endl;
    return &g_b;
}

[[nodiscard]]
auto operator new [](std::size_t size, A)
   -> void*
{
    std::cout << "Called: void* operator new[](std::size_t size, A)" << std::endl;
    std::cout << "Size: " << size << std::endl;
    return &g_b;
}

void operator delete(void* ptr)
   noexcept
{
    if (ptr == &g_b) 
    {
        std::cout << "Called: delete(void* ptr)" << std::endl;
    }
}

void operator delete(void* ptr, A)
   noexcept
{
    if (ptr == &g_b) 
    {
        std::cout << "Called: delete(void* ptr, A)" << std::endl;
    }   
}

void operator delete [](void* ptr)
   noexcept
{
    if (ptr == &g_b) 
    {
        std::cout << "Called: delete [](void* ptr)" << std::endl;
    }
}

void operator delete [](void* ptr, A)
   noexcept
{
    if (ptr == &g_b) 
    {
        std::cout << "Called: delete [](void* ptr, A)" << std::endl;
    }
}

auto main()
   -> int
{
   A a;
   try { const auto b1 = new (a) B; }    catch (...) {}
   try { const auto b2 = new (a) B[5]; } catch (...) {}

   return 0;
}
