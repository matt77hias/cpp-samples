struct A
{};

struct B : A
{};

struct C : B
{};

struct Base
{
    virtual auto Function(const B*)
        -> const B*;
};

struct Derived : Base
{
    auto Function(const B*) // const A* not allowed
        -> const C* override;
};

auto main()
    -> int
{
    return 0;
}
