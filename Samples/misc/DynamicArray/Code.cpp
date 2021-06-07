// TODO: update

#include <array>
#include <iostream>
#include <memory>
#include <stdexcept>

template< typename T >
class DynamicArray {

public:

	//---------------------------------------------------------------------
	// Class Member Types
	//---------------------------------------------------------------------

	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using reference = value_type& ;
	using const_reference = const value_type&;
	using pointer = value_type* ;
	using const_pointer = const value_type*;

	using iterator = T * ;
	using const_iterator = const T*;
	using reverse_iterator = std::reverse_iterator< iterator >;
	using const_reverse_iterator = std::reverse_iterator< const_iterator >;

	//---------------------------------------------------------------------
	// Constructors and Destructors
	//---------------------------------------------------------------------

	explicit DynamicArray(std::size_t size)
		: m_size(size),
		m_data((0u == size) ? nullptr : new value_type[size] {}) {}
	
	DynamicArray(const DynamicArray& a)
		: DynamicArray(a.size()) {

		auto from = a.cbegin();
		for (auto to = begin(); to != end(); ++to, ++from) {
			*to = *from;
		}
	}
	
	DynamicArray(DynamicArray&& a) noexcept = default;
	
	~DynamicArray() = default;

	//---------------------------------------------------------------------
	// Assignment Operators
	//---------------------------------------------------------------------

	DynamicArray& operator=(const DynamicArray& a) {
		if (size() != a.size()) {
			m_size = a.size();
			m_data.reset(new value_type[m_size] {});
		}

		auto from = a.cbegin();
		for (auto to = begin(); to != end(); ++to, ++from) {
			*to = *from;
		}

		return *this;
	};
	
	DynamicArray& operator=(DynamicArray&& a) noexcept = default;

	//---------------------------------------------------------------------
	// Member Methods: Element access
	//---------------------------------------------------------------------

	[[nodiscard]]
	reference at(size_type index) {
		if (size() <= index) {
			throw std::out_of_range("DynamicArray index out of range.");
		}

		return m_data[index];
	}

	[[nodiscard]]
	const_reference at(size_type index) const {
		if (size() <= index) {
			throw std::out_of_range("DynamicArray index out of range.");
		}

		return m_data[index];
	}

	[[nodiscard]]
	reference operator[](size_type index) noexcept {
		return m_data[index];
	}

	[[nodiscard]]
	const_reference operator[](size_type index) const noexcept {
		return m_data[index];
	}

	[[nodiscard]]
	reference front() noexcept {
		return m_data[0u];
	}

	[[nodiscard]]
	const_reference front() const noexcept {
		return m_data[0u];
	}

	[[nodiscard]]
	reference back() noexcept {
		return m_data[size() - 1u];
	}

	[[nodiscard]]
	const_reference back() const noexcept {
		return m_data[size() - 1u];
	}

	[[nodiscard]]
	T* data() noexcept {
		return m_data.get();
	}

	[[nodiscard]]
	const T* data() const noexcept {
		return m_data.get();
	}

	//---------------------------------------------------------------------
	// Member Methods: Iterators
	//---------------------------------------------------------------------

	[[nodiscard]]
	iterator begin() noexcept {
		return data();
	}

	[[nodiscard]]
	const_iterator begin() const noexcept {
		return data();
	}

	[[nodiscard]]
	const_iterator cbegin() const noexcept {
		return begin();
	}

	[[nodiscard]]
	iterator end() noexcept {
		return empty() ? nullptr : (data() + size());
	}

	[[nodiscard]]
	const_iterator end() const noexcept {
		return empty() ? nullptr : (data() + size());
	}

	[[nodiscard]]
	const_iterator cend() const noexcept {
		return end();
	}

	[[nodiscard]]
	reverse_iterator rbegin() noexcept {
		return reverse_iterator(end());
	}

	[[nodiscard]]
	const_reverse_iterator rbegin() const noexcept {
		return reverse_iterator(cend());
	}

	[[nodiscard]]
	const_reverse_iterator crbegin() const noexcept {
		return rbegin();
	}

	[[nodiscard]]
	reverse_iterator rend() noexcept {
		return reverse_iterator(begin());
	}

	[[nodiscard]]
	const_reverse_iterator rend() const noexcept {
		return reverse_iterator(cbegin());
	}

	[[nodiscard]]
	const_reverse_iterator crend() const noexcept {
		return rend();
	}

	//---------------------------------------------------------------------
	// Member Methods: Capacity
	//---------------------------------------------------------------------

	[[nodiscard]]
	bool empty() const noexcept {
		return size() == 0u;
	}

	[[nodiscard]]
	size_type size() const noexcept {
		return m_size;
	}

	[[nodiscard]]
	size_type max_size() const noexcept {
		return size();
	}

	//---------------------------------------------------------------------
	// Member Methods: Modifiers
	//---------------------------------------------------------------------

	void fill(const T& value) {
		for (auto& element : *this) {
			element = value;
		}
	}

	void swap(DynamicArray& other) noexcept {
		std::swap(m_size, other.m_size);
		std::swap(m_data, other.m_data);
	}

private:
	
	//---------------------------------------------------------------------
	// Member Variables
	//---------------------------------------------------------------------

	std::size_t m_size;

	std::unique_ptr< T[] > m_data;
};

template< typename T, std::size_t Capacity >
class StaticMemoryBuffer {

public:

	//---------------------------------------------------------------------
	// Class Member Types
	//---------------------------------------------------------------------

	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using reference = value_type& ;
	using const_reference = const value_type&;
	using pointer = value_type* ;
	using const_pointer = const value_type*;

	using iterator = T*;
	using const_iterator = const T*;
	using reverse_iterator = std::reverse_iterator< iterator >;
	using const_reverse_iterator = std::reverse_iterator< const_iterator >;

	//---------------------------------------------------------------------
	// Constructors and Destructors
	//---------------------------------------------------------------------

	StaticMemoryBuffer()
		: m_size(0u),
		m_data{} {}

	StaticMemoryBuffer(const StaticMemoryBuffer& buffer) = default;

	StaticMemoryBuffer(StaticMemoryBuffer&& buffer) noexcept = default;

	~StaticMemoryBuffer() = default;

	//---------------------------------------------------------------------
	// Assignment Operators
	//---------------------------------------------------------------------

	StaticMemoryBuffer& operator=(
		const StaticMemoryBuffer& buffer) = default;

	StaticMemoryBuffer& operator=(
		StaticMemoryBuffer&& buffer) noexcept = default;

	//---------------------------------------------------------------------
	// Member Methods: Element access
	//---------------------------------------------------------------------

	[[nodiscard]]
	reference at(size_type index) {
		if (size() <= index) {
			throw std::out_of_range("StaticMemoryBuffer index out of range.");
		}

		return m_data[index];
	}

	[[nodiscard]]
	const_reference at(size_type index) const {
		if (size() <= index) {
			throw std::out_of_range("StaticMemoryBuffer index out of range.");
		}

		return m_data[index];
	}

	[[nodiscard]]
	reference operator[](size_type index) noexcept {
		return m_data[index];
	}

	[[nodiscard]]
	const_reference operator[](size_type index) const noexcept {
		return m_data[index];
	}

	[[nodiscard]]
	reference front() noexcept {
		return m_data[0u];
	}

	[[nodiscard]]
	const_reference front() const noexcept {
		return m_data[0u];
	}

	[[nodiscard]]
	reference back() noexcept {
		return m_data[size() - 1u];
	}

	[[nodiscard]]
	const_reference back() const noexcept {
		return m_data[size() - 1u];
	}

	[[nodiscard]]
	T* data() noexcept {
		return m_data.data();
	}

	[[nodiscard]]
	const T* data() const noexcept {
		return m_data.data();
	}

	//---------------------------------------------------------------------
	// Member Methods: Iterators
	//---------------------------------------------------------------------

	[[nodiscard]]
	iterator begin() noexcept {
		return data();
	}

	[[nodiscard]]
	const_iterator begin() const noexcept {
		return data();
	}

	[[nodiscard]]
	const_iterator cbegin() const noexcept {
		return begin();
	}

	[[nodiscard]]
	iterator end() noexcept {
		return empty() ? nullptr : (data() + size());
	}

	[[nodiscard]]
	const_iterator end() const noexcept {
		return empty() ? nullptr : (data() + size());
	}

	[[nodiscard]]
	const_iterator cend() const noexcept {
		return end();
	}

	[[nodiscard]]
	reverse_iterator rbegin() noexcept {
		return reverse_iterator(end());
	}

	[[nodiscard]]
	const_reverse_iterator rbegin() const noexcept {
		return reverse_iterator(cend());
	}

	[[nodiscard]]
	const_reverse_iterator crbegin() const noexcept {
		return rbegin();
	}

	[[nodiscard]]
	reverse_iterator rend() noexcept {
		return reverse_iterator(begin());
	}

	[[nodiscard]]
	const_reverse_iterator rend() const noexcept {
		return reverse_iterator(cbegin());
	}

	[[nodiscard]]
	const_reverse_iterator crend() const noexcept {
		return rend();
	}

	//---------------------------------------------------------------------
	// Member Methods: Capacity
	//---------------------------------------------------------------------

	[[nodiscard]]
	bool empty() const noexcept {
		return size() == 0u;
	}

	[[nodiscard]]
	bool full() const noexcept {
		return size() == capacity();
	}

	[[nodiscard]]
	size_type size() const noexcept {
		return m_size;
	}

	[[nodiscard]]
	size_type max_size() const noexcept {
		return size();
	}

	[[nodiscard]]
	size_type capacity() const noexcept {
		return Capacity;
	}

	//---------------------------------------------------------------------
	// Member Methods: Modifiers
	//---------------------------------------------------------------------

	void push_back(const T& value) {
		emplace_back(value);
	}

	void push_back(T&& value) {
		emplace_back(std::move(value));
	}

	template< typename... Args >
	void emplace_back(Args&&... args) {
		if (full()) {
			return;
		}

		m_data[m_size++] = T { std::forward< Args >(args)... };
	}

	void swap(StaticMemoryBuffer& other) noexcept {
		std::swap(m_size, other.m_size);
		std::swap(m_data, other.m_data);
	}

private:
	
	//---------------------------------------------------------------------
	// Member Variables
	//---------------------------------------------------------------------

	std::size_t m_size;

	std::array< T, Capacity > m_data;
};

template< typename T >
class DynamicMemoryBuffer {

public:

	//---------------------------------------------------------------------
	// Class Member Types
	//---------------------------------------------------------------------

	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using reference = value_type& ;
	using const_reference = const value_type&;
	using pointer = value_type* ;
	using const_pointer = const value_type*;

	using iterator = T*;
	using const_iterator = const T*;
	using reverse_iterator = std::reverse_iterator< iterator >;
	using const_reverse_iterator = std::reverse_iterator< const_iterator >;

	//---------------------------------------------------------------------
	// Constructors and Destructors
	//---------------------------------------------------------------------

	explicit DynamicMemoryBuffer(std::size_t capacity = 0u)
		: m_size(0u),
		m_data(capacity) {}

	DynamicMemoryBuffer(const DynamicMemoryBuffer& buffer) = delete;

	DynamicMemoryBuffer(DynamicMemoryBuffer&& buffer) noexcept = default;

	~DynamicMemoryBuffer() = default;

	//---------------------------------------------------------------------
	// Assignment Operators
	//---------------------------------------------------------------------

	DynamicMemoryBuffer& operator=(const DynamicMemoryBuffer& buffer) = delete;

	DynamicMemoryBuffer& operator=(DynamicMemoryBuffer&& buffer) = delete;

	//---------------------------------------------------------------------
	// Member Methods: Element access
	//---------------------------------------------------------------------

	[[nodiscard]]
	reference at(size_type index) {
		if (size() <= index) {
			throw std::out_of_range("DynamicMemoryBuffer index out of range.");
		}

		return m_data[index];
	}

	[[nodiscard]]
	const_reference at(size_type index) const {
		if (size() <= index) {
			throw std::out_of_range("DynamicMemoryBuffer index out of range.");
		}

		return m_data[index];
	}

	[[nodiscard]]
	reference operator[](size_type index) noexcept {
		return m_data[index];
	}

	[[nodiscard]]
	const_reference operator[](size_type index) const noexcept {
		return m_data[index];
	}

	[[nodiscard]]
	reference front() noexcept {
		return m_data[0u];
	}

	[[nodiscard]]
	const_reference front() const noexcept {
		return m_data[0u];
	}

	[[nodiscard]]
	reference back() noexcept {
		return m_data[size() - 1u];
	}

	[[nodiscard]]
	const_reference back() const noexcept {
		return m_data[size() - 1u];
	}

	[[nodiscard]]
	T* data() noexcept {
		return m_data.data();
	}

	[[nodiscard]]
	const T* data() const noexcept {
		return m_data.data();
	}

	//---------------------------------------------------------------------
	// Member Methods: Iterators
	//---------------------------------------------------------------------

	[[nodiscard]]
	iterator begin() noexcept {
		return data();
	}

	[[nodiscard]]
	const_iterator begin() const noexcept {
		return data();
	}

	[[nodiscard]]
	const_iterator cbegin() const noexcept {
		return begin();
	}

	[[nodiscard]]
	iterator end() noexcept {
		return empty() ? nullptr : (data() + size());
	}

	[[nodiscard]]
	const_iterator end() const noexcept {
		return empty() ? nullptr : (data() + size());
	}

	[[nodiscard]]
	const_iterator cend() const noexcept {
		return end();
	}

	[[nodiscard]]
	reverse_iterator rbegin() noexcept {
		return reverse_iterator(end());
	}

	[[nodiscard]]
	const_reverse_iterator rbegin() const noexcept {
		return reverse_iterator(cend());
	}

	[[nodiscard]]
	const_reverse_iterator crbegin() const noexcept {
		return rbegin();
	}

	[[nodiscard]]
	reverse_iterator rend() noexcept {
		return reverse_iterator(begin());
	}

	[[nodiscard]]
	const_reverse_iterator rend() const noexcept {
		return reverse_iterator(cbegin());
	}

	[[nodiscard]]
	const_reverse_iterator crend() const noexcept {
		return rend();
	}

	//---------------------------------------------------------------------
	// Member Methods: Capacity
	//---------------------------------------------------------------------

	[[nodiscard]]
	bool empty() const noexcept {
		return size() == 0u;
	}

	[[nodiscard]]
	bool full() const noexcept {
		return size() == capacity();
	}

	[[nodiscard]]
	size_type size() const noexcept {
		return m_size;
	}

	[[nodiscard]]
	size_type max_size() const noexcept {
		return size();
	}

	[[nodiscard]]
	size_type capacity() const noexcept {
		return m_data.size();
	}

	void reserve(size_type new_capacity) {
		if (new_capacity <= capacity()) {
			return;
		}

		DynamicArray< T > a(new_capacity);
		for (size_type i = 0u; i < size(); ++i) {
			a[i] = std::move(m_data[i]);
		}

		m_data = std::move(a);
	}

	//---------------------------------------------------------------------
	// Member Methods: Modifiers
	//---------------------------------------------------------------------

	void push_back(const T& value) {
		emplace_back(value);
	}

	void push_back(T&& value) {
		emplace_back(std::move(value));
	}

	template< typename... Args >
	void emplace_back(Args&&... args) {
		if (full()) {
			return;
		}

		m_data[m_size++] = T { std::forward< Args >(args)... };
	}

	void swap(DynamicMemoryBuffer& other) noexcept {
		std::swap(m_size, other.m_size);
		std::swap(m_data, other.m_data);
	}

private:
	
	//---------------------------------------------------------------------
	// Member Variables
	//---------------------------------------------------------------------

	std::size_t m_size;

	DynamicArray< T > m_data;
};

template< typename T, std::size_t StaticCapacity >
class MemoryBuffer {

public:

	//---------------------------------------------------------------------
	// Class Member Types
	//---------------------------------------------------------------------

	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using reference = value_type& ;
	using const_reference = const value_type&;
	using pointer = value_type* ;
	using const_pointer = const value_type*;

	using iterator = T*;
	using const_iterator = const T*;
	using reverse_iterator = std::reverse_iterator< iterator >;
	using const_reverse_iterator = std::reverse_iterator< const_iterator >;

	//---------------------------------------------------------------------
	// Constructors and Destructors
	//---------------------------------------------------------------------

	MemoryBuffer()
		: m_static_data(), 
		m_dynamic_data() {}
	
	MemoryBuffer(const MemoryBuffer& buffer) = delete;

	MemoryBuffer(MemoryBuffer&& buffer) noexcept = default;

	~MemoryBuffer() = default;

	//---------------------------------------------------------------------
	// Assignment Operators
	//---------------------------------------------------------------------

	MemoryBuffer& operator=(const MemoryBuffer& buffer) = delete;

	MemoryBuffer& operator=(MemoryBuffer&& buffer) = delete;

	//---------------------------------------------------------------------
	// Member Methods: Element access
	//---------------------------------------------------------------------

	[[nodiscard]]
	bool UsesStaticMemoryBuffer() const noexcept {
		return m_dynamic_data.capacity() == 0u;
	}

	[[nodiscard]]
	bool UsesDynamicMemoryBuffer() const noexcept {
		return !UsesStaticMemoryBuffer();
	}

	[[nodiscard]]
	reference at(size_type index) {
		return UsesStaticMemoryBuffer() ?
			m_static_data.at(index) : m_dynamic_data.at(index);
	}

	[[nodiscard]]
	const_reference at(size_type index) const {
		return UsesStaticMemoryBuffer() ?
			m_static_data.at(index) : m_dynamic_data.at(index);
	}

	[[nodiscard]]
	reference operator[](size_type index) noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data[index] : m_dynamic_data[index];
	}

	[[nodiscard]]
	const_reference operator[](size_type index) const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data[index] : m_dynamic_data[index];
	}

	[[nodiscard]]
	reference front() noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.front() : m_dynamic_data.front();
	}

	[[nodiscard]]
	const_reference front() const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.front() : m_dynamic_data.front();
	}

	[[nodiscard]]
	reference back() noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.back() : m_dynamic_data.back();
	}

	[[nodiscard]]
	const_reference back() const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.back() : m_dynamic_data.back();
	}

	[[nodiscard]]
	T* data() noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.data() : m_dynamic_data.data();
	}

	[[nodiscard]]
	const T* data() const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.data() : m_dynamic_data.data();
	}

	//---------------------------------------------------------------------
	// Member Methods: Iterators
	//---------------------------------------------------------------------

	[[nodiscard]]
	iterator begin() noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.begin() : m_dynamic_data.begin();
	}

	[[nodiscard]]
	const_iterator begin() const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.begin() : m_dynamic_data.begin();
	}

	[[nodiscard]]
	const_iterator cbegin() const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.cbegin() : m_dynamic_data.cbegin();
	}

	[[nodiscard]]
	iterator end() noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.end() : m_dynamic_data.end();
	}

	[[nodiscard]]
	const_iterator end() const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.end() : m_dynamic_data.end();
	}

	[[nodiscard]]
	const_iterator cend() const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.cend() : m_dynamic_data.cend();
	}

	[[nodiscard]]
	reverse_iterator rbegin() noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.rbegin() : m_dynamic_data.rbegin();
	}

	[[nodiscard]]
	const_reverse_iterator rbegin() const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.rbegin() : m_dynamic_data.rbegin();
	}

	[[nodiscard]]
	const_reverse_iterator crbegin() const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.crbegin() : m_dynamic_data.crbegin();
	}

	[[nodiscard]]
	reverse_iterator rend() noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.rend() : m_dynamic_data.rend();
	}

	[[nodiscard]]
	const_reverse_iterator rend() const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.rend() : m_dynamic_data.rend();
	}

	[[nodiscard]]
	const_reverse_iterator crend() const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.crend() : m_dynamic_data.crend();
	}

	//---------------------------------------------------------------------
	// Member Methods: Capacity
	//---------------------------------------------------------------------
	
	[[nodiscard]]
	bool empty() const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.empty() : m_dynamic_data.empty();
	}

	[[nodiscard]]
	bool full() const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.full() : m_dynamic_data.full();
	}

	[[nodiscard]]
	size_type size() const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.size() : m_dynamic_data.size();
	}

	[[nodiscard]]
	size_type max_size() const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.max_size() : m_dynamic_data.max_size();
	}

	void reserve(size_type new_capacity) {
		if (new_capacity <= capacity()) {
			return;
		}
        
        std::cout << "grow" << std::endl;
		
		const bool no_transfer = UsesDynamicMemoryBuffer();
		m_dynamic_data.reserve(new_capacity);
		if (no_transfer) {
			return;
		}
        
        std::cout << "s->d" << std::endl;

		for (size_type i = 0u; i < m_static_data.size(); ++i) {
			m_dynamic_data.push_back(std::move(m_static_data[i]));
		}
	}

	[[nodiscard]]
	size_type capacity() const noexcept {
		return UsesStaticMemoryBuffer() ?
			m_static_data.capacity() : m_dynamic_data.capacity();
	}

	//---------------------------------------------------------------------
	// Member Methods: Modifiers
	//---------------------------------------------------------------------

	void push_back(const T& value) {
		emplace_back(value);
	}

	void push_back(T&& value) {
		emplace_back(std::move(value));
	}

	template< typename... Args >
	void emplace_back(Args&&... args) {
		if (UsesStaticMemoryBuffer()) {
            std::cout << 's';
			m_static_data.emplace_back(std::forward< Args >(args)...);
		}
		else {
            std::cout << 'd';
			m_dynamic_data.emplace_back(std::forward< Args >(args)...);
		}
	}

	void swap(MemoryBuffer& other) noexcept {
		std::swap(m_static_data,  other.m_static_data);
		std::swap(m_dynamic_data, other.m_dynamic_data);
	}

private:
	
	//---------------------------------------------------------------------
	// Member Variables
	//---------------------------------------------------------------------

	StaticMemoryBuffer< T, StaticCapacity > m_static_data;
	DynamicMemoryBuffer< T > m_dynamic_data;
};

int main() {
    //StaticMemoryBuffer< std::size_t, 5u > buffer;
    //DynamicMemoryBuffer< std::size_t > buffer(5u);
    
    MemoryBuffer< std::size_t, 5u > buffer;
    for (std::size_t i = 0u; i <= buffer.capacity(); ++i) {
        buffer.push_back(i);
        std::cout << std::endl;
        
        for (auto e : buffer) {
            std::cout << e << ' ';
        }
        std::cout << std::endl;
    }

    buffer.reserve(10);
    for (auto e : buffer) {
        std::cout << e << ' ';
    }
    std::cout << std::endl;
    
    buffer.push_back(5);
    std::cout << std::endl;
    for (auto e : buffer) {
        std::cout << e << ' ';
    }
    std::cout << std::endl;
    
    return 0;
}
