// TODO: update

// std::remove
#include <algorithm>
// std::size_t
#include <cstddef>
// std::ref
#include <functional>
// std::cout
// std::endl
#include <iostream>
// std::make_pair
// std::move
// std::pair
#include <utility>
// std::vector
#include <vector>

template< typename FirstT, typename SecondT >
class BiRandomAccessIterator
{

public:

    BiRandomAccessIterator()
        noexcept = default;

    BiRandomAccessIterator(FirstT it1, SecondT it2)
        noexcept
        : m_it1(std::move(it1))
        , m_it2(std::move(it2))
    {}

    BiRandomAccessIterator(const BiRandomAccessIterator& src)
        noexcept = default;

    BiRandomAccessIterator(BiRandomAccessIterator&& src)
        noexcept = default;

    ~BiRandomAccessIterator() = default;

    auto operator =(const BiRandomAccessIterator& src)
        noexcept -> BiRandomAccessIterator& = default;

    auto operator =(BiRandomAccessIterator&& src)
        noexcept -> BiRandomAccessIterator& = default;

    [[nodiscard]]
    auto operator *() const
        noexcept
    {
        return std::make_pair(std::ref(*m_it1), std::ref(*m_it2));
    }

    auto operator ->() const
        noexcept
    {
        return std::make_pair(&*m_it1, &*m_it2);
    }

    [[nodiscard]]
    auto operator -(const BiRandomAccessIterator& bit) const
        -> std::size_t
    {
        return m_it1 - bit.m_it1;
    }

    [[nodiscard]]
    auto operator +(std::size_t n) const
        noexcept -> BiRandomAccessIterator
    {
        return { m_it1 + n, m_it2 + n };
    }

    [[nodiscard]]
    auto operator -(std::size_t n) const
        noexcept -> BiRandomAccessIterator
    {
        return { m_it1 - n, m_it2 - n };
    }

    [[nodiscard]]
    friend auto operator +(std::size_t n, const BiRandomAccessIterator& bit)
        noexcept -> BiRandomAccessIterator
    {
        return bit + n;
    }

    auto operator ++()
        noexcept -> BiRandomAccessIterator&
    {
        ++m_it1;
        ++m_it2;
        return *this;
    }

    auto operator --()
        noexcept -> BiRandomAccessIterator&
    {
        --m_it1;
        --m_it2;
        return *this;
    }

    [[nodiscard]]
    friend auto operator ++(const BiRandomAccessIterator& bit)
        noexcept -> BiRandomAccessIterator
    {
        return { bit.m_it1 + 1, bit.m_it2 + 1 };
    }

    [[nodiscard]]
    friend auto operator --(const BiRandomAccessIterator& bit)
        noexcept -> BiRandomAccessIterator
    {
        return { bit.m_it1 - 1, bit.m_it2 - 1 };
    }

    auto operator +=(std::size_t n)
        -> BiRandomAccessIterator&
    {
        m_it1 += n;
        m_it2 += n;
        return *this;
    }

    auto operator -=(std::size_t n)
        -> BiRandomAccessIterator&
    {
        m_it1 -= n;
        m_it2 -= n;
        return *this;
    }

    [[nodiscard]]
    auto operator [](std::size_t n) const
        noexcept
	{
        return std::make_pair(std::ref(m_it1[n]), std::ref(m_it2[n]));
    }

    [[nodiscard]]
    friend constexpr auto operator ==(const BiRandomAccessIterator& lhs, const BiRandomAccessIterator& rhs) const
        noexcept -> bool = default;

    [[nodiscard]]
    constexpr auto operator <=(const BiRandomAccessIterator& rhs) const
        noexcept -> bool
    {
        return m_it1 <= rhs.m_it1;
    }

    [[nodiscard]]
    constexpr auto operator >=(const BiRandomAccessIterator& rhs) const
        noexcept -> bool
    {
        return m_it1 >= rhs.m_it1;
    }

    [[nodiscard]]
    constexpr auto operator <(const BiRandomAccessIterator& rhs) const
        noexcept -> bool
    {
        return m_it1 < rhs.m_it1;
    }

    [[nodiscard]]
    constexpr auto operator >(const BiRandomAccessIterator& rhs) const
        noexcept -> bool
    {
        return m_it1 > rhs.m_it1;
    }

private:

    FirstT  m_it1;
    SecondT m_it2;
};

auto main()
    -> int
{
    std::vector< int > a = { 5, 4, 3, 2, 1 };
    std::vector< int > b = { 5, 4, 3, 2, 1 };
    
    int i = 5;
    
    BiRandomAccessIterator begin = { a.begin(), b.begin() };
    BiRandomAccessIterator end   = { a.end(),   b.end()   };
    //std::remove(begin, end, std::pair< int, int >(5,5));
    std::remove(begin, end, std::make_pair(std::ref(i), std::ref(i)));
    
    for (auto e : a)
	{
        std::cout << e;
    }
    std::cout << std::endl;
    for (auto e : b)
	{
        std::cout << e;
    }
    
    return 0;
}
