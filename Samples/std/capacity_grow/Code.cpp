// cout. endl
#include <iostream>
// vector
#include <vector>

auto main()
    -> int
{
    std::vector< int > v1 = { 1, 2, 3 };
    std::cout << v1.capacity() << std::endl;

    std::vector< int > v2;
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(3);
    std::cout << v2.capacity() << std::endl;
    
    return 0;
}
