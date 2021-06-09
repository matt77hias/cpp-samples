#include <iostream>

#define BREAK() break
#define RETURN(arg) return (arg)

[[nodiscard]]
int f() noexcept
{
    int i = 5;
    while (true)
    {
        if (--i < 0)
        {
            BREAK();
        }
    };

    RETURN(i);
}

int main()
{
   return f();
}
