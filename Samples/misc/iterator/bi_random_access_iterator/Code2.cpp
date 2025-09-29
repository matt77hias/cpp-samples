// TODO: update

// std::remove
#include <algorithm>
// std::ptrdiff_t
#include <cstddef>
// std::cout
// std::endl
#include <iostream>
// std::move
// std::swap
#include <utility>
// std::vector
#include <vector>

template< typename FirstT, typename SecondT >
class BiValue
{
    
public:
    
    BiValue() noexcept
        : m_it1{}, m_it2{} {}
    BiValue(FirstT it1, SecondT it2) noexcept
        : m_it1(std::move(it1)), m_it2(std::move(it2)) {}
    BiValue(const BiValue& value) 
        : m_it1(*value.m_it1), m_it2(*value.m_it2) {}
    BiValue(BiValue&& value) noexcept 
        : m_it1(std::move(*value.m_it1)), m_it2(std::move(*value.m_it2)) {} 
    ~BiValue() = default;

    BiValue& operator=(const BiValue& value) {
        *m_it1 = *value.m_it1;
        *m_it2 = *value.m_it2;
        return *this;
    }
    BiValue& operator=(BiValue&& value) noexcept {
        *m_it1 = std::move(*value.m_it1);
        *m_it2 = std::move(*value.m_it2);
        return *this;
    }
    
    [[nodiscard]]
    friend constexpr auto operator ==(const BiValue& lhs, const int& rhs)
		noexcept -> bool
    {
        return *lhs.m_it1 == rhs;
    }
    [[nodiscard]]
    friend constexpr auto operator !=(const BiValue& lhs, const int& rhs)
		noexcept -> bool
    {
        return *lhs.m_it1 != rhs;
    }
    [[nodiscard]]
    friend constexpr auto operator <=(const BiValue& lhs, const int& rhs)
		noexcept -> bool
    {
        return *lhs.m_it1 <= rhs;
    }
    [[nodiscard]]
    friend constexpr auto operator >=(const BiValue& lhs, const int& rhs)
		noexcept -> bool
    {
        return *lhs.m_it1 >= rhs;
    }
    [[nodiscard]]
    friend constexpr auto operator <(const BiValue& lhs, const int& rhs)
		noexcept -> bool
    {
        return *lhs.m_it1 < rhs;
    }
    [[nodiscard]]
    friend constexpr auto operator >(const BiValue& lhs, const int& rhs)
		noexcept -> bool
    {
        return *lhs.m_it1 > rhs;
    }
    
    [[nodiscard]]
    friend constexpr auto operator ==(const int& lhs, const BiValue& rhs)
		noexcept -> bool
    {
        return lhs == *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr auto operator !=(const int& lhs, const BiValue& rhs)
		noexcept -> bool
    {
        return lhs != *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr auto operator <=(const int& lhs, const BiValue& rhs)
		noexcept -> bool
    {
        return lhs <= *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr auto operator >=(const int& lhs, const BiValue& rhs)
		noexcept -> bool
    {
        return lhs >= *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr auto operator <(const int& lhs, const BiValue& rhs)
		noexcept -> bool
    {
        return lhs < *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr auto operator >(const int& lhs, const BiValue& rhs)
		noexcept -> bool
    {
        return lhs > *rhs.m_it1;
    }
    
    [[nodiscard]]
    friend constexpr auto operator ==(const BiValue& lhs, const BiValue& rhs)
		noexcept -> bool
    {
        return *lhs.m_it1 == *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr auto operator !=(const BiValue& lhs, const BiValue& rhs)
		noexcept -> bool
    {
        return *lhs.m_it1 != *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr auto operator <=(const BiValue& lhs, const BiValue& rhs)
		noexcept -> bool
    {
        return *lhs.m_it1 <= *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr auto operator >=(const BiValue& lhs, const BiValue& rhs)
		noexcept -> bool
    {
        return *lhs.m_it1 >= *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr auto operator <(const BiValue& lhs, const BiValue& rhs)
		noexcept -> bool
    {
        return *lhs.m_it1 < *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr auto operator >(const BiValue& lhs, const BiValue& rhs)
		noexcept -> bool
    {
        return *lhs.m_it1 > *rhs.m_it1;
    }
    
    void swap(BiValue& other) noexcept {
        std::swap(*m_it1, *other.m_it1);
        std::swap(*m_it2, *other.m_it2);
    }
    
private:

    FirstT  m_it1;
    SecondT m_it2;
};

template< typename FirstT, typename SecondT >
auto make_bi_value(FirstT first, SecondT second) {
    return BiValue< FirstT, SecondT >(std::move(first), std::move(second));
}

namespace std {
  
    template< typename FirstT, typename SecondT >
    void swap(BiValue< FirstT, SecondT >& lhs, BiValue< FirstT, SecondT >& rhs) {
        lhs.swap(rhs);
    }
}

template< typename FirstT, typename SecondT >
class BiRandomAccessIterator {

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
	auto operator *() noexcept
	{
        return make_bi_value(m_it1, m_it2);
    }

    auto operator *() const
        noexcept
	{
        return make_bi_value(m_it1, m_it2);
    }

    [[nodiscard]]
    auto operator [](std::ptrdiff_t n)
        noexcept
	{
        return make_bi_value(m_it1 + n, m_it2 + n);
    }

    [[nodiscard]]
    auto operator [](std::ptrdiff_t n) const
        noexcept
	{
        return make_bi_value(m_it1 + n, m_it2 + n);
    }

    [[nodiscard]]
    std::ptrdiff_t operator-(const BiRandomAccessIterator& bit) const {
        return m_it1 - bit.m_it1;
    }
    [[nodiscard]]
    const BiRandomAccessIterator operator+(std::ptrdiff_t n) const {
        return { m_it1 + n, m_it2 + n };
    }
    [[nodiscard]]
    const BiRandomAccessIterator operator-(std::ptrdiff_t n) const {
        return { m_it1 - n, m_it2 - n };
    }

    [[nodiscard]]
    friend const BiRandomAccessIterator 
        operator+(std::ptrdiff_t n, const BiRandomAccessIterator& bit)
	{
        return bit + n;
    }

    BiRandomAccessIterator& operator++()
	{
        ++m_it1;
        ++m_it2;
        return *this;
    }

    BiRandomAccessIterator& operator--()
	{
        --m_it1;
        --m_it2;
        return *this;
    }

    [[nodiscard]]
    friend const BiRandomAccessIterator operator++(const BiRandomAccessIterator& bit)
	{
        return { bit.m_it1 + 1u, bit.m_it2 + 1u };
    }

    [[nodiscard]]
    friend const BiRandomAccessIterator operator--(const BiRandomAccessIterator& bit)
	{
        return { bit.m_it1 - 1u, bit.m_it2 - 1u };
    }

    BiRandomAccessIterator& operator+=(std::ptrdiff_t n)
	{
        m_it1 += n;
        m_it2 += n;
        return *this;
    }

    BiRandomAccessIterator& operator-=(std::ptrdiff_t n)
	{
        m_it1 -= n;
        m_it2 -= n;
        return *this;
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
    
    BiRandomAccessIterator begin = { a.begin(), b.begin() };
    BiRandomAccessIterator end   = { a.end(),   b.end()   };
    std::remove(begin, end, 5);
    
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
