#include <iostream>

constexpr bool IsEven(unsigned int x) {
	switch(x) {
		case 0u: return true;
		case 1u: return false;
		default: return IsEven(x*x);
	}
}

int main() {
	std::cout << IsEven(3u) << std::endl;
	std::cout << IsEven(4u) << std::endl;
	return 0;
}
