struct Base
{
    explicit operator int () const noexcept { return 7; }
};

struct Derived : Base
{
    using Base::operator int;
};

int main()
{
    return static_cast< int >(Derived{});
}
