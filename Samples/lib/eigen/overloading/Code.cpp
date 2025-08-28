// Eigen::Matrix
// Eigen::StorageOptions
#include <Eigen/Dense>
// std::cout
#include <iostream>

using F32 = float;

using StaticF32x2 = Eigen::Matrix< F32, 1u, 2u >;
static_assert(sizeof(StaticF32x2) == 2u * sizeof(F32));

using StaticF32x3 = Eigen::Matrix< F32, 1u, 3u >;
static_assert(sizeof(StaticF32x3) == 3u * sizeof(F32));

void Foobar(const StaticF32x2& v)
{
    std::cout << "Foobar(const StaticF32x2& v)";
}

void Foobar(const StaticF32x3& v)
{
    std::cout << "Foobar(const StaticF32x3& v)";
}

auto main()
    -> int
{
    const StaticF32x3 v = {};
    const auto result = v + v;
    Foobar(v);
    
    return 0;
}
