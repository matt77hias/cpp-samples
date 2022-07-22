// cout, endl
#include <iostream>

#define EVER ;;

auto main() -> int
{
    int i = 0;
    for (EVER)
    {
        
        std::cout << i++ << std::endl;
        
        if (i > 5)
        {
            break;
        }
    }
    
    return 0;
}
