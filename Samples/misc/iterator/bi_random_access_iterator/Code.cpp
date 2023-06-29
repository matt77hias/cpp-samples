// TODO: update

#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

template< typename FirstT, typename SecondT >
class BiRandomAccessIterator {

public:

    BiRandomAccessIterator() noexcept
        : m_it1{}, m_it2{} {}
    BiRandomAccessIterator(FirstT it1, SecondT it2) noexcept
        : m_it1(std::move(it1)), m_it2(std::move(it2)) {}
    BiRandomAccessIterator(const BiRandomAccessIterator& it) = default;
    BiRandomAccessIterator(BiRandomAccessIterator&& it) = default;
    ~BiRandomAccessIterator() = default;

    BiRandomAccessIterator& operator=(const BiRandomAccessIterator& it) = default;
    BiRandomAccessIterator& operator=(BiRandomAccessIterator&& it) = default;

    auto operator*() noexcept {
        return std::make_pair(std::ref(*m_it1), std::ref(*m_it2));
    }

    auto operator*() const noexcept {
        return std::make_pair(std::cref(*m_it1), std::cref(*m_it2));
    }

    auto operator->() noexcept {
        return std::make_pair(&*m_it1, &*m_it2);
    }

    auto operator->() const noexcept {
        return std::make_pair(&*m_it1, &*m_it2);
    }

    [[nodiscard]]
    std::size_t operator-(const BiRandomAccessIterator& bit) const {
        return m_it1 - bit.m_it1;
    }

    [[nodiscard]]
    const BiRandomAccessIterator operator+(std::size_t n) const {
        return { m_it1 + n, m_it2 + n };
    }

    [[nodiscard]]
    const BiRandomAccessIterator operator-(std::size_t n) const {
        return { m_it1 - n, m_it2 - n };
    }

    [[nodiscard]]
    friend const BiRandomAccessIterator 
        operator+(std::size_t n, const BiRandomAccessIterator& bit) {

        return bit + n;
    }

    BiRandomAccessIterator& operator++() {
        ++m_it1;
        ++m_it2;
        return *this;
    }

    BiRandomAccessIterator& operator--() {
        --m_it1;
        --m_it2;
        return *this;
    }

    [[nodiscard]]
    friend const BiRandomAccessIterator 
        operator++(const BiRandomAccessIterator& bit) {

        return { bit.m_it1 + 1u, bit.m_it2 + 1u };
    }

    [[nodiscard]]
    friend const BiRandomAccessIterator 
        operator--(const BiRandomAccessIterator& bit) {

        return { bit.m_it1 - 1u, bit.m_it2 - 1u };
    }

    BiRandomAccessIterator& operator+=(std::size_t n) {
        m_it1 += n;
        m_it2 += n;
        return *this;
    }

    BiRandomAccessIterator& operator-=(std::size_t n) {
        m_it1 -= n;
        m_it2 -= n;
        return *this;
    }

    [[nodiscard]]
    auto operator[](std::size_t n) noexcept {
        return std::make_pair(std::ref(m_it1[n]), std::ref(m_it2[n]));
    }

    [[nodiscard]]
    auto operator[](std::size_t n) const noexcept {
        return std::make_pair(std::cref(m_it1[n]), std::cref(m_it2[n]));
    }

    [[nodiscard]]
    constexpr bool operator==(const BiRandomAccessIterator& rhs) const noexcept {
        return m_it1 == rhs.m_it1;
    }

    [[nodiscard]]
    constexpr bool operator!=(const BiRandomAccessIterator& rhs) const noexcept {
        return m_it1 != rhs.m_it1;
    }

    [[nodiscard]]
    constexpr bool operator<=(const BiRandomAccessIterator& rhs) const noexcept {
        return m_it1 <= rhs.m_it1;
    }

    [[nodiscard]]
    constexpr bool operator>=(const BiRandomAccessIterator& rhs) const noexcept {
        return m_it1 >= rhs.m_it1;
    }

    [[nodiscard]]
    constexpr bool operator<(const BiRandomAccessIterator& rhs) const noexcept {
        return m_it1 < rhs.m_it1;
    }

    [[nodiscard]]
    constexpr bool operator>(const BiRandomAccessIterator& rhs) const noexcept {
        return m_it1 > rhs.m_it1;
    }

    void swap(BiRandomAccessIterator& other) noexcept {
        std::swap(m_it1, other.m_it1);
        std::swap(m_it2, other.m_it2);
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
