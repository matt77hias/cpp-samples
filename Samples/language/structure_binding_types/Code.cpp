// std::same_as
#include <concepts>
// std::tuple
#include <tuple>

auto main()
    -> int
{
    int a = {};
    std::tuple< int, const int, int&, const int& > t = { a, a, a, a };
    
    {
        auto [t0, t1, t2, t3] = t;
        static_assert(std::same_as< decltype(t0), int >);
        static_assert(std::same_as< decltype(t1), const int >);
        static_assert(std::same_as< decltype(t2), int& >);
        static_assert(std::same_as< decltype(t3), const int& >);
    }
    {
        const auto [t0, t1, t2, t3] = t;
        static_assert(std::same_as< decltype(t0), const int >);
        static_assert(std::same_as< decltype(t1), const int >);
        static_assert(std::same_as< decltype(t2), int& >);
        static_assert(std::same_as< decltype(t3), const int& >);
    }
    {
        auto& [t0, t1, t2, t3] = t;
        static_assert(std::same_as< decltype(t0), int >);
        static_assert(std::same_as< decltype(t1), const int >);
        static_assert(std::same_as< decltype(t2), int& >);
        static_assert(std::same_as< decltype(t3), const int& >);
    }
    {
        const auto& [t0, t1, t2, t3] = t;
        static_assert(std::same_as< decltype(t0), const int >);
        static_assert(std::same_as< decltype(t1), const int >);
        static_assert(std::same_as< decltype(t2), int& >);
        static_assert(std::same_as< decltype(t3), const int& >);
    }
    {
        auto&& [t0, t1, t2, t3] = t;
        static_assert(std::same_as< decltype(t0), int >);
        static_assert(std::same_as< decltype(t1), const int >);
        static_assert(std::same_as< decltype(t2), int& >);
        static_assert(std::same_as< decltype(t3), const int& >);
    }
    {
        //const auto&& [t0, t1, t2, t3] = t;
    }
    
    return 0;
}
