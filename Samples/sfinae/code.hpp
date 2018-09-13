#include <iostream>
#include <string>

struct A {};

const std::string ToString(const A&) {
    return "ToString(const A&)";
}

struct B {
    const std::string Serialize() const {
        return "B::Serialize()";
    }
};

struct C {
    const std::string serialize;
};

const std::string ToString(const C&) {
    return "ToString(const C&)";
}

struct Yes {
    char m_ = 0;
};
struct No {
    char m_[2] = {}; 
};

static_assert(sizeof(Yes) != sizeof(No));

template< typename T >
struct HasSerializeMemberMethod {

private:
    
    template< typename U, U ValueU > 
    struct IsMatch {};

    template< typename U > 
    static const Yes Test(IsMatch< const std::string (U::*)(), &U::Serialize >*) noexcept {
        return Yes();
    }
    
    template< typename U > 
    static const Yes Test(IsMatch< const std::string (U::*)() const, &U::Serialize >*) noexcept {
        return Yes();
    }
    
    template< typename U > 
    static const No Test(...) noexcept {
        return No();
    }
    
public:
    
    static const bool value = (sizeof(Yes) == sizeof(Test< T >(nullptr)));
};

template< bool ConditionT, typename T = void >
struct enable_if {};

template< typename T >
struct enable_if< true, T > { 
    using type = T; 
};

template< typename T > 
typename enable_if< HasSerializeMemberMethod< T >::value, std::string >::type Serialize(const T& v) {
    return v.Serialize();
}

template< typename T > 
typename enable_if< !HasSerializeMemberMethod< T >::value, std::string >::type Serialize(const T& v) {
    return ToString(v);
}

int main() {
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
