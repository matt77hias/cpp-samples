// cout, endl
#include <iostream>
// is_final_v, is_polymorphic_v
#include <type_traits>

template< typename T >
requires(std::is_polymorphic_v< T >)
[[nodiscard]]
constexpr auto most_derived_cast(T* ptr)
    noexcept -> void*
{
    if constexpr (std::is_final_v< T >)
    {
        return static_cast< void* >(ptr);
    }
    else
    {
        return dynamic_cast< void* >(ptr);
    }
}

template< typename T >
requires(std::is_polymorphic_v< T >)
[[nodiscard]]
constexpr auto most_derived_cast(const T* ptr)
    noexcept -> const void*
{
    if constexpr (std::is_final_v< T >)
    {
        return static_cast< const void* >(ptr);
    }
    else
    {
        return dynamic_cast< const void* >(ptr);
    }
}

struct A { virtual ~A() = default; };
struct B { virtual ~B() = default; };
struct C : A, B {};

auto main()
    -> int
{
    C* c = new C;
    std::cout << c << std::endl;
    
    A* a = c;
    std::cout << a << std::endl;
    B* b = c;
    std::cout << b << std::endl;

    std::cout << most_derived_cast(b) << std::endl;

    return 0;
}
