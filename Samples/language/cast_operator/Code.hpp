// cout, endl
#include <iostream>

struct Vector
{};

struct Rgb : Vector
{
    Rgb()
    {
        std::cout << "Rgb()" << std::endl;
    }
    Rgb(const Rgb&)
    {
        std::cout << "Rgb(const Rgb&)" << std::endl;
    }
    Rgb(Rgb&&)
    {
        std::cout << "Rgb(Rgb&&)" << std::endl;
    }
    explicit Rgb(const Vector&)
    {
        std::cout << "Rgb(const Vector&)" << std::endl;
    }
    explicit Rgb(Vector&&)
    {
        std::cout << "Rgb(Vector&&)" << std::endl;
    }
};

struct Xyz : Vector
{
    Xyz()
    {
        std::cout << "Xyz()" << std::endl;
    }
    explicit operator Rgb() const
    {
        std::cout << "operator Rgb()" << std::endl;
        return Rgb{};
    }
};

int main()
{
    Xyz xyz;
    Rgb rgb1 = static_cast< Rgb >(xyz);
    Rgb rgb2 = static_cast< Rgb >(Xyz{});

    return 0;
}
