// map
#include <map>
// pair
#include <utility>

enum Node : int { A, B };
using Edge = std::pair< Node, Node >;

[[nodiscard]]
const Edge operator,(Node p1, Node p2)
{
    return { p1, p2 };
}

auto main()
    -> int
{ 
    std::map< Edge, double > lengths;
    lengths[A, B] = 123.0;
    lengths[B, A] = 123.0;
	
    return 0;
}
