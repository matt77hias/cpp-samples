#include <iostream>

#define BREAK() break
#define RETURN(arg) return (arg)

[[nodiscard]]
auto f()
   noexcept -> int
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

auto main()
   -> int
{
   return f();
}
