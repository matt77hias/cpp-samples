// unique_ptr
#include <memory>

int main()
{
    std::unique_ptr< int > ptr(new int{});

    ptr.swap(ptr);

    return ptr != nullptr;
}
