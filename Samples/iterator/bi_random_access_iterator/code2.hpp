#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

template< typename FirstT, typename SecondT >
class BiValue {
    
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
    friend constexpr bool operator==(const BiValue& lhs, const int& rhs) noexcept {
        return *lhs.m_it1 == rhs;
    }
    [[nodiscard]]
    friend constexpr bool operator!=(const BiValue& lhs, const int& rhs) noexcept {
        return *lhs.m_it1 != rhs;
    }
    [[nodiscard]]
    friend constexpr bool operator<=(const BiValue& lhs, const int& rhs) noexcept {
        return *lhs.m_it1 <= rhs;
    }
    [[nodiscard]]
    friend constexpr bool operator>=(const BiValue& lhs, const int& rhs) noexcept {
        return *lhs.m_it1 >= rhs;
    }
    [[nodiscard]]
    friend constexpr bool operator<(const BiValue& lhs, const int& rhs) noexcept {
        return *lhs.m_it1 < rhs;
    }
    [[nodiscard]]
    friend constexpr bool operator>(const BiValue& lhs, const int& rhs) noexcept {
        return *lhs.m_it1 > rhs;
    }
    
    [[nodiscard]]
    friend constexpr bool operator==(const int& lhs, const BiValue& rhs) noexcept {
        return lhs == *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr bool operator!=(const int& lhs, const BiValue& rhs) noexcept {
        return lhs != *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr bool operator<=(const int& lhs, const BiValue& rhs) noexcept {
        return lhs <= *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr bool operator>=(const int& lhs, const BiValue& rhs) noexcept {
        return lhs >= *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr bool operator<(const int& lhs, const BiValue& rhs) noexcept {
        return lhs < *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr bool operator>(const int& lhs, const BiValue& rhs) noexcept {
        return lhs > *rhs.m_it1;
    }
    
    [[nodiscard]]
    friend constexpr bool operator==(const BiValue& lhs, const BiValue& rhs) noexcept {
        return *lhs.m_it1 == *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr bool operator!=(const BiValue& lhs, const BiValue& rhs) noexcept {
        return *lhs.m_it1 != *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr bool operator<=(const BiValue& lhs, const BiValue& rhs) noexcept {
        return *lhs.m_it1 <= *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr bool operator>=(const BiValue& lhs, const BiValue& rhs) noexcept {
        return *lhs.m_it1 >= *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr bool operator<(const BiValue& lhs, const BiValue& rhs) noexcept {
        return *lhs.m_it1 < *rhs.m_it1;
    }
    [[nodiscard]]
    friend constexpr bool operator>(const BiValue& lhs, const BiValue& rhs) noexcept {
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
    
    BiRandomAccessIterator() noexcept
        : m_it1{}, m_it2{} {}
    BiRandomAccessIterator(FirstT it1, SecondT it2) noexcept
        : m_it1(std::move(it1)), m_it2(std::move(it2)) {}
    BiRandomAccessIterator(const BiRandomAccessIterator& bit) = default;
    BiRandomAccessIterator(BiRandomAccessIterator&& bit) noexcept = default;
    ~BiRandomAccessIterator() = default;

    BiRandomAccessIterator& operator=(const BiRandomAccessIterator& bit) = default;
    BiRandomAccessIterator& operator=(BiRandomAccessIterator&& bit) noexcept = default;

    auto operator*() noexcept {
        return make_bi_value(m_it1, m_it2);
    }
    auto operator*() const noexcept {
        return make_bi_value(m_it1, m_it2);
    }
    [[nodiscard]]
    auto operator[](std::size_t n) noexcept {
        return make_bi_value(m_it1 + n, m_it2 + n);
    }
    [[nodiscard]]
    auto operator[](std::size_t n) const noexcept {
        return make_bi_value(m_it1 + n, m_it2 + n);
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
    friend const BiRandomAccessIterator operator++(const BiRandomAccessIterator& bit) {
        return { bit.m_it1 + 1u, bit.m_it2 + 1u };
    }
    [[nodiscard]]
    friend const BiRandomAccessIterator operator--(const BiRandomAccessIterator& bit) {
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
    
private:

    FirstT  m_it1;
    SecondT m_it2;
};


int main() {
    std::vector< int > a = { 5, 4, 3, 2, 1 };
    std::vector< int > b = { 5, 4, 3, 2, 1 };
    
    BiRandomAccessIterator begin = { a.begin(), b.begin() };
    BiRandomAccessIterator end   = { a.end(),   b.end()   };
    std::remove(begin, end, 5);
    
    for (auto e : a) {
        std::cout << e;
    }
    std::cout << std::endl;
    for (auto e : b) {
        std::cout << e;
    }
    
    return 0;
}
