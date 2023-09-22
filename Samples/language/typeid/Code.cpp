// for_each
#include <algorithm>
// cout, endl
#include <iostream>
// type_index
#include <typeindex>
// unordered_multimap
#include <unordered_map>
// vector
#include <vector>

struct Component
{
    virtual ~Component() = default;
};

struct A : Component
{};
struct B : Component
{};

struct Node
{
    template< typename ComponentT >
    [[nodiscard]]
	auto Has() const
		noexcept -> bool
    {
		return m_components.find(typeid(ComponentT)) != m_components.cend();
	}

	template< typename ComponentT >
    [[nodiscard]]
	auto GetNumberOf() const
		noexcept -> size_t
    {
		return m_components.count(typeid(ComponentT));
	};

	template< typename ComponentT >
    [[nodiscard]]
	auto Get()
		noexcept -> ComponentT*
    {
		const auto it = m_components.find(typeid(ComponentT));
		return (it != m_components.end()) ? 
			static_cast< ComponentT* >(it->second) : nullptr;
	}

	template< typename ComponentT >
    [[nodiscard]]
	auto Get() const
		noexcept -> const ComponentT*
    {
		const auto it = m_components.find(typeid(ComponentT));
		return (it != m_components.cend()) ? 
			static_cast< ComponentT* >(it->second) : nullptr;
	}

	template< typename ComponentT >
    [[nodiscard]]
	auto GetAll()
		-> std::vector< ComponentT* >
    {
		std::vector< ComponentT* > components;
		const auto range = m_components.equal_range(typeid(ComponentT));
		std::for_each(range.first, range.second,
                      [&components](decltype(m_components)::value_type& x)
                      {
                          components.push_back(static_cast< ComponentT* >(x.second));
                      }
		);

		return components;
	}

	template< typename ComponentT >
    [[nodiscard]]
	auto GetAll() const
		-> std::vector< const ComponentT* >
    {
		std::vector< ComponentT* > components;
		const auto range = m_components.equal_range(typeid(ComponentT));
		std::for_each(range.first, range.second,
                      [&components](decltype(m_components)::value_type& x)
                      {
                          components.push_back(static_cast< ComponentT* >(x.second));
                      }
		);

		return components;
	}
    
    void AddComponent(Component* component)
    {
		m_components.emplace(typeid(*component), component);
	}
    
    std::unordered_multimap< std::type_index, Component* > m_components;
};

auto main()
    -> int
{
    Node n;
    A* c = new A();
    n.AddComponent(c);
    
    A* g = n.Get< A >();
    std::vector< A* > gs = n.GetAll< A >();
    std::cout << gs.size() << std::endl;
    std::cout << "----" << std::endl;
    std::cout << n.Has< A >() << std::endl;
    std::cout << n.Has< B >() << std::endl;
    std::cout << n.Has< Component >() << std::endl;
    std::cout << "----" << std::endl;
    std::cout << n.GetNumberOf< A >() << std::endl;
    std::cout << n.GetNumberOf< B >() << std::endl;
    std::cout << n.GetNumberOf< Component >() << std::endl;
    std::cout << "----" << std::endl;
    
    return 0;
}
