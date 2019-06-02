#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

using U32 = std::uint32_t;

template< typename T >
using AlignedVector = std::vector< T >; // placeholder

#define MAGE_ASSERT assert
#define private public // Testing purposes

namespace mage
{
	class Entity
	{

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit Entity(U32 id = 0u) noexcept
			: m_id(id)
		{}

		constexpr Entity(const Entity& entity) noexcept = default;

		constexpr Entity(Entity&& entity) noexcept = default;

		~Entity() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		Entity& operator=(const Entity& entity) noexcept = default;

		Entity& operator=(Entity&& entity) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		constexpr U32 GetID() const noexcept
		{
			return m_id;
		}

		[[nodiscard]]
		constexpr explicit operator U32() const noexcept
		{
			return GetID();
		}

		[[nodiscard]]
		constexpr bool operator==(const Entity& rhs) const noexcept
		{
			return m_id == rhs.m_id;
		}

		[[nodiscard]]
		constexpr bool operator!=(const Entity& rhs) const noexcept
		{
			return m_id != rhs.m_id;
		}

		[[nodiscard]]
		constexpr bool operator<=(const Entity& rhs) const noexcept
		{
			return m_id <= rhs.m_id;
		}

		[[nodiscard]]
		constexpr bool operator>=(const Entity& rhs) const noexcept
		{
			return m_id >= rhs.m_id;
		}

		[[nodiscard]]
		constexpr bool operator<(const Entity& rhs) const noexcept
		{
			return m_id < rhs.m_id;
		}

		[[nodiscard]]
		constexpr bool operator>(const Entity& rhs) const noexcept
		{
			return m_id > rhs.m_id;
		}

		[[nodiscard]]
		std::size_t Hash() const noexcept
		{
			return std::hash< U32 >()(m_id);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		U32 m_id;
	};

	static_assert(sizeof(U32) == sizeof(Entity));
}

namespace std
{
	template<>
	struct hash< mage::Entity >
	{
		size_t operator()(const mage::Entity& entity) const
		{
			return entity.Hash();
		}
	};
}

namespace mage
{
	template< typename T >
	class ComponentManager
	{

	public:

		//---------------------------------------------------------------------
		// Forward Declarations
		//---------------------------------------------------------------------

		class Reference;

		class ConstReference;

		template< typename ComponentIteratorT, typename ReferenceT >
		class Iterator;

		//---------------------------------------------------------------------
		// Class Member Types
		//---------------------------------------------------------------------

		using ComponentContainer = AlignedVector< T >;

		using EntityContainer = AlignedVector< Entity >;

		using MappingContainer = std::unordered_map< Entity, U32 >;

		using value_type
			= typename ComponentContainer::value_type;

		using size_type
			= typename ComponentContainer::size_type;

		using difference_type
			= typename ComponentContainer::difference_type;

		using pointer
			= typename ComponentContainer::pointer;

		using const_pointer
			= typename ComponentContainer::const_pointer;

		using reference = Reference;

		using const_reference = ConstReference;

		using ComponentIterator
			= typename ComponentContainer::iterator;

		using ConstComponentIterator
			= typename ComponentContainer::const_iterator;

		using ReverseComponentIterator
			= typename ComponentContainer::reverse_iterator;

		using ConstReverseComponentIterator
			= typename ComponentContainer::const_reverse_iterator;

		using EnityIterator
			= typename EntityContainer::iterator;

		using ConstEnityIterator
			= typename EntityContainer::const_iterator;

		using ReverseEnityIterator
			= typename EntityContainer::reverse_iterator;

		using ConstReverseEnityIterator
			= typename EntityContainer::const_reverse_iterator;

		using iterator 
			= Iterator< ComponentIterator, reference >;

		using const_iterator 
			= Iterator< ConstComponentIterator, const_reference >;

		using reverse_iterator
			= Iterator< ReverseComponentIterator, reference >;

		using const_reverse_iterator
			= Iterator< ConstReverseComponentIterator, const_reference >;

		//---------------------------------------------------------------------
		// Reference
		//---------------------------------------------------------------------

		class Reference
		{

		public:

			//-----------------------------------------------------------------
			// Class Member Types
			//-----------------------------------------------------------------

			using ComponentIterator
				= typename ComponentManager< T >::ComponentIterator;

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			explicit Reference(ComponentIterator component_it,
							   ComponentManager* component_manager) noexcept
				: m_component_it(std::move(component_it)),
				m_component_manager(component_manager)
			{
				MAGE_ASSERT(nullptr != m_component_manager);
				MAGE_ASSERT(m_component_manager->m_components.end()
							!= m_component_it);
			}

			Reference(const Reference& value) noexcept = default;

			Reference(Reference&& value) noexcept = default;

			~Reference() = default;

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			Reference& operator=(const Reference& value) = delete;

			Reference& operator=(Reference&& value) noexcept
			{
				swap(value);
				return *this;
			}

			Reference& operator=(const T& value)
			{
				GetComponent() = value;
				return *this;
			};

			Reference& operator=(T&& value)
			{
				GetComponent() = std::move(value);
				return *this;
			}

			//-----------------------------------------------------------------
			// Member Methods
			//-----------------------------------------------------------------

			[[nodiscard]]
			operator T& () noexcept
			{
				return GetComponent();
			}

			[[nodiscard]]
			operator const T& () const noexcept
			{
				return GetComponent();
			}

			[[nodiscard]]
			T& GetComponent() noexcept
			{
				return *m_component_it;
			}

			[[nodiscard]]
			const T& GetComponent() const noexcept
			{
				return *m_component_it;
			}

			[[nodiscard]]
			const Entity& GetEntity() const noexcept
			{
				const auto& components = m_component_manager->m_components;
				const auto& entities   = m_component_manager->m_entities;

				const auto begin = components.begin();
				const std::size_t index(m_component_it - begin);
				return entities[index];
			}

			void swap(Reference other) noexcept
			{
				MAGE_ASSERT(m_component_manager == other.m_component_manager);
				const auto& components = m_component_manager->m_components;

				const auto begin = components.begin();
				const std::size_t index1(m_component_it - begin);
				const std::size_t index2(other.m_component_it - begin);
				m_component_manager->SwapComponents(index1, index2);
			}

			friend void swap(Reference lhs, Reference rhs) noexcept
			{
				lhs.swap(rhs);
			}

		private:

			//-----------------------------------------------------------------
			// Member Variables
			//-----------------------------------------------------------------

			ComponentIterator m_component_it;

			ComponentManager* m_component_manager;
		};

		//---------------------------------------------------------------------
		// ConstReference
		//---------------------------------------------------------------------

		class ConstReference
		{

		public:

			//-----------------------------------------------------------------
			// Class Member Types
			//-----------------------------------------------------------------

			using ComponentIterator
				= typename ComponentManager< T >::ComponentIterator;

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			explicit ConstReference(ComponentIterator component_it,
									ComponentManager* component_manager) noexcept
				: m_component_it(std::move(component_it)),
				m_component_manager(component_manager)
			{
				MAGE_ASSERT(nullptr != m_component_manager);
				MAGE_ASSERT(m_component_manager->m_components.end()
							!= m_component_it);
			}

			ConstReference(const ConstReference& value) noexcept = default;

			ConstReference(ConstReference&& value) noexcept = default;

			~ConstReference() = default;

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			ConstReference& operator=(const ConstReference& value) = delete;

			ConstReference& operator=(ConstReference&& value) = delete;

			//-----------------------------------------------------------------
			// Member Methods
			//-----------------------------------------------------------------

			[[nodiscard]]
			operator const T& () const noexcept
			{
				return GetComponent();
			}

			[[nodiscard]]
			const T& GetComponent() const noexcept
			{
				return *m_component_it;
			}

			[[nodiscard]]
			const Entity& GetEntity() const noexcept
			{
				const auto& components = m_component_manager->m_components;
				const auto& entities   = m_component_manager->m_entities;

				const auto begin = components.begin();
				const std::size_t index(m_component_it - begin);
				return entities[index];
			}

		private:

			//-----------------------------------------------------------------
			// Member Variables
			//-----------------------------------------------------------------

			ComponentIterator m_component_it;

			ComponentManager* m_component_manager;
		};

		//---------------------------------------------------------------------
		// Iterator
		//---------------------------------------------------------------------

		template< typename ComponentIteratorT, typename ReferenceT >
		class Iterator
		{

		public:

			//-----------------------------------------------------------------
			// Class Member Types
			//-----------------------------------------------------------------

			using ComponentIterator = ComponentIteratorT;

			using value_type = typename ComponentIteratorT::value_type;

			using reference = ReferenceT;

			using pointer = void;

			using difference_type = std::ptrdiff_t;

			using iterator_category = std::random_access_iterator_tag;

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			Iterator() noexcept
				: m_component_it{},
				m_component_manager(nullptr)
			{}

			explicit Iterator(ComponentIterator component_it,
							  ComponentManager* component_manager) noexcept
				: m_component_it(std::move(component_it)),
				m_component_manager(component_manager)
			{}

			Iterator(const Iterator& it) noexcept = default;

			Iterator(Iterator&& it) noexcept = default;

			~Iterator() = default;

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			Iterator& operator=(const Iterator& it) noexcept = default;

			Iterator& operator=(Iterator&& it) noexcept = default;

			//-----------------------------------------------------------------
			// Member Methods
			//-----------------------------------------------------------------

			[[nodiscard]]
			reference operator*() const noexcept
			{
				return reference(m_component_it, m_component_manager);
			}

			pointer operator->() const = delete;

			[[nodiscard]]
			reference operator[](difference_type n) const noexcept
			{
				return reference(m_component_it + n, m_component_manager);
			}

			[[nodiscard]]
			difference_type operator-(const Iterator& it) const noexcept
			{
				return m_component_it - it.m_component_it;
			}

			[[nodiscard]]
			const Iterator operator+(difference_type n) const noexcept
			{
				return Iterator(m_component_it + n, m_component_manager);
			}

			[[nodiscard]]
			const Iterator operator-(difference_type n) const noexcept
			{
				return Iterator(m_component_it - n, m_component_manager);
			}

			[[nodiscard]]
			friend const Iterator operator+(difference_type n, const Iterator& it) noexcept
			{
				return it + n;
			}

			Iterator& operator++() noexcept
			{
				++m_component_it;
				return *this;
			}

			Iterator& operator--() noexcept
			{
				--m_component_it;
				return *this;
			}

			[[nodiscard]]
			friend const Iterator operator++(const Iterator& it) noexcept
			{
				return Iterator(it.m_component_it + 1u, it.m_component_manager);
			}

			[[nodiscard]]
			friend const Iterator operator--(const Iterator& it) noexcept
			{
				return Iterator(it.m_component_it - 1u, it.m_component_manager);
			}

			Iterator& operator+=(difference_type n) noexcept
			{
				m_component_it += n;
				return *this;
			}

			Iterator& operator-=(difference_type n) noexcept
			{
				m_component_it -= n;
				return *this;
			}

			[[nodiscard]]
			constexpr bool operator==(const Iterator& rhs) const noexcept
			{
				return m_component_it == rhs.m_component_it;
			}

			[[nodiscard]]
			constexpr bool operator!=(const Iterator& rhs) const noexcept
			{
				return m_component_it != rhs.m_component_it;
			}

			[[nodiscard]]
			constexpr bool operator<=(const Iterator& rhs) const noexcept
			{
				return m_component_it <= rhs.m_component_it;
			}

			[[nodiscard]]
			constexpr bool operator>=(const Iterator& rhs) const noexcept
			{
				return m_component_it >= rhs.m_component_it;
			}

			[[nodiscard]]
			constexpr bool operator<(const Iterator& rhs) const noexcept
			{
				return m_component_it < rhs.m_component_it;
			}

			[[nodiscard]]
			constexpr bool operator>(const Iterator& rhs) const noexcept
			{
				return m_component_it > rhs.m_component_it;
			}

			void swap(Iterator& other) noexcept
			{
				using std::swap;
				swap(m_component_it, other.m_component_it);
				swap(m_component_manager, other.m_component_manager);
			}

		private:

			ComponentIterator m_component_it;

			ComponentManager* m_component_manager;
		};

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		ComponentManager() = default;

		ComponentManager(const ComponentManager& manager) = default;

		ComponentManager(ComponentManager&& manager) noexcept = default;

		~ComponentManager() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ComponentManager& operator=(const ComponentManager& manager) = default;

		ComponentManager& operator=(ComponentManager&& manager) = default;

		//---------------------------------------------------------------------
		// Member Methods: Element access
		//---------------------------------------------------------------------

		[[nodiscard]]
		bool Contains(Entity entity) const noexcept
		{
			return m_mapping.find(entity) != m_mapping.cend();
		}

		[[nodiscard]]
		pointer Get(Entity entity) noexcept
		{
			if (const auto it = m_mapping.find(entity);
				it != m_mapping.cend())
			{
				return &m_components[it->second];
			}

			return nullptr;
		}

		[[nodiscard]]
		const_pointer Get(Entity entity) const noexcept
		{
			if (const auto it = m_mapping.find(entity);
				it != m_mapping.cend())
			{
				return &m_components[it->second];
			}

			return nullptr;
		}

		[[nodiscard]]
		reference at(size_type index)
		{
			if (size() <= index)
			{
				throw std::out_of_range("ComponentManager index out of range.");
			}
			
			return (*this)[index];
		}

		[[nodiscard]]
		const_reference at(size_type index) const
		{
			if (size() <= index)
			{
				throw std::out_of_range("ComponentManager index out of range.");
			}
			
			return (*this)[index];
		}

		[[nodiscard]]
		reference operator[](size_type index) noexcept
		{
			return *iterator(m_components.begin() + index, this);
		}

		[[nodiscard]]
		const_reference operator[](size_type index) const noexcept
		{
			return *const_iterator(m_components.begin() + index, this);
		}

		[[nodiscard]]
		reference front() noexcept
		{
			return (*this)[0u];
		}

		[[nodiscard]]
		const_reference front() const noexcept
		{
			return (*this)[0u];
		}

		[[nodiscard]]
		reference back() noexcept
		{
			return (*this)[size() - 1u];
		}

		[[nodiscard]]
		const_reference back() const noexcept
		{
			return (*this)[size() - 1u];
		}

		[[nodiscard]]
		pointer data() noexcept
		{
			return m_components.data();
		}

		[[nodiscard]]
		const_pointer data() const noexcept
		{
			return m_components.data();
		}

		//---------------------------------------------------------------------
		// Member Methods: Iterators
		//---------------------------------------------------------------------

		[[nodiscard]]
		iterator begin() noexcept
		{
			return iterator(m_components.begin(), this);
		}

		[[nodiscard]]
		const_iterator begin() const noexcept
		{
			return const_iterator(m_components.begin(), this);
		}

		[[nodiscard]]
		const_iterator cbegin() const noexcept
		{
			return const_iterator(m_components.cbegin(), this);
		}

		[[nodiscard]]
		iterator end() noexcept
		{
			return iterator(m_components.end(), this);
		}

		[[nodiscard]]
		const_iterator end() const noexcept
		{
			return const_iterator(m_components.end(), this);
		}

		[[nodiscard]]
		const_iterator cend() const noexcept
		{
			return const_iterator(m_components.end(), this);
		}

		[[nodiscard]]
		reverse_iterator rbegin() noexcept
		{
			return reverse_iterator(m_components.rbegin(), this);
		}

		[[nodiscard]]
		const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator(m_components.rbegin(), this);
		}

		[[nodiscard]]
		const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator(m_components.crbegin(), this);
		}

		[[nodiscard]]
		reverse_iterator rend() noexcept
		{
			return reverse_iterator(m_components.rend(), this);
		}

		[[nodiscard]]
		const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator(m_components.rend(), this);
		}

		[[nodiscard]]
		const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator(m_components.crend(), this);
		}

		//---------------------------------------------------------------------
		// Member Methods: Capacity
		//---------------------------------------------------------------------

		[[nodiscard]]
		bool empty() const noexcept
		{
			return m_components.empty();
		}

		[[nodiscard]]
		size_type size() const noexcept
		{
			return m_components.size();
		}

		[[nodiscard]]
		size_type max_size() const noexcept
		{
			return m_components.max_size();
		}

		void reserve(size_type new_capacity)
		{
			m_components.reserve(new_capacity);
			m_entities.reserve(new_capacity);
			m_mapping.reserve(new_capacity);
		}

		[[nodiscard]]
		size_type capacity() const noexcept
		{
			return m_components.capacity();
		}

		void shrink_to_fit()
		{
			m_components.shrink_to_fit();
			m_entities.shrink_to_fit();
		}

		//---------------------------------------------------------------------
		// Member Methods: Modifiers
		//---------------------------------------------------------------------

		void clear() noexcept
		{
			m_components.clear();
			m_entities.clear();
			m_mapping.clear();
		}

		void push_back(Entity entity, const value_type& value)
		{
			emplace_back(entity, value);
		}

		void push_back(Entity entity, value_type&& value)
		{
			emplace_back(entity, std::move(value));
		}

		template< typename... ConstructorArgsT  >
		reference emplace_back(Entity entity, ConstructorArgsT&& ... args)
		{
			if (const auto it = m_mapping.find(entity);
				it != m_mapping.cend())
			{
				return (*this)[it->second];
			}

			m_mapping.emplace(entity, static_cast< U32 >(size()));
			m_entities.push_back(entity);
			m_components.emplace_back(std::forward< ConstructorArgsT >(args)...);

			return back();
		}

		void pop_back()
		{
			m_mapping.erase(m_entities.back());
			m_components.pop_back();
			m_entities.pop_back();
		}

		void erase(Entity entity)
		{
			if (const auto it = m_mapping.find(entity);
				it != m_mapping.cend())
			{
				const auto index1 = it->second;
				const auto index2 = size() - 1u;
				if (index1 != index2)
				{
					SwapComponents(index1, index2);
				}

				pop_back();
			}
		}

		void swap(ComponentManager& other) noexcept
		{
			using std::swap;
			swap(m_components, other.m_components);
			swap(m_entities, other.m_entities);
			swap(m_mapping, other.m_mapping);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void SwapComponents(std::size_t index1, std::size_t index2) noexcept
		{
			auto& component1 = m_components[index1];
			auto& entity1    = m_entities[index1];
			auto& mapping1   = m_mapping[entity1];

			auto& component2 = m_components[index2];
			auto& entity2    = m_entities[index2];
			auto& mapping2   = m_mapping[entity2];

			using std::swap;
			swap(component1, component2);
			swap(entity1, entity2);
			swap(mapping1, mapping2);
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ComponentContainer m_components;

		EntityContainer m_entities;

		MappingContainer m_mapping;
	};
}

int main() {
    mage::ComponentManager< float > manager;
    manager.emplace_back(mage::Entity(5u), 5.0f);
    manager.emplace_back(mage::Entity(4u), 4.0f);
    manager.emplace_back(mage::Entity(3u), 3.0f);
    manager.emplace_back(mage::Entity(2u), 2.0f);
    manager.emplace_back(mage::Entity(1u), 1.0f);
    
    for (auto v : manager) {
        std::cout << v.GetComponent();
    }
    std::cout << std::endl;
    for (auto v : manager) {
        std::cout << U32(v.GetEntity());
    }
    std::cout << std::endl;
    std::cout << std::endl;
    for (auto& [e, i] : manager.m_mapping) {
        std::cout << '(' << U32(e) << "->" << i << ')';
    }
    std::cout << std::endl;
    
    std::sort(std::begin(manager), std::end(manager),
              [](const float& lhs, const float& rhs) { 
                  return lhs < rhs; 
              });
    std::partition(std::begin(manager), std::end(manager),
              [](const float& lhs) { 
                  return lhs == 3.0f; 
              });

    for (auto v : manager) {
        std::cout << v.GetComponent();
    }
    std::cout << std::endl;
    for (auto v : manager) {
        std::cout << U32(v.GetEntity());
    }
    std::cout << std::endl;
    std::cout << std::endl;
    for (auto& [e, i] : manager.m_mapping) {
        std::cout << '(' << U32(e) << "->" << i << ')';
    }
    std::cout << std::endl;

    return 0;
}
