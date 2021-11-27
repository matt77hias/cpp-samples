// cout
#include <iostream>
// forward_iterator, input_iterator
#include <iterator>

struct Widget
{
    template< std::input_iterator I >
    void f(I it)
    {
        std::cout << "input_iterator: " << *it;
    }

    template< std::forward_iterator I >
    void f(I it)
    {
        std::cout << "forward_iterator: " << *it;
    }
};


auto main()
    -> int
{
    int i = 1;
    Widget w;
    w.f(&i);

    return 0;
}
