// std::cout
// std::endl
#include <iostream>
// std::string
#include <string>

struct A {};

[[nodiscard]]
auto ToString(const A&)
    -> std::string
{
    return "ToString(const A&)";
}

struct B
{
    [[nodiscard]]
    auto Serialize() const
        -> std::string
    {
        return "B::Serialize()";
    }
};

struct C
{
    std::string serialize;
};

[[nodiscard]]
auto ToString(const C&)
    -> std::string
{
    return "ToString(const C&)";
}

struct [[nodiscard]] Yes
{
    char m_ = 0;
};

struct [[nodiscard]] No
{
    char m_[2] = {}; 
};

static_assert(sizeof(Yes) != sizeof(No));

template< typename T >
struct HasSerializeMemberMethod
{

private:
    
    template< typename U, U ValueU > 
    struct IsMatch
    {};

    template< typename U > 
    static constexpr auto Test(IsMatch< std::string (U::*)(), &U::Serialize >*)
        noexcept -> Yes
    {
        return {};
    }
    
    template< typename U > 
    static constexpr auto Test(IsMatch< std::string (U::*)() const, &U::Serialize >*)
        noexcept -> Yes
    {
        return {};
    }
    
    template< typename U > 
    static constexpr auto Test(...)
        noexcept -> No
    {
        return {};
    }
    
public:
    
    static const bool value = (sizeof(Yes) == sizeof(Test< T >(nullptr)));
};

template< bool ConditionT, typename T = void >
struct enable_if
{};

template< typename T >
struct enable_if< true, T >
{
    using type = T;
};

template< typename T >
[[nodiscard]]
auto Serialize(const T& v)
    -> typename enable_if< HasSerializeMemberMethod< T >::value, std::string >::type
{
    return v.Serialize();
}

template< typename T >
[[nodiscard]]
auto Serialize(const T& v)
    -> typename enable_if< not HasSerializeMemberMethod< T >::value, std::string >::type
{
    return ToString(v);
}

auto main()
    -> int
{
    std::cout << HasSerializeMemberMethod< A >::value << std::endl;
    std::cout << HasSerializeMemberMethod< B >::value << std::endl;
    std::cout << HasSerializeMemberMethod< C >::value << std::endl;
    
    A a;
    B b;
    C c;

    std::cout << Serialize(a) << std::endl;
    std::cout << Serialize(b) << std::endl;
    std::cout << Serialize(c) << std::endl;
    
    return 0;
}
