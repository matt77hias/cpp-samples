// This does not compile.
#include <new>

consteval auto f()
{
    const auto ptr = operator new(16u);
    operator delete(ptr);

    return true;
}

auto main()
    -> int
{
    static_assert(f());

    return 0;
}
