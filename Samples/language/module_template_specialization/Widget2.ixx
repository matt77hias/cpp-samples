export module Widget2;

import Widget;

export
namespace mage
{
	struct Foobar
	{};
}

namespace mage::internal
{
	template<>
	struct Type< Foobar >
	{
		using type = int;
	};
}
