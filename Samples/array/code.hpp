#include <array>
#include <iostream>
#include <tuple>
#include <utility>

namespace details {

    template< typename ActionT, typename FromT, size_t...I >
    constexpr decltype(auto) TransformArray(ActionT action, 
                                            const std::array< FromT, sizeof...(I) >& a,
                                            std::index_sequence< I... >) {

        using ToT = decltype(std::declval< ActionT >()(std::declval< FromT >()));
        return std::array< ToT, sizeof...(I) >{ action(a[I])... };
    }

    template< typename T, size_t...I >
    constexpr decltype(auto) FillArray(T value, std::index_sequence< I... >) {
        return std::array< T, sizeof...(I) >{ (static_cast< void >(I), value)... };
    }

    template< size_t ToN, typename T, size_t...I >
    constexpr decltype(auto) EnlargeArray(const std::array< T, sizeof...(I) >& a,
                                          std::index_sequence< I... >) {

        return std::array< T, ToN >{ a[I]... };
    }

    template< typename T, typename TupleT, std::size_t... I >
    constexpr decltype(auto) TuppleToArray(const TupleT& t, 
                                           std::index_sequence< I... >) {

        return std::array< T, sizeof...(I) >{ std::get< I >(t)... };
    }
}

template< typename ActionT, typename FromT, size_t N >
constexpr decltype(auto) TransformArray(ActionT action,
                                        const std::array< FromT, N >& a) {

    return details::TransformArray(std::move(action), a,
                                   std::make_index_sequence< N >());
}

template< typename ToT, typename FromT, size_t N >
constexpr decltype(auto) StaticCastArray(const std::array< FromT, N >& a) {
    constexpr auto f = [](const FromT& v) {
        return static_cast< ToT >(v); 
    };
    return TransformArray(f, a);
}

template< typename ToT, typename FromT, size_t N >
constexpr decltype(auto) DynamicCastArray(const std::array< FromT, N >& a) {
    constexpr auto f = [](const FromT& v) {
        return dynamic_cast< ToT >(v); 
    };
    return TransformArray(f, a);
}

template< typename ToT, typename FromT, size_t N >
constexpr decltype(auto) ConstCastArray(const std::array< FromT, N >& a) {
    constexpr auto f = [](const FromT& v) {
        return const_cast< ToT >(v); 
    };
    return TransformArray(f, a);
}

template< typename ToT, typename FromT, size_t N >
constexpr decltype(auto) ReinterpretCastArray(const std::array< FromT, N >& a) {
    constexpr auto f = [](const FromT& v) {
        return reinterpret_cast< ToT >(v); 
    };
    return TransformArray(f, a);
}

template< typename T, size_t N >
constexpr decltype(auto) FillArray(T value) {
    return details::FillArray(value, std::make_index_sequence< N >());
}

template< size_t ToN, typename T, size_t FromN >
constexpr decltype(auto) EnlargeArray(const std::array< T, FromN >& a) {
    return details::EnlargeArray< ToN >(a, std::make_index_sequence< FromN >());
}

template< typename T, typename... Ts >
constexpr decltype(auto) TuppleToArray(const std::tuple< T, Ts... >& t) {
    constexpr auto N = sizeof...(Ts) + 1u;
    return details::TuppleToArray< T >(t, std::make_index_sequence< N >());
}

namespace details {

    template< typename T, size_t...I >
    constexpr decltype(auto) ArrayToTupple(const std::array< T, sizeof...(I) >& a, 
                                           std::index_sequence< I... >) noexcept {
        return std::make_tuple(a[I]...);
    }
}

template< typename T, size_t N >
constexpr decltype(auto) ArrayToTupple(const std::array< T, N >& a) noexcept {
    return details::ArrayToTupple(a, std::make_index_sequence< N >());
}

template< typename... ArgsT >
constexpr decltype(auto) ArgsToTuple(ArgsT&&... args) noexcept {
    return std::make_tuple(std::forward< ArgsT >(args)...);
}

template< typename T, size_t N, 
          typename = std::enable_if_t< (N != 1) > >  
struct Array : std::array< T, N > {

    constexpr Array() noexcept
        : std::array< T, N >{} {}

    template< typename... ArgsT, 
    typename = std::enable_if_t< (N == sizeof...(ArgsT)) > >
        constexpr Array(ArgsT&&... args) noexcept
        : std::array< T, N >{ std::forward< ArgsT >(args)... } {}

    template< size_t FromN, 
    typename = std::enable_if_t< (FromN < N) > >
        constexpr Array(const Array< T, FromN >& a) noexcept
        : std::array< T, N >(EnlargeArray< N >(a)) {}

    template< size_t FromN, typename... ArgsT, 
    typename = std::enable_if_t< (FromN < N && (FromN + sizeof...(ArgsT)) == N) > >
        constexpr Array(const Array< T, FromN >& a, ArgsT&&... args) noexcept
        : std::array< T, N >(TuppleToArray(
            std::tuple_cat(ArrayToTupple(a), ArgsToTuple(std::forward< ArgsT >(args)...)))) {}

    constexpr Array(const Array& a) noexcept = default;

    constexpr Array(Array&& a) noexcept = default;

    template< typename U >
    constexpr explicit Array(const Array< U, N >& a) noexcept
    : std::array< T, N >(StaticCastArray< T >(a)) {}

    ~Array() = default;

    constexpr Array& operator=(const Array& a) noexcept = default;

    constexpr Array& operator=(Array&& a) noexcept = default;
    
    constexpr std::enable_if_t< ( 1 <= N ), T& > GetX() noexcept {
        return std::array< T, N >::operator[](0);
    }
    constexpr std::enable_if_t< ( 2 <= N ), T& > GetY() noexcept {
        return std::array< T, N >::operator[](1);
    }
    constexpr std::enable_if_t< ( 3 <= N ), T& > GetZ() noexcept {
        return std::array< T, N >::operator[](2);
    }
    constexpr std::enable_if_t< ( 4 <= N ), T& > GetW() noexcept {
        return std::array< T, N >::operator[](3);
    }
    
    constexpr std::enable_if_t< ( 1 <= N ), const T& > GetX() const noexcept {
        return std::array< T, N >::operator[](0);
    }
    constexpr std::enable_if_t< ( 2 <= N ), const T& > GetY() const noexcept {
        return std::array< T, N >::operator[](1);
    }
    constexpr std::enable_if_t< ( 3 <= N ), const T& > GetZ() const noexcept {
        return std::array< T, N >::operator[](2);
    }
    constexpr std::enable_if_t< ( 4 <= N ), const T& > GetW() const noexcept {
        return std::array< T, N >::operator[](3);
    }
};

template< typename T, std::size_t N >
std::ostream& operator<<(std::ostream& os, const std::array< T, N >& a) {
    for (auto i : a) { os << i << ' '; }
    return os << '\n';
}

int main() {
    constexpr Array< float, 5 > a;
    std::cout << a;
  
    constexpr Array< float, 5 > b( 1.5f, 2.5f, 3.5f, 4.5f, 5.5f );
    std::cout << b;
    
    constexpr Array< float, 5 > c{ 1.5f, 2.5f, 3.5f, 4.5f, 5.5f };
    std::cout << c;
    
    constexpr Array< float, 6 > d(c);
    std::cout << d;
    
    constexpr Array< float, 6 > e(d);
    std::cout << e;
    
    constexpr Array< int, 6 > f(e);
    std::cout << f;
    
    std::cout << f.GetW();
    
    return 0;
}
