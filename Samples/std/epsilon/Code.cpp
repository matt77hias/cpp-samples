// std::cout
// std::endl
#include <iostream>
// std::numeric_limits
#include <limits>

auto main()
	-> int
{
    std::cout << std::numeric_limits< float >::epsilon() << std::endl;
    std::cout << std::numeric_limits< int >::epsilon()   << std::endl;
    
    return 0;
}
