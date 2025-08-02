// std::same_as
#include <concepts>

template< typename T >
concept Check = requires(const T t)
{ 
   { t.Get() } noexcept -> std::same_as< int >;
};

struct Foo
{

public:
    auto Get() const noexcept -> int;
};

struct Bar
{

protected:
    auto Get() const noexcept -> int;
};

struct Baz
{

private:
    auto Get() const noexcept -> int;
};

static_assert(Check< Foo >);
static_assert(not Check< Bar >);
static_assert(not Check< Baz >);


auto main()
    -> int
{
    return 0;
}
