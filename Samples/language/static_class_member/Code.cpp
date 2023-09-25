struct Base
{
    [[nodiscard]]
    static consteval auto f()
        noexcept -> bool
    {
        return true;
    }
};

struct Derived : Base
{};

template< typename T >
concept Concept = T::f();

static_assert(Derived::f());
static_assert(Concept< Derived >);

auto main()
    -> int
{
    return 0;
}
