// deque
#include <deque>

template< typename T >
struct Widget : T
{
    using typename T::size_type;
    
    void reserve(size_type capacity)
        requires(requires(T t, size_type c) { t.reserve(c); });
};

template< typename T >
void Widget< T >
    ::reserve(size_type capacity)
    requires(requires(T t, size_type c) { t.reserve(c); })
{
        T::reserve(capacity);
}

int main()
{
    Widget< std::deque< int > > widget;
    //widget.reserve(2u);

    return 0;
}
