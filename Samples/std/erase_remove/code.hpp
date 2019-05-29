#include <algorithm>
#include <iostream>
#include <vector>

struct A {
    constexpr A(int a) noexcept : m_a(a) {}
    constexpr A(const A&) noexcept = default;
    constexpr A(A&&) noexcept = default;
    ~A() noexcept {
        std::cout << "Destruction: " << m_a << std::endl;
    }
    A& operator=(const A& a) noexcept {
        std::cout << "Copy assignment: " << a.m_a << std::endl;
        m_a = a.m_a;
        return *this;
    }
    A& operator=(A&& a) noexcept {
        std::cout << "Move assignment: " << a.m_a << std::endl;
        m_a = a.m_a;
        return *this;
    }
    
    int m_a;
};


int main() {
    std::vector< A > v = { 1, 2, 5, 4, 5, 5 };
    std::cout << "BEGIN REMOVE" << std::endl;
    auto end = std::remove_if(v.begin(), v.end(), [](const A& a) noexcept { return 5 == a.m_a; });
    std::cout << "BEGIN ERASE" << std::endl;
    v.erase(end, v.end());
    std::cout << "END" << std::endl;
    return 0;
}
