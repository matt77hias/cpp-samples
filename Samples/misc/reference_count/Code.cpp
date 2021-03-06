// TODO: update

#include <atomic>
#include <iostream>
#include <type_traits>

class ReferenceCounted {

public:

	std::uint32_t IncrementReferenceCount() noexcept {
		return ++m_reference_count;
	}
	std::uint32_t DecrementReferenceCount() noexcept {
		return --m_reference_count;
	}

protected:

	ReferenceCounted() 
		: m_reference_count(0u) {}
		
private:

	std::atomic< std::uint32_t > m_reference_count;
};

template < typename T, 
           typename = std::enable_if_t< std::is_base_of_v< ReferenceCounted, T > > >
class Reference final {

public:

	Reference(T* ptr = nullptr) noexcept 
		: m_ptr(ptr) {
			
		if (m_ptr) {
			m_ptr->IncrementReferenceCount();
		}
	}
	
	explicit Reference(const Reference< T >& ref) noexcept 
		: Reference(ref.m_ptr) {}
	
	~Reference() {
		if (m_ptr && 0u == m_ptr->DecrementReferenceCount()) {
			delete m_ptr;
		}
	}
	
	Reference& operator=(T* ptr) {
		if (ptr) {
			ptr->IncrementReferenceCount();
		}
		if (m_ptr && 0u == m_ptr->DecrementReferenceCount()) {
			delete m_ptr;
		}
		m_ptr = ptr;
		return *this;
	}

	Reference& operator=(const Reference< T >& ref) {
		return operator=(ref.m_ptr);
	}

	T* operator->() noexcept { 
		return m_ptr; 
	}
	
	const T* operator->() const noexcept { 
		return m_ptr; 
	}
    
    T* GetPtr() noexcept { 
		return m_ptr; 
	}

	const T* GetPtr() const noexcept { 
		return m_ptr; 
	}

	operator bool() const noexcept { 
		return nullptr != m_ptr; 
	}

private:

	T *m_ptr;
};

struct A : ReferenceCounted {
    A() { 
        std::cout << "A::A()" << std::endl; 
    }
    A(const A&) noexcept { 
        std::cout << "A::A(const A&)" << std::endl; 
    }
    A& operator=(const A&) noexcept { 
        std::cout << "A::perator=(const A&)" << std::endl; 
        return *this; 
    }
    ~A() noexcept { 
        std::cout << "A::~A()" << std::endl; 
    }
};

int main() {
    auto a1 = new A;
    auto a2 = new A;
    Reference< A > ref1(a1);
    Reference< A > ref2 = ref1;
    ref1 = a2;
    ref2 = a2;
    std::cout << "only a2 is alive" << std::endl;
    ref1 = nullptr;
    ref2 = ref1;
    std::cout << "a2 is dead" << std::endl;
    return 0;
}
