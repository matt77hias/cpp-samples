// cout, endl
#include <iostream>

struct Vector
{};

struct Rgb : Vector
{
    [[nodiscard]]
	Rgb()
    {
        std::cout << "Rgb()" << std::endl;
    }
	
	[[nodiscard]]
    Rgb(const Rgb&)
    {
        std::cout << "Rgb(const Rgb&)" << std::endl;
    }
	
	[[nodiscard]]
    Rgb(Rgb&&)
    {
        std::cout << "Rgb(Rgb&&)" << std::endl;
    }
	
	[[nodiscard]]
    explicit Rgb(const Vector&)
    {
        std::cout << "Rgb(const Vector&)" << std::endl;
    }
	
	[[nodiscard]]
    explicit Rgb(Vector&&)
    {
        std::cout << "Rgb(Vector&&)" << std::endl;
    }
};

struct Xyz : Vector
{
    [[nodiscard]]
	Xyz()
    {
        std::cout << "Xyz()" << std::endl;
    }
	
	[[nodiscard]]
    explicit operator Rgb() const
    {
        std::cout << "operator Rgb()" << std::endl;
        return Rgb{};
    }
};

auto main()
    -> int
{
    Xyz xyz;
    Rgb rgb1 = static_cast< Rgb >(xyz);
    Rgb rgb2 = static_cast< Rgb >(Xyz{});

    return 0;
}
