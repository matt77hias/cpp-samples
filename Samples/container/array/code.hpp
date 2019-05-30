#include <array>
#include <iostream>
#include <tuple>
#include <utility>

namespace details {

	template< typename ActionT, typename FromT, size_t...I >
	[[nodiscard]]
	constexpr auto TransformArray(ActionT&& action, 
								  const std::array< FromT, sizeof...(I) >& a, 
								  std::index_sequence< I... >) {

		using ToT = decltype(std::declval< ActionT >()(std::declval< FromT >()));
		return std::array< ToT, sizeof...(I) >{ action(a[I])... };
	}

	template< typename T, size_t...I >
	[[nodiscard]]
	constexpr auto FillArray(const T& value, std::index_sequence< I... >) {
		return std::array< T, sizeof...(I) >{ (static_cast< void >(I), value)... };
	}

	template< size_t ToN, typename T, size_t...I >
	[[nodiscard]]
	constexpr auto EnlargeArray(const std::array< T, sizeof...(I) >& a, 
								std::index_sequence< I... >) {

		return std::array< T, ToN >{ a[I]... };
	}

	template< typename T, typename TupleT, std::size_t... I >
	[[nodiscard]]
	constexpr auto TuppleToArray(const TupleT& t, 
								 std::index_sequence< I... >) {

		return std::array< T, sizeof...(I) >{ std::get< I >(t)... };
	}

	template< typename T, size_t...I >
	[[nodiscard]]
	constexpr auto ArrayToTupple(const std::array< T, sizeof...(I) >& a,
								 std::index_sequence< I... >) {
		
		return std::make_tuple(a[I]...);
	}
}

template< typename ActionT, typename FromT, size_t N >
[[nodiscard]]
constexpr auto TransformArray(ActionT&& action, 
							  const std::array< FromT, N >& a) {
	
	return details::TransformArray(std::forward< ActionT >(action), a,
								   std::make_index_sequence< N >());
}

template< typename ToT, typename FromT, size_t N >
[[nodiscard]]
constexpr auto StaticCastArray(const std::array< FromT, N >& a) {
	constexpr auto f = [](const FromT& v) {
		return static_cast< ToT >(v); 
	};
	return TransformArray(f, a);
}

template< typename T, size_t N >
[[nodiscard]]
constexpr auto FillArray(const T& value) {
	return details::FillArray(value, std::make_index_sequence< N >());
}

template< size_t ToN, typename T, size_t FromN >
[[nodiscard]]
constexpr auto EnlargeArray(const std::array< T, FromN >& a) {
	return details::EnlargeArray< ToN >(a, std::make_index_sequence< FromN >());
}

template< typename T, typename... Ts >
[[nodiscard]]
constexpr auto TuppleToArray(const std::tuple< T, Ts... >& t) {
	constexpr auto N = sizeof...(Ts) + 1u;
	return details::TuppleToArray< T >(t, std::make_index_sequence< N >());
}

template< typename T, size_t N >
[[nodiscard]]
constexpr auto ArrayToTupple(const std::array< T, N >& a) {
	return details::ArrayToTupple(a, std::make_index_sequence< N >());
}

template< typename T, size_t N, size_t A = alignof(T), 
		  typename = std::enable_if_t< (N > 1) > >
struct alignas(A) Array : public std::array< T, N > {

public:

	constexpr Array() noexcept
		: std::array< T, N >{} {}

	constexpr explicit Array(const T& value) noexcept
		: std::array< T, N >(FillArray< T, N >(value)) {}

	template< typename... ArgsT, 
			  typename = std::enable_if_t< (N == sizeof...(ArgsT)) > >
	constexpr Array(ArgsT&&... args) noexcept
		: std::array< T, N >{ std::forward< ArgsT >(args)... } {}

	template< size_t FromN, 
			  typename = std::enable_if_t< (FromN < N) > >
	constexpr Array(const Array< T, FromN, A >& a) noexcept
		: std::array< T, N >(EnlargeArray< N >(a)) {}

	template< size_t FromN, size_t FromA,
			  typename = std::enable_if_t< (FromN < N && FromA != A) > >
	constexpr explicit Array(const Array< T, FromN, FromA >& a) noexcept
		: std::array< T, N >(EnlargeArray< N >(a)) {}

	template< size_t FromN, typename... ArgsT, 
			  typename = std::enable_if_t< (FromN < N && (FromN + sizeof...(ArgsT)) == N) > >
	constexpr Array(const Array< T, FromN, A >& a, ArgsT&&... args) noexcept
		: std::array< T, N >(TuppleToArray(std::tuple_cat(ArrayToTupple(a), 
							 std::make_tuple(std::forward< ArgsT >(args)...)))) {}
	
	template< size_t FromN, size_t FromA, typename... ArgsT, 
			  typename = std::enable_if_t< (FromN < N && (FromN + sizeof...(ArgsT)) == N && FromA != A) > >
	constexpr explicit Array(const Array< T, FromN, FromA >& a, ArgsT&&... args) noexcept
		: std::array< T, N >(TuppleToArray(std::tuple_cat(ArrayToTupple(a), 
							 std::make_tuple(std::forward< ArgsT >(args)...)))) {}

	constexpr Array(const Array& a) noexcept = default;
	
	constexpr Array(Array&& a) noexcept = default;

	template< typename FromT, size_t FromA, 
			  typename = std::enable_if_t< std::is_convertible_v< FromT, T > > >
	constexpr explicit Array(const Array< FromT, N, FromA >& a) noexcept
		: std::array< T, N >(StaticCastArray< T >(a)) {}

	~Array() = default;
	
	Array& operator=(const Array& a) noexcept = default;

	Array& operator=(Array&& a) noexcept = default;
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
    
    constexpr Array< float, 6 > e(c, 6.5f);
    std::cout << e;
    
    constexpr Array< int, 6 > f(e);
    std::cout << f;
    
    constexpr Array< int, 6 > g(5);
    std::cout << g;
    
    constexpr int h_value = 5;
    constexpr Array< int, 6 > h(h_value);
    std::cout << h;
    
    constexpr Array< Array< float, 5 >, 5 > i(c);
    std::cout << i;
    
    return 0;
}
