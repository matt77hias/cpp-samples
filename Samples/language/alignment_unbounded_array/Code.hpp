struct alignas(4u) A
{};

int main()
{
    return static_cast< int >(alignof(A[]));
}
