// cout, endl
#include <iostream>

struct Vector
{
    [[nodiscard]]
	Vector()
    {
        std::cout << "Vector()" << std::endl;
    }

	[[nodiscard]]
    Vector(float, float, float)
    {
        std::cout << "Vector(float, float, float)" << std::endl;
    }

	[[nodiscard]]
    Vector(const Vector&)
    {
        std::cout << "Vector(const Vector&)" << std::endl;
    }

	[[nodiscard]]
    Vector(Vector&&)
    {
        std::cout << "Vector(Vector&&)" << std::endl;
    }

    ~Vector() = default;

    Vector& operator=(const Vector&)
    {
       std::cout << "operator=(const Vector&)" << std::endl;
       return *this;
    }

    Vector& operator=(Vector&&)
    {
       std::cout << "operator=(Vector&&)" << std::endl;
       return *this;
    }
};

struct Rgb : Vector
{
    [[nodiscard]]
	Rgb()
        : Vector()
    {
        std::cout << "Rgb()" << std::endl;
    }

    [[nodiscard]]
	Rgb(float r, float g, float b)
        : Vector(r, g, b)
    {
        std::cout << "Rgb(float, float, float)" << std::endl;
    }

    [[nodiscard]]
	Rgb(const Rgb& rgb)
        : Vector(rgb)
    {
        std::cout << "Rgb(const Rgb&)" << std::endl;
    }

    [[nodiscard]]
	Rgb(Rgb&& rgb)
        : Vector(std::move(rgb))
    {
        std::cout << "Rgb(Rgb&&)" << std::endl;
    }

    ~Rgb() = default;

    Rgb& operator=(const Rgb& rgb)
    {
       Vector::operator=(rgb);
       std::cout << "operator=(const Rgb&)" << std::endl;
       return *this;
    }

    Rgb& operator=(Rgb&& rgb)
    {
        Vector::operator=(std::move(rgb));
        std::cout << "operator=(Rgb&&)" << std::endl;
        return *this;
    }
};

struct Xyz : Vector
{
    [[nodiscard]]
	Xyz()
        : Vector()
    {
        std::cout << "Xyz()" << std::endl;
    }

	[[nodiscard]]
    Xyz(float x, float y, float z)
        : Vector(x, y, z)
    {
        std::cout << "Xyz(float, float, float)" << std::endl;
    }

	[[nodiscard]]
    explicit Xyz(const Rgb& rgb)
        : Vector(rgb)
    {
        std::cout << "Xyz(const Rgb&)" << std::endl;
    }

	[[nodiscard]]
    explicit Xyz(Rgb&& rgb)
        : Vector(std::move(rgb))
    {
        std::cout << "Xyz(Rgb&&)" << std::endl;
    }

	[[nodiscard]]
    Xyz(const Xyz& xyz)
        : Vector(xyz)
    {
        std::cout << "Xyz(const Xyz&)" << std::endl;
    }

	[[nodiscard]]
    Xyz(Xyz&& xyz)
        : Vector(std::move(xyz))
    {
        std::cout << "Xyz(Xyz&&)" << std::endl;
    }

    ~Xyz() = default;

    Xyz& operator=(const Xyz& xyz)
    {
       Vector::operator=(xyz);
       std::cout << "operator=(const Xyz&)" << std::endl;
       return *this;
    }

    Xyz& operator=(Xyz&& xyz)
    {
        Vector::operator=(std::move(xyz));
        std::cout << "operator=(Xyz&&)" << std::endl;
        return *this;
    }
};

int main()
{
   Vector v  = {};
   Rgb rgb = {};
   Xyz xyz = {};

   std::cout << std::endl;
   
   v = rgb;
   v = xyz;

   std::cout << std::endl;

   // rgb = v; // Does not compile.
   static_cast< Vector& >(rgb) = v;
   // rgb = xyz; // Does not compile.
   static_cast< Vector& >(rgb) = xyz;

   std::cout << std::endl;

   // xyz = v; // Does not compile.
   static_cast< Vector& >(xyz) = v;
   // xyz = rgb; // Does not compile.
   static_cast< Vector& >(xyz) = rgb;
   xyz = static_cast< Xyz >(rgb);

   return 0;
}
