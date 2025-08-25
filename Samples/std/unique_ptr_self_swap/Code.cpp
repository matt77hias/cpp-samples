// std::unique_ptr
#include <memory>

auto main()
	-> int
{
    std::unique_ptr< int > ptr(new int{});

    ptr.swap(ptr);

    return ptr != nullptr;
}
