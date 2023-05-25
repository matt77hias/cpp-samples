// TODO: update

// atomic
#include <atomic>
// uint32_t
#include <cstdint>
// cout, endl
#include <iostream>
// enable_if_t, is_base_of_v
#include <type_traits>

class ReferenceCounted
{

public:

	auto IncrementReferenceCount()
		noexcept -> std::uint32_t
	{
		return ++m_reference_count;
	}

	auto DecrementReferenceCount()
		noexcept -> std::uint32_t
	{
		return --m_reference_count;
	}

protected:

	[[nodiscard]]
	ReferenceCounted()
		noexcept = default;
		
private:

	std::atomic< std::uint32_t > m_reference_count = {};
};

template < typename T, 
           typename = std::enable_if_t< std::is_base_of_v< ReferenceCounted, T > > >
class Reference final
{

public:

	[[nodiscard]]
	Reference(T* ptr = nullptr)
		noexcept 
		: m_ptr(ptr)
	{
		if (m_ptr != nullptr)
		{
			m_ptr->IncrementReferenceCount();
		}
	}
	
	[[nodiscard]]
	explicit Reference(const Reference< T >& ref)
		noexcept 
		: Reference(ref.m_ptr)
	{}
	
	~Reference()
	{
		if ((m_ptr != nullptr) and (m_ptr->DecrementReferenceCount() == 0u))
		{
			delete m_ptr;
		}
	}
	
	auto operator =(T* ptr)
		noexcept -> Reference&
	{
		if (m_ptr != nullptr)
		{
			ptr->IncrementReferenceCount();
		}
		if ((m_ptr != nullptr) and (m_ptr->DecrementReferenceCount() == 0u))
		{
			delete m_ptr;
		}
		m_ptr = ptr;
		return *this;
	}

	auto operator =(const Reference< T >& ref)
		noexcept -> Reference&
	{
		return operator =(ref.m_ptr);
	}

	auto operator ->()
		noexcept -> T*
	{ 
		return m_ptr; 
	}
	
	auto operator ->() const
		noexcept -> const T*
	{ 
		return m_ptr; 
	}
    
    auto GetPtr()
		noexcept -> T*
	{ 
		return m_ptr; 
	}

	auto GetPtr() const
		noexcept -> const T*
	{ 
		return m_ptr; 
	}

	operator bool() const
		noexcept
	{ 
		return m_ptr != nullptr; 
	}

private:

	T* m_ptr;
};

struct A : ReferenceCounted
{
    A()
	{ 
        std::cout << "A::A()" << std::endl; 
    }

    A(const A&)
		noexcept
	{ 
        std::cout << "A::A(const A&)" << std::endl; 
    }

    auto operator =(const A&)
		noexcept -> A&
	{ 
        std::cout << "A::operator =(const A&)" << std::endl; 
        return *this; 
    }

    ~A()
		noexcept
	{ 
        std::cout << "A::~A()" << std::endl; 
    }
};

auto main()
	-> int
{
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
