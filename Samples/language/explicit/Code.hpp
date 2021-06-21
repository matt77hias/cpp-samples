struct Vector
{};

struct Rgb : Vector
{
    [[nodiscard]]
	constexpr Rgb()
        : Vector{}, m_i(0)
    {}
	
	[[nodiscard]]
    constexpr Rgb(const Rgb&)
        : Vector{}, m_i(16)
    {}
	
	[[nodiscard]]
    constexpr Rgb(Rgb&&)
        : Vector{}, m_i(16)
    {}
	
	[[nodiscard]]
    constexpr explicit Rgb(const Vector&)
        : Vector{}, m_i(1)
    {}
	
	[[nodiscard]]
    constexpr explicit Rgb(Vector&&)
        : Vector{}, m_i(1)
    {}

    int m_i;
};

struct Xyz : Vector
{
    [[nodiscard]]
	constexpr explicit operator Rgb() const
    {
        Rgb temp{};
        return temp;
    }
};

int main()
{
    constexpr Xyz xyz;
    constexpr Rgb rgb1 = static_cast< Rgb >(xyz);
    constexpr Rgb rgb2 = static_cast< Rgb >(Xyz{});
    constexpr Rgb rgb3 = Rgb(xyz);
    constexpr Rgb rgb4 = Rgb(Xyz{});

    constexpr int v = rgb1.m_i + rgb2.m_i + rgb3.m_i + rgb4.m_i;
    return v;
}
