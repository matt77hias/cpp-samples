#include <functional>

template< typename F >
using Function = std::function< F >;

auto main()
   -> int
{
    [[maybe_unused]] Function< void () > f;
    
    return 0;
}
