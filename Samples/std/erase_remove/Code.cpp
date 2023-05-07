// remove_if
#include <algorithm>
// cout, endl
#include <iostream>
// vector
#include <vector>

struct A
{
    constexpr A(int a)
		noexcept
        : m_a(a) {}
    
    constexpr A(const A&)
		noexcept = default;
    
    constexpr A(A&&)
		noexcept = default;
    
    ~A()
		noexcept
    {
        std::cout << "Destruction: " << m_a << std::endl;
    }
    
    auto operator =(const A& a)
		noexcept -> A&
    {
        std::cout << "Copy assignment: " << a.m_a << std::endl;
        m_a = a.m_a;
        return *this;
    }
    
    auto operator =(A&& a)
		noexcept -> A&
    {
        std::cout << "Move assignment: " << a.m_a << std::endl;
        m_a = a.m_a;
        return *this;
    }
    
    int m_a;
};


auto main()
	-> int
{
    std::vector< A > v = { 1, 2, 5, 4, 5, 5 };
    
    std::cout << "BEGIN REMOVE" << std::endl;
    const auto end = std::remove_if(v.begin(), v.end(), [](const A& a) noexcept { return 5 == a.m_a; });
    std::cout << "BEGIN ERASE" << std::endl;
    v.erase(end, v.end());
    std::cout << "END" << std::endl;

    return 0;
}
