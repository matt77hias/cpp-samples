// size_t
#include <cstddef>
// uintptr_t
#include <cstdint>
// free, malloc
#include <cstdlib>
// cout, endl
#include <iostream>

bool g_logging = false;

[[nodiscard]]
void* operator new(std::size_t size)
{
    const auto ptr = std::malloc(size);
    
    if (g_logging)
    {
        std::cout << "Allocated: " << (uintptr_t)ptr << std::endl;
    }

    return ptr;
}

void operator delete(void* ptr) noexcept
{
    if (g_logging)
    {
       std::cout << "Deallocated: " << (uintptr_t)ptr << std::endl; 
    }

    std::free(ptr);
}

struct A
{
    ~A()
    {
       std::cout << "A::~A()" << std::endl; 
    } 

    virtual void f() {}
};

struct B : A
{
    ~B()
    {
       std::cout << "B::~B()" << std::endl; 
    }
};

auto main()
    -> int
{
    std::cout << sizeof(A) << std::endl;
    std::cout << sizeof(B) << std::endl;
    
    g_logging = true;
    A* a = new B();
    delete a;
    g_logging = false;
    
    return 0;
}
