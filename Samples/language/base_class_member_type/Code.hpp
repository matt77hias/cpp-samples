struct A
{
    using type = int;
};

struct B : A
{};

template< typename T >
constexpr void f(typename T::type value)
{}

int main()
{
    A::type a = {};
    B::type b = {};

    f< A >({});
    f< B >({});
    return 0;
}
