// array
#include <array>
// tuple
#include <tuple>

auto main()
   -> int
{
   [[maybe_unused]] std::array< int, 0u > a;
   [[maybe_unused]] std::tuple<> t;

   return 0;
}
