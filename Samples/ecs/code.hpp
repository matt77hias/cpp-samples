#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using U32 = std::uint32_t;

template< typename T >
using AlignedVector = std::vector< T >; // placeholder

namespace mage {

	class Entity {

	public:
        
        //---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit Entity(U32 id = 0u) noexcept
			: m_id(id) {}
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
		constexpr U32 GetID() const noexcept {
			return m_id;
		}
        [[nodiscard]]
		constexpr explicit operator U32() const noexcept {
			return GetID();
		}
        
		[[nodiscard]]
		constexpr bool IsValid() const noexcept {
			return 0u != m_id;
		}
        [[nodiscard]]
		constexpr explicit operator bool() const noexcept {
			return IsValid();
		}
        
		[[nodiscard]]
		constexpr bool operator==(const Entity& rhs) const noexcept {
			return m_id == rhs.m_id;
		}
		[[nodiscard]]
		constexpr bool operator!=(const Entity& rhs) const noexcept {
			return m_id != rhs.m_id;
		}
		[[nodiscard]]
		constexpr bool operator<=(const Entity& rhs) const noexcept {
			return m_id <= rhs.m_id;
		}
		[[nodiscard]]
		constexpr bool operator>=(const Entity& rhs) const noexcept {
			return m_id >= rhs.m_id;
		}
		[[nodiscard]]
		constexpr bool operator<(const Entity& rhs) const noexcept {
			return m_id < rhs.m_id;
		}
		[[nodiscard]]
		constexpr bool operator>(const Entity& rhs) const noexcept {
			return m_id > rhs.m_id;
		}

		[[nodiscard]]
		std::size_t Hash() const noexcept {
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

namespace std {

	template<>
	struct hash< mage::Entity > {

		size_t operator()(const mage::Entity& entity) const {
			return entity.Hash();
		}
	};
}

namespace mage {

	//-------------------------------------------------------------------------
	// ComponentManager
	//-------------------------------------------------------------------------

	template< typename T >
	class ComponentManager {

	public:

		//---------------------------------------------------------------------
		// Class Member Types
		//---------------------------------------------------------------------

		using ComponentContainer = AlignedVector< T >;
		using EntityContainer    = AlignedVector< Entity >;
		using MappingContainer   = std::unordered_map< Entity, std::size_t >;

		using value_type
			= typename ComponentContainer::value_type;
		using size_type
			= typename ComponentContainer::size_type;
		using difference_type
			= typename ComponentContainer::difference_type;
		using reference
			= typename ComponentContainer::reference;
		using const_reference
			= typename ComponentContainer::const_reference;
		using pointer
			= typename ComponentContainer::pointer;
		using const_pointer
			= typename ComponentContainer::const_pointer;

		using iterator
			= typename ComponentContainer::iterator;
		using const_iterator
			= typename ComponentContainer::const_iterator;
		using reverse_iterator
			= typename ComponentContainer::reverse_iterator;
		using const_reverse_iterator
			= typename ComponentContainer::const_reverse_iterator;

		//---------------------------------------------------------------------
		// Friends
		//---------------------------------------------------------------------

        template< typename U >
		friend class Record;
        template< typename U >
		friend class RecordIterator;

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
		ComponentManager& operator=(ComponentManager&& manager) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods: Element access
		//---------------------------------------------------------------------

		[[nodiscard]]
		bool Contains(Entity entity) const noexcept {
			return m_mapping.find(entity) != m_mapping.cend();
		}

		[[nodiscard]]
		pointer Get(Entity entity) noexcept {
			if (const auto it = m_mapping.find(entity);
				it != m_mapping.cend()) {

				return &m_components[it->second];
			}

			return nullptr;
		}

		[[nodiscard]]
		const_pointer Get(Entity entity) const noexcept {
			if (const auto it = m_mapping.find(entity);
				it != m_mapping.cend()) {

				return &m_components[it->second];
			}

			return nullptr;
		}

		[[nodiscard]]
		reference at(size_type index) {
			return m_components.at(index);
		}

		[[nodiscard]]
		const_reference at(size_type index) const {
			return m_components.at(index);
		}

		[[nodiscard]]
		reference operator[](size_type index) noexcept {
			return m_components[index];
		}

		[[nodiscard]]
		const_reference operator[](size_type index) const noexcept {
			return m_components[index];
		}

		[[nodiscard]]
		reference front() noexcept {
			return m_components.front();
		}

		[[nodiscard]]
		const_reference front() const noexcept {
			return m_components.front();
		}

		[[nodiscard]]
		reference back() noexcept {
			return m_components.back();
		}

		[[nodiscard]]
		const_reference back() const noexcept {
			return m_components.back();
		}

		[[nodiscard]]
		value_type* data() noexcept {
			return m_components.data();
		}

		[[nodiscard]]
		const value_type* data() const noexcept {
			return m_components.data();
		}

		//---------------------------------------------------------------------
		// Member Methods: Iterators
		//---------------------------------------------------------------------

		[[nodiscard]]
		iterator begin() noexcept {
			return m_components.begin();
		}

		[[nodiscard]]
		const_iterator begin() const noexcept {
			return m_components.begin();
		}

		[[nodiscard]]
		const_iterator cbegin() const noexcept {
			return m_components.cbegin();
		}

		[[nodiscard]]
		iterator end() noexcept {
			return m_components.end();
		}

		[[nodiscard]]
		const_iterator end() const noexcept {
			return m_components.end();
		}

		[[nodiscard]]
		const_iterator cend() const noexcept {
			return m_components.end();
		}

		[[nodiscard]]
		reverse_iterator rbegin() noexcept {
			return m_components.rbegin();
		}

		[[nodiscard]]
		const_reverse_iterator rbegin() const noexcept {
			return m_components.rbegin();
		}

		[[nodiscard]]
		const_reverse_iterator crbegin() const noexcept {
			return m_components.crbegin();
		}

		[[nodiscard]]
		reverse_iterator rend() noexcept {
			return m_components.rend();
		}

		[[nodiscard]]
		const_reverse_iterator rend() const noexcept {
			return m_components.rend();
		}

		[[nodiscard]]
		const_reverse_iterator crend() const noexcept {
			return m_components.crend();
		}

		//---------------------------------------------------------------------
		// Member Methods: Capacity
		//---------------------------------------------------------------------

		[[nodiscard]]
		bool empty() const noexcept {
			return m_components.empty();
		}

		[[nodiscard]]
		size_type size() const noexcept {
			return m_components.size();
		}

		[[nodiscard]]
		size_type max_size() const noexcept {
			return m_components.max_size();
		}

		void reserve(size_type new_capacity) {
			m_components.reserve(new_capacity);
			m_entities.reserve(new_capacity);
			m_mapping.reserve(new_capacity);
		}

		[[nodiscard]]
		size_type capacity() const noexcept {
			return m_components.capacity();
		}

		void shrink_to_fit() {
			m_components.shrink_to_fit();
			m_entities.shrink_to_fit();
		}

		//---------------------------------------------------------------------
		// Member Methods: Modifiers
		//---------------------------------------------------------------------

		void clear() noexcept {
			m_components.clear();
			m_entities.clear();
			m_mapping.clear();
		}

		void push_back(Entity entity, const value_type& value) {
			emplace_back(entity, value);
		}

		void push_back(Entity entity, value_type&& value) {
			emplace_back(entity, std::move(value));
		}

		template< typename... ConstructorArgsT  >
		reference emplace_back(Entity entity, ConstructorArgsT&&... args) {
			if (const auto it = m_mapping.find(entity);
				it != m_mapping.cend()) {
				
				return m_components[it->second];
			}

			m_mapping.emplace(entity, size());
			m_entities.push_back(entity);
			return m_components.emplace_back(
				std::forward< ConstructorArgsT >(args)...);
		}

		void pop_back() {
			m_mapping.erase(m_entities.back());
			m_components.pop_back();
			m_entities.pop_back();
		}

		void swap(ComponentManager& other) noexcept {
			std::swap(m_components, other.m_components);
			std::swap(m_entities,   other.m_entities);
			std::swap(m_mapping,    other.m_mapping);
		}
        
    // private: commented for std::cout illustration

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		AlignedVector< value_type > m_components;
		
		AlignedVector< Entity > m_entities;

		std::unordered_map< Entity, std::size_t > m_mapping;
	};

	//-------------------------------------------------------------------------
	// Record
	//-------------------------------------------------------------------------
		
	template< typename T >
	class Record {

	public:

		//---------------------------------------------------------------------
		// Class Member Types
		//---------------------------------------------------------------------

		using ComponentIterator = typename ComponentManager< T >::iterator;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		Record() noexcept
			: m_component_it{},
			m_component_manager(nullptr) {}
		explicit Record(ComponentIterator component_it,
						ComponentManager< T >* component_manager) noexcept
			: m_component_it(std::move(component_it)),
			m_component_manager(component_manager) {}
		Record(const Record& record) noexcept = default;
		Record(Record&& record) noexcept = default;
		~Record() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		Record& operator=(const Record& record) = delete;
		Record& operator=(Record&& record) noexcept {
			swap(record);
			return *this;
		}
			
		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		constexpr bool operator==(const T& rhs) const noexcept {
			return *m_component_it == rhs;
		}
		[[nodiscard]]
		constexpr bool operator!=(const T& rhs) const noexcept {
			return *m_component_it != rhs;
		}
		[[nodiscard]]
		constexpr bool operator<=(const T& rhs) const noexcept {
			return *m_component_it <= rhs;
		}
		[[nodiscard]]
		constexpr bool operator>=(const T& rhs) const noexcept {
			return *m_component_it >= rhs;
		}
		[[nodiscard]]
		constexpr bool operator<(const T& rhs) const noexcept {
			return *m_component_it < rhs;
		}
		[[nodiscard]]
		constexpr bool operator>(const T& rhs) const noexcept {
			return *m_component_it > rhs;
		}

		[[nodiscard]]
		friend constexpr bool operator==(const T& lhs, const Record& rhs) noexcept {
			return lhs == *rhs.m_component_it;
		}
		[[nodiscard]]
		friend constexpr bool operator!=(const T& lhs, const Record& rhs) noexcept {
			return lhs != *rhs.m_component_it;
		}
		[[nodiscard]]
		friend constexpr bool operator<=(const T& lhs, const Record& rhs) noexcept {
			return lhs <= *rhs.m_component_it;
		}
		[[nodiscard]]
		friend constexpr bool operator>=(const T& lhs, const Record& rhs) noexcept {
			return lhs >= *rhs.m_component_it;
		}
		[[nodiscard]]
		friend constexpr bool operator<(const T& lhs, const Record& rhs) noexcept {
			return lhs < *rhs.m_component_it;
		}
		[[nodiscard]]
		friend constexpr bool operator>(const T& lhs, const Record& rhs) noexcept {
			return lhs > *rhs.m_component_it;
		}

		[[nodiscard]]
		constexpr bool operator==(const Record& rhs) const noexcept {
			return *m_component_it == *rhs.m_component_it;
		}
		[[nodiscard]]
		constexpr bool operator!=(const Record& rhs) const noexcept {
			return *m_component_it != *rhs.m_component_it;
		}
		[[nodiscard]]
		constexpr bool operator<=(const Record& rhs) const noexcept {
			return *m_component_it <= *rhs.m_component_it;
		}
		[[nodiscard]]
		constexpr bool operator>=(const Record& rhs) const noexcept {
			return *m_component_it >= *rhs.m_component_it;
		}
		[[nodiscard]]
		constexpr bool operator<(const Record& rhs) const noexcept {
			return *m_component_it < *rhs.m_component_it;
		}
		[[nodiscard]]
		constexpr bool operator>(const Record& rhs) const noexcept {
			return *m_component_it > *rhs.m_component_it;
		}

        void swap(Record& other) noexcept {
			assert(nullptr != m_component_manager);
			assert(m_component_manager == other.m_component_manager);
			assert(m_component_manager->end() != m_component_it);
			assert(m_component_manager->end() != other.m_component_it);

			const std::size_t n1 = m_component_it - m_component_manager->m_components.begin();
			auto entity_it1      = m_component_manager->m_entities.begin() + n1;
			auto& mapping1       = m_component_manager->m_mapping[*entity_it1];

			const std::size_t n2 = other.m_component_it - m_component_manager->m_components.begin();
			auto entity_it2      = m_component_manager->m_entities.begin() + n2;
			auto& mapping2       = m_component_manager->m_mapping[*entity_it2];

			std::swap(*m_component_it, *other.m_component_it);
			std::swap(*entity_it1, *entity_it2);
			std::swap(mapping1, mapping2);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ComponentIterator m_component_it;
		ComponentManager< T >* m_component_manager;
	};

	//-------------------------------------------------------------------------
	// RecordIterator
	//-------------------------------------------------------------------------
		
	template< typename T >
	class RecordIterator {

	public:

		//---------------------------------------------------------------------
		// Class Member Types
		//---------------------------------------------------------------------

		using ComponentIterator = typename ComponentManager< T >::iterator;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		RecordIterator() noexcept
			: m_component_it{},
			m_component_manager(nullptr) {}
		explicit RecordIterator(ComponentIterator component_it,
						        ComponentManager< T >* component_manager) noexcept
			: m_component_it(std::move(component_it)), 
			m_component_manager(component_manager) {}
		RecordIterator(const RecordIterator& it) noexcept = default;
		RecordIterator(RecordIterator&& it) noexcept = default;
		~RecordIterator() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		RecordIterator& operator=(const RecordIterator& it) noexcept = default;
		RecordIterator& operator=(RecordIterator&& it) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		Record< T > operator*() noexcept {
			return Record< T >(m_component_it, m_component_manager);
		}
		Record< T > operator*() const noexcept {
			return Record< T >(m_component_it, m_component_manager);
		}

		[[nodiscard]]
		Record< T > operator[](std::size_t n) noexcept {
			return Record< T >(m_component_it + n, m_component_manager);
		}
		[[nodiscard]]
		Record< T > operator[](std::size_t n) const noexcept {
			return Record< T >(m_component_it + n, m_component_manager);
		}

		[[nodiscard]]
		std::size_t operator-(const RecordIterator& it) const noexcept {
			return m_component_it - it.m_component_it;
		}

		[[nodiscard]]
		const RecordIterator operator+(std::size_t n) const noexcept {
			return RecordIterator(m_component_it + n, m_component_manager);
		}
		[[nodiscard]]
		const RecordIterator operator-(std::size_t n) const noexcept {
			return RecordIterator(m_component_it - n, m_component_manager);
		}
			
		[[nodiscard]]
		friend const RecordIterator operator+(std::size_t n, const RecordIterator& it) noexcept {
			return it + n;
		}
			
		RecordIterator& operator++() noexcept {
			++m_component_it;
			return *this;
		}
		RecordIterator& operator--() noexcept {
			--m_component_it;
			return *this;
		}
			
		[[nodiscard]]
		friend const RecordIterator operator++(const RecordIterator& it) noexcept {
			return RecordIterator(it.m_component_it + 1u, it.m_component_manager);
		}
		[[nodiscard]]
		friend const RecordIterator operator--(const RecordIterator& it) noexcept {
			return RecordIterator(it.m_component_it - 1u, it.m_component_manager);
		}

		RecordIterator& operator+=(std::size_t n) noexcept {
			m_component_it += n;
			return *this;
		}
		RecordIterator& operator-=(std::size_t n) noexcept {
			m_component_it -= n;
			return *this;
		}

		[[nodiscard]]
		constexpr bool operator==(const RecordIterator& rhs) const noexcept {
			return m_component_it == rhs.m_component_it;
		}
		[[nodiscard]]
		constexpr bool operator!=(const RecordIterator& rhs) const noexcept {
			return m_component_it != rhs.m_component_it;
		}
		[[nodiscard]]
		constexpr bool operator<=(const RecordIterator& rhs) const noexcept {
			return m_component_it <= rhs.m_component_it;
		}
		[[nodiscard]]
		constexpr bool operator>=(const RecordIterator& rhs) const noexcept {
			return m_component_it >= rhs.m_component_it;
		}
		[[nodiscard]]
		constexpr bool operator<(const RecordIterator& rhs) const noexcept {
			return m_component_it < rhs.m_component_it;
		}
		[[nodiscard]]
		constexpr bool operator>(const RecordIterator& rhs) const noexcept {
			return m_component_it > rhs.m_component_it;
		}

	private:
			
		ComponentIterator m_component_it;
		ComponentManager< T >* m_component_manager;
	};

	//-------------------------------------------------------------------------
	// ComponentManager
	//-------------------------------------------------------------------------

	template< typename T >
	[[nodiscard]]
	inline RecordIterator< T > RecordBegin(ComponentManager< T >& manager) noexcept {
		return RecordIterator< T >(manager.begin(), &manager);
	}

	template< typename T >
	[[nodiscard]]
	inline RecordIterator< T > RecordEnd(ComponentManager< T >& manager) noexcept {
		return RecordIterator< T >(manager.end(), &manager);
	}

    template< typename T >
	void swap(mage::Record< T > lhs, mage::Record< T > rhs) noexcept {
		lhs.swap(rhs);
	}
}

namespace std {

    template< typename T >
    struct iterator_traits< mage::RecordIterator< T > > {
     
    public:
    
        using value_type        = mage::Record< T >;
        using reference_type    = mage::Record< T >&;
        using pointer_type      = mage::Record< T >*;
        using difference_type   = ptrdiff_t;
        using iterator_category = random_access_iterator_tag;
    };
}

int main() {
    mage::ComponentManager< float > manager;
    manager.emplace_back(mage::Entity(5u), 5.0f);
    manager.emplace_back(mage::Entity(4u), 4.0f);
    manager.emplace_back(mage::Entity(3u), 3.0f);
    manager.emplace_back(mage::Entity(2u), 2.0f);
    manager.emplace_back(mage::Entity(1u), 1.0f);
    
    for (auto& c : manager.m_components) {
        std::cout << c;
    }
    std::cout << std::endl;
    for (auto& e : manager.m_entities) {
        std::cout << U32(e);
    }
    std::cout << std::endl;
    for (auto& [e, i] : manager.m_mapping) {
        std::cout << '(' << U32(e) << "->" << i << ')';
    }
    std::cout << std::endl;
    
    std::sort(RecordBegin(manager), RecordEnd(manager));
    
    for (auto& c : manager.m_components) {
        std::cout << c;
    }
    std::cout << std::endl;
    for (auto& e : manager.m_entities) {
        std::cout << U32(e);
    }
    std::cout << std::endl;
    for (auto& [e, i] : manager.m_mapping) {
        std::cout << '(' << U32(e) << "->" << i << ')';
    }
    std::cout << std::endl;
    
    return 0;
}
