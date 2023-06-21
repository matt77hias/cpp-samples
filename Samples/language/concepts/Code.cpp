// size_t
#include <cstddef>
// make_unique, unique_ptr
#include <memory>
// is_array, is_array_v, enable_if, enable_if_t, extent, extent_v
#include <type_traits>
// forward
#include <utility>

// C++11 <=
namespace v0
{
    template< typename T,
		      typename... ConstructorArgsT,
		      typename std::enable_if< !std::is_array< T >::value, int >::type = 0 >
	inline auto MakeUnique(ConstructorArgsT&&... args)
		-> std::unique_ptr< T >
    {
        return std::make_unique< T >(std::forward< ConstructorArgsT >(args)...); // C++14
    }

	template< typename T,
		      typename... ConstructorArgsT,
		      typename std::enable_if< (std::extent< T >::value != 0u), int >::type = 0 >
	auto MakeUnique(ConstructorArgsT&&... args)
		-> std::unique_ptr< T > = delete;

	template< typename T,
		      typename std::enable_if< std::is_array< T >::value && (std::extent< T >::value == 0u), int >::type = 0 >
	inline auto MakeUnique(std::size_t size)
		-> std::unique_ptr< T >
    {
        return std::make_unique< T >(size); // C++14
    }
}

// C++14 <=
namespace v1
{
    template< typename T,
		      typename... ConstructorArgsT,
		      std::enable_if_t< !std::is_array_v< T >, int > = 0 >
	inline auto MakeUnique(ConstructorArgsT&&... args)
		-> std::unique_ptr< T >
    {
        return std::make_unique< T >(std::forward< ConstructorArgsT >(args)...);
    }

	template< typename T,
		      typename... ConstructorArgsT,
		      std::enable_if_t< (std::extent_v< T > != 0u), int > = 0 >
	auto MakeUnique(ConstructorArgsT&&... args)
		-> std::unique_ptr< T > = delete;

	template< typename T,
		      std::enable_if_t< std::is_array_v< T > && (std::extent_v< T > == 0u), int > = 0 >
	inline auto MakeUnique(std::size_t size)
		-> std::unique_ptr< T >
    {
        return std::make_unique< T >(size);
    }
}

// C++20 <=
namespace v2
{
    template< typename T, typename... ConstructorArgsT >
	requires (std::is_array_v< T > == false)
	[[nodiscard]]
	inline auto MakeUnique(ConstructorArgsT&&... args)
		-> std::unique_ptr< T >
    {
        return std::make_unique< T >(std::forward< ConstructorArgsT >(args)...);
    }

	template< typename T, typename... ConstructorArgsT >
	requires (std::extent_v< T > != 0u)
	[[nodiscard]]
	auto MakeUnique(ConstructorArgsT&&... args)
		-> std::unique_ptr< T > = delete;

	template< typename T >
	requires (std::is_array_v< T > && (std::extent_v< T > == 0u))
	[[nodiscard]]
	inline auto MakeUnique(std::size_t size)
		-> std::unique_ptr< T >
    {
        return std::make_unique< T >(size);
    }
}

// C++20 <=
namespace v3
{
    template < typename T >
    concept Array = std::is_array< T >::value;
    
    template < typename T >
    concept NonArray = !std::is_array< T >::value;

    template < typename T >
    concept StackArray = Array< T > && (std::extent_v< T > != 0u);

    template < typename T >
    concept HeapArray = Array< T > && (std::extent_v< T > == 0u);
    
    template< NonArray T, typename... ConstructorArgsT >
	[[nodiscard]]
	inline auto MakeUnique(ConstructorArgsT&&... args)
		-> std::unique_ptr< T >
    {
        return std::make_unique< T >(std::forward< ConstructorArgsT >(args)...);
    }

	template< StackArray T, typename... ConstructorArgsT >
	[[nodiscard]]
	auto MakeUnique(ConstructorArgsT&&... args)
		-> std::unique_ptr< T > = delete;

	template< HeapArray T >
	[[nodiscard]]
	inline auto MakeUnique(std::size_t size)
		-> std::unique_ptr< T >
    {
        return std::make_unique< T >(size);
    }
}

int main()
{
   auto p0 = v0::MakeUnique< int[] >(16u);
   auto p1 = v1::MakeUnique< int[] >(16u);
   auto p2 = v2::MakeUnique< int[] >(16u);
   auto p3 = v3::MakeUnique< int[] >(16u);

   return 0;
}
