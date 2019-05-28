#include <iostream>

#define EVER ;;

int main() {
    int i = 0;
    for (EVER) {
        
        std::cout << i++ << std::endl;
        
        if (i > 5) {
            break;
        }
    }
    
    return 0;
}
