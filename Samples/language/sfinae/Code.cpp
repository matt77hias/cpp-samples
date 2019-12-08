// cout, endl
#include <iostream>
// string
#include <string>

struct A {};

[[nodiscard]]
std::string ToString(const A&)
{
    return "ToString(const A&)";
}

struct B
{
    [[nodiscard]]
    std::string Serialize() const
    {
        return "B::Serialize()";
    }
};

struct C
{
    std::string serialize;
};

[[nodiscard]]
std::string ToString(const C&)
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
    static constexpr Yes Test(IsMatch< std::string (U::*)(), &U::Serialize >*) noexcept
    {
        return {};
    }
    
    template< typename U > 
    static constexpr Yes Test(IsMatch< std::string (U::*)() const, &U::Serialize >*) noexcept
    {
        return {};
    }
    
    template< typename U > 
    static constexpr No Test(...) noexcept
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
typename enable_if< HasSerializeMemberMethod< T >::value, std::string >::type Serialize(const T& v)
{
    return v.Serialize();
}

template< typename T >
[[nodiscard]]
typename enable_if< !HasSerializeMemberMethod< T >::value, std::string >::type Serialize(const T& v)
{
    return ToString(v);
}

int main()
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
