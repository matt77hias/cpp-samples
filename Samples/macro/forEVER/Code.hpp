// cout, endl
#include <iostream>

#define EVER ;;

int main()
{
    int i = 0;
    for (EVER)
    {
        
        std::cout << i++ << std::endl;
        
        if (5 < i)
        {
            break;
        }
    }
    
    return 0;
}
