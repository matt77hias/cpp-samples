export module Widget;

export
namespace mage::internal
{
	template< typename T >
	struct Type;
}

export
namespace mage
{
	template< typename T >
	using Type = internal::Type< T >::type;
}

namespace mage::internal
{
	template<>
	struct Type< int >
	{
		using type = int;
	};
}
