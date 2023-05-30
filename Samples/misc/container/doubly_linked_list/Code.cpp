// size_t
#include <cstddef>
// count, endl
#include <iostream>

template< typename T >
class LinkedList
{

public:

	struct LinkedListElement
	{

	public:

		[[nodiscard]]
		explicit LinkedListElement(T* data)
			noexcept 
			: m_data(data)
		{}

		~LinkedListElement()
		{
			delete m_data;

			if (m_next != nullptr)
			{
				m_next->m_prev = m_prev;
			}
			if (m_prev != nullptr)
			{
				m_prev->m_next = m_next;
			}
		}

		T* m_data;
		LinkedListElement* m_next = {};
		LinkedListElement* m_prev = {};
	};

	[[nodiscard]]
	LinkedList()
		noexcept = default;

	~LinkedList()
		noexcept
	{
		Empty();
	}

	auto Add(T* data)
		-> T*
	{
		if (!data)
		{
			return {};
		}

		if (m_first == nullptr)
		{
			m_first = new LinkedListElement(data);
			m_last  = m_first;
		}
		else
		{
			m_last->m_next = new LinkedListElement(data);
			m_last->m_next->m_prev = m_last;
			m_last = m_last->m_next;
		}

		++m_size;

		return m_last->m_data;
	}
	
	auto InsertBefore(T* data, LinkedListElement* element_next)
		-> T*
	{
        if (data == nullptr)
		{
			return {};
		}
        
        ++m_size;
        
		const auto current = element_next->m_prev;
		if (current == nullptr)
		{
			m_first = new LinkedListElement(data);
			m_first->m_next = element_next;
			element_next->m_prev = m_first;
			return m_first->m_data;
		}
		else
		{
			current->m_next = new LinkedListElement(data);
			current->m_next->m_prev = current;
			current->m_next->m_next = element_next;
			element_next->m_prev = current->m_next;
			return current->m_next->m_data;
		}
	}
	
	auto InsertAfter(T* data, LinkedListElement* element_prev)
		-> T*
	{
        if (data == nullptr)
		{
			return {};
		}
        
        ++m_size;
        
		const auto current = element_prev->m_next;
		if (current == nullptr)
		{
			m_last = new LinkedListElement(data);
			m_last->m_prev = element_prev;
			element_prev->m_next = m_last;
			return m_last->m_data;
		}
		else
		{
			current->m_prev = new LinkedListElement(data);
			current->m_prev->m_next = current;
			current->m_prev->m_prev = element_prev;
			element_prev->m_next = current->m_prev;
			return current->m_prev->m_data;
		}
	}

	void Remove(T* data, bool data_destruction = true)
	{
        for (auto current = m_first; nullptr != current; current = current->m_next)
		{
			if (data != current->m_data)
			{
                continue;
            }
            
            if (m_first == current)
			{
                m_first = m_first->m_next;
				if (m_first)
				{
                    m_first->m_prev = nullptr;
                }
			}
            
            if (m_last == current)
			{
                m_last = m_last->m_prev;
                if (m_last)
				{
                    m_last->m_next = nullptr;
				}
            }
            
            if (!data_destruction)
			{
                current->m_data = nullptr;
			}
			
            delete current;
            --m_size;
            break;
		}
	}

	void Empty(bool data_destruction = true)
	{
		while (nullptr != m_last)
		{
			const auto current = m_last;
			m_last = m_last->m_prev;

			if (!data_destruction)
			{
				current->m_data = nullptr;
			}
			else
			{
                delete current;
            }
		}
        
		m_first = {};
        m_last  = {};
		m_size  = {};
	}

	[[nodiscard]]
	auto GetFirst() const
		noexcept -> T*
	{
		return m_first ? m_first->m_data : nullptr;
	}
    
	[[nodiscard]]
	auto GetLast() const
		noexcept -> T*
	{
		return m_last ? m_last->m_data : nullptr;
	}
    
	[[nodiscard]]
	auto GetPrevious(const T* data) const
		noexcept -> T*
	{
		const auto element = GetCompleteLinkedListElement(data);
        if (element == nullptr)
		{
           return nullptr; 
        }
        
        const auto element_prev = element->m_prev;
        return element_prev ? element_prev->m_data : nullptr;
	}

	[[nodiscard]]
	auto GetNext(const T* data) const
		noexcept -> T*
	{
        const auto element = GetCompleteLinkedListElement(data);
        if (element == nullptr)
		{
           return nullptr; 
        }
        
        const auto element_next = element->m_next;
        return element_next ? element_next->m_data : nullptr;
	}

	[[nodiscard]]
	auto GetAt(size_t index) const
		noexcept -> T*
	{
		if (index >= m_size)
		{
			return nullptr;
		}

		auto current = m_first;
		for (size_t i = 0; i < index; ++i)
		{
			current = current->m_next;
        }
		return current->m_data;
	}

	[[nodiscard]]
	auto GetCompleteLinkedListElement(const T* data) const
		noexcept -> LinkedListElement*
	{
		for (auto current = m_first; current != nullptr; current = current->m_next)
		{
			if (data == current->m_data)
			{
				return current;
			}
		}
		return {};
	}

	[[nodiscard]]
	auto GetSize() const
		noexcept -> std::size_t
	{
		return m_size;
	}

private:
	
	LinkedListElement* m_first = {};
	LinkedListElement* m_last = {};
	std::size_t m_size = {};
};

auto main()
	-> int
{
    const auto i1 = new int(1);
    const auto i2 = new int(2);
    const auto i3 = new int(3);
    
    LinkedList< int > list;
    list.Add(i1);
    list.Add(i3);
    list.InsertBefore(i2, list.GetCompleteLinkedListElement(i3));
    list.Remove(i1);
    
    std::cout << *list.GetAt(0) << std::endl;
    return 0;
}
