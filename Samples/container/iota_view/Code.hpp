// assert
#include <cassert>
// weak_ordering
#include <compare>
// ptrdiff_t, size_t
#include <cstddef>
// cout
#include <iostream>
// random_access_iterator_tag, reverse_iterator
#include <iterator>

//-----------------------------------------------------------------------------
// Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage
{
	//-------------------------------------------------------------------------
	// IotaView
	//-------------------------------------------------------------------------
	
	class IotaView
	{
	
	public:

		//---------------------------------------------------------------------
		// Forward Declarations
		//---------------------------------------------------------------------

		class Iterator;

		//---------------------------------------------------------------------
		// Class Member Types
		//---------------------------------------------------------------------

		using value_type = std::size_t;

		using size_type = std::size_t;

		using difference_type = std::ptrdiff_t;

		using reference = value_type;

		using const_reference = reference;

		using pointer = void;

		using const_pointer = pointer;

		using iterator = Iterator;

		using const_iterator = iterator;

		using reverse_iterator = std::reverse_iterator< iterator >;

		using const_reverse_iterator = reverse_iterator;

		//---------------------------------------------------------------------
		// Iterator
		//---------------------------------------------------------------------

		class Iterator
		{

		public:

			//-----------------------------------------------------------------
			// Class Member Types
			//-----------------------------------------------------------------

			using value_type = IotaView::value_type;

			using reference = IotaView::reference;

			using pointer = IotaView::pointer;

			using size_type = IotaView::size_type;

			using difference_type = IotaView::difference_type;

			using iterator_category = std::random_access_iterator_tag;

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			[[nodiscard]]
			constexpr Iterator() noexcept = default;

			[[nodiscard]]
			constexpr Iterator(value_type offset, size_type index) noexcept
				: m_offset(offset)
				, m_index(index)
			{}

			[[nodiscard]]
			constexpr Iterator(const Iterator& rhs) noexcept = default;

			[[nodiscard]]
			constexpr Iterator(Iterator&& rhs) noexcept = default;

			~Iterator() = default;

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			constexpr Iterator&
				operator =(const Iterator& rhs) noexcept = default;

			constexpr Iterator&
				operator =(Iterator&& rhs) noexcept = default;

			//-----------------------------------------------------------------
			// Member Methods
			//-----------------------------------------------------------------

			[[nodiscard]]
			constexpr reference operator *() const noexcept
			{
				return operator [](0);
			}

			pointer operator ->() const = delete;

			[[nodiscard]]
			constexpr reference operator [](difference_type n) const noexcept
			{
				assert((0 <= n) || (-n <= static_cast< difference_type >(m_index)));
				return m_offset + (m_index + n);
			}

			[[nodiscard]]
			constexpr difference_type
				operator -(const Iterator& it) const noexcept
			{
				return static_cast< difference_type >(m_index)
					 - static_cast< difference_type >(it.m_index);
			}

			[[nodiscard]]
			constexpr Iterator
				operator +(difference_type n) const noexcept
			{
				assert((0 <= n) || (-n <= static_cast< difference_type >(m_index)));
				return { m_offset, m_index + n };
			}

			[[nodiscard]]
			constexpr Iterator
				operator -(difference_type n) const noexcept
			{
				assert((n <= 0) || (n <= static_cast< difference_type >(m_index)));
				return { m_offset, m_index - n };
			}

			[[nodiscard]]
			friend constexpr Iterator
				operator +(difference_type n, const Iterator& it) noexcept
			{
				return it + n;
			}

			constexpr Iterator& operator ++() noexcept
			{
				++m_index;
				return *this;
			}

			constexpr Iterator& operator --() noexcept
			{
				assert(0u < m_index);
				--m_index;
				return *this;
			}

			[[nodiscard]]
			friend constexpr Iterator
				operator ++(const Iterator& it) noexcept
			{
				return { it.m_offset, it.m_index + 1u };
			}

			[[nodiscard]]
			friend constexpr Iterator
				operator --(const Iterator& it) noexcept
			{
				assert(0u < it.m_index);
				return { it.m_offset, it.m_index - 1u };
			}

			constexpr Iterator& operator +=(difference_type n) noexcept
			{
				assert((0 <= n) || (-n <= static_cast< difference_type >(m_index)));
				m_index += n;
				return *this;
			}

			constexpr Iterator& operator -=(difference_type n) noexcept
			{
				assert((n <= 0) || (n <= static_cast< difference_type >(m_index)));
				m_index -= n;
				return *this;
			}

            [[nodiscard]]
		    constexpr bool
			    operator ==(const Iterator& rhs) const noexcept = default;

			[[nodiscard]]
			constexpr std::weak_ordering
				operator <=>(const Iterator& rhs) const noexcept
			{
				return m_index <=> rhs.m_index;
			}

		private:

			//-----------------------------------------------------------------
			// Member Variables
			//-----------------------------------------------------------------

			value_type m_offset = {};

			size_type m_index = {};
		};

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		[[nodiscard]]
		constexpr IotaView() noexcept = default;

		[[nodiscard]]
		constexpr IotaView(value_type offset, size_type count) noexcept
			: m_offset(offset)
			, m_count(count)
		{}

		[[nodiscard]]
		constexpr IotaView(const IotaView& rhs) noexcept = default;

		[[nodiscard]]
		constexpr IotaView(IotaView&& rhs) noexcept = default;

		~IotaView() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		constexpr IotaView&
			operator =(const IotaView& rhs) noexcept = default;

		constexpr IotaView&
			operator =(IotaView&& rhs) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		constexpr bool
			operator ==(const IotaView& rhs) const noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods: Element Access
		//---------------------------------------------------------------------

		[[nodiscard]]
		constexpr const_reference operator [](size_type index) const noexcept
		{
			assert(index < size());
			return *(begin() + index);
		}

		[[nodiscard]]
		constexpr const_reference front() const noexcept
		{
			assert(empty() == false);
			return (*this)[0u];
		}

		[[nodiscard]]
		constexpr const_reference back() const noexcept
		{
			assert(empty() == false);
			return (*this)[size() - 1u];
		}

		//---------------------------------------------------------------------
		// Member Methods: Iterators
		//---------------------------------------------------------------------

		[[nodiscard]]
		constexpr const_iterator begin() const noexcept
		{
			return { m_offset, 0u };
		}

		[[nodiscard]]
		constexpr const_iterator cbegin() const noexcept
		{
			return begin();
		}

		[[nodiscard]]
		constexpr const_iterator end() const noexcept
		{
			return { m_offset, size() };
		}

		[[nodiscard]]
		constexpr const_iterator cend() const noexcept
		{
			return end();
		}

		[[nodiscard]]
		constexpr const_reverse_iterator rbegin() const noexcept
		{
			return reverse_iterator(end());
		}

		[[nodiscard]]
		constexpr const_reverse_iterator crbegin() const noexcept
		{
			return reverse_iterator(cend());
		}

		[[nodiscard]]
		constexpr const_reverse_iterator rend() const noexcept
		{
			return reverse_iterator(begin());
		}

		[[nodiscard]]
		constexpr const_reverse_iterator crend() const noexcept
		{
			return reverse_iterator(cbegin());
		}

		//---------------------------------------------------------------------
		// Member Methods: Capacity
		//---------------------------------------------------------------------

		[[nodiscard]]
		constexpr bool empty() const noexcept
		{
			return size() == size_type{};
		}

		[[nodiscard]]
		constexpr size_type size() const noexcept
		{
			return m_count;
		}

		[[nodiscard]]
		constexpr size_type max_size() const noexcept
		{
			return size();
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		value_type m_offset = {};

		size_type m_count = {};
	};
}
 
int main()
{
    mage::IotaView range = { 0u, 10u };
    for (auto element : range)
    {
        std::cout << element;
    }

    return 0;
}
