// size_t
#include <cstddef>
// uintptr_t
#include <cstdint>
// free, malloc
#include <cstdlib>
// cout, endl
#include <iostream>
// make_unique, unique_ptr
#include <memory>
// logic_error
#include <stdexcept>

bool g_logging = false;

[[nodiscard]]
auto operator new(std::size_t size)
	-> void*
{
    const auto ptr = std::malloc(size);
    
    if (g_logging)
    {
        std::cout << "Allocated: " << (uintptr_t)ptr << std::endl;
    }

    return ptr;
}

void operator delete(void* ptr)
	noexcept
{
    if (g_logging)
    {
       std::cout << "Deallocated: " << (uintptr_t)ptr << std::endl;
    }

    std::free(ptr);
}

struct A
{
    [[nodiscard]]
	A()
    {
        std::cout << "A::A()" << std::endl;
    }
    
    ~A()
    {
        std::cout << "A::~A()" << std::endl;
    }

    int m_data = {};
};

struct B
{
    [[nodiscard]]
	B()
    {
        std::cout << "B::B()" << std::endl;
        throw std::logic_error("This is a long string to avoid SSO.");
    }
    
    ~B()
    {
        std::cout << "B::~B()" << std::endl;
    }
    
    A m_a = {};
};

auto main()
    -> int
{ 
    g_logging = true;
    try { std::make_unique< B >(); } catch (...) {}
    
    return 0;
};
