// cout, endl
#include <iostream>

int main()
{
	int a = 5;
    int b = 2;

    std::cout << a - b * (a / b) << std::endl;
    std::cout << a % b << std::endl;

    a = -5;
    b = 2;

    std::cout << a - b * (a / b) << std::endl;
    std::cout << a % b << std::endl;

    a = 5;
    b = -2;

    std::cout << a - b * (a / b) << std::endl;
    std::cout << a % b << std::endl;

    a = -5;
    b = -2;

    std::cout << a - b * (a / b) << std::endl;
    std::cout << a % b << std::endl;
	
    return 0;
}
