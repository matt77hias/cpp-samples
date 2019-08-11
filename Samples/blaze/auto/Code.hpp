// norm, rowVector, StaticVector
#include <blaze/math/StaticVector.h>
// cout, endl
#include <iostream>

int main()
{
	using F32x4 = blaze::StaticVector< float, 4u, blaze::rowVector >;

    const F32x4 v1{ 0.0f, 1.0f, 2.0f, 3.0f };
    const F32x4 v2{ 0.0f, 1.0f, 2.0f, 3.0f };
    const F32x4 v3 = v1 + v2;
    const auto  v4 = v1 + v2;

    std::cout << blaze::norm(v3) << std::endl;
    std::cout << blaze::norm(v4) << std::endl;
	
    return 0;
}
