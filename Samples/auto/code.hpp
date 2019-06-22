#include <iostream>
 
int& f(int& i) 
{ 
    return i; 
};

int main()
{
    int i = 5;
    auto j = f(i);
    j = 0;
    std::cout << i;
    std::cout << ' ';
    std::cout << j;
    return 0;
}
