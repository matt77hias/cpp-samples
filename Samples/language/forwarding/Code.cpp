// std::cout
// std::endl
#include <iostream>
// std::forward_like
#include <type_traits>
// std::declval
#include <utility>

template< typename T, typename U >
using forward_like_t = decltype(std::forward_like< T, U >(std::declval< U >()));

struct Base
{};

void print(Base&)
{
    std::cout << "&" << std::endl;
}
void print(const Base&)
{
    std::cout << "const&" << std::endl;
}
void print(Base&&)
{
    std::cout << "&&" << std::endl;
}
void print(const Base&&)
{
    std::cout << "const&&" << std::endl;
}

struct Widget : Base
{
    template< typename SelfT >
    constexpr auto f(this SelfT&& self)
        noexcept
    {
        std::cout << "member variable" << std::endl;
        print(self.value);
        print(std::forward_like< SelfT >(self).value);
        print(std::forward_like< SelfT >(self.value));

        std::cout << "member method" << std::endl;
        print(self.get());
        print(std::forward_like< SelfT >(self).get());
        print(std::forward_like< SelfT >(self.get()));

        std::cout << "argument" << std::endl;
        print(self);
        print(std::forward_like< SelfT >(self));
    }
    
    template< typename SelfT >
    constexpr auto get(this SelfT&& self)
        noexcept -> decltype(auto)
    {
        return std::forward_like< SelfT >(self.value);
    }

    Base value = {};
};

auto main() -> int
{
    Widget w;
    std::cout << "=&=" << std::endl;
    w.f();
    std::cout << "=const&=" << std::endl;
    ((const Widget&)w).f();
    std::cout << "=&&=" << std::endl;
    ((Widget&&)w).f();
    std::cout << "=const&&=" << std::endl;
    ((const Widget&&)w).f();
    
    return 0;
}
