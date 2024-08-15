struct A
{
    enum ScopedEnum
    {
        Huey,
        Dewey,
        Louie
    };

    enum UnscopedEnum
    {
        UnscopedEnum_Huey,
        UnscopedEnum_Dewey,
        UnscopedEnum_Louie
    };
};

struct B
{
    using ScopedEnum = A::ScopedEnum;

    using UnscopedEnum = A::UnscopedEnum;
};

[[maybe_unused]] constexpr auto a = B::ScopedEnum::Huey;
//[[maybe_unused]] constexpr auto b = B::UnscopedEnum_Huey;

struct C
{
    using ScopedEnum = A::ScopedEnum;

    using UnscopedEnum = A::UnscopedEnum;
    
    static constexpr auto UnscopedEnum_Huey = A::UnscopedEnum_Huey;
    static constexpr auto UnscopedEnum_Dewey = A::UnscopedEnum_Dewey;
    static constexpr auto UnscopedEnum_Louie = A::UnscopedEnum_Louie;
};

[[maybe_unused]] constexpr auto c = C::ScopedEnum::Huey;
[[maybe_unused]] constexpr auto d = C::UnscopedEnum_Huey;

struct D
{
    using ScopedEnum = A::ScopedEnum;

    using enum A::UnscopedEnum; // C++20
};

[[maybe_unused]] constexpr auto e = D::ScopedEnum::Huey;
[[maybe_unused]] constexpr auto f = D::UnscopedEnum_Huey;

auto main()
	noexcept -> int
{
    return 0;
}
