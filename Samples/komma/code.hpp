#include <map>

enum Node { A, B };
using Edge = std::pair< Node, Node >;

const Edge operator,(Node p1, Node p2) {
    return std::make_pair(p1, p2);
}

int main() { 
    std::map< Edge, double > lengths;
    lenghts[A, B] = 123.0;
    lenghts[B, A] = 123.0;
	return 0;
}
