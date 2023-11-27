struct Vector
{};

struct Xyz;

struct Rgb : Vector
{
    [[nodiscard]]
	constexpr Rgb()
		noexcept = default;
	
	[[nodiscard]]
    constexpr Rgb(const Rgb&)
		noexcept
        : Vector{}
		, m_i(16)
    {}
	
	[[nodiscard]]
    constexpr Rgb(Rgb&&)
		noexcept
        : Vector{}
		, m_i(16)
    {}
	
	[[nodiscard]]
    constexpr explicit Rgb(const Xyz&)
		noexcept;
	
	[[nodiscard]]
    constexpr explicit Rgb(Xyz&&)
		noexcept;

    int m_i = {};
};

struct Xyz : Vector
{
    [[nodiscard]]
	constexpr explicit operator Rgb() const
		noexcept
    {
        Rgb temp{};
        return temp;
    }
};

[[nodiscard]]
constexpr Rgb
    ::Rgb(const Xyz&)
    noexcept
    : Vector{}
    , m_i(1)
{}

[[nodiscard]]
constexpr Rgb
    ::Rgb(Xyz&&)
    noexcept
    : Vector{}
    , m_i(1)
{}

auto main()
    -> int
{
    constexpr Xyz xyz;
    constexpr Rgb rgb1 = static_cast< Rgb >(xyz);
    constexpr Rgb rgb2 = static_cast< Rgb >(Xyz{});
    constexpr Rgb rgb3 = Rgb(xyz);
    constexpr Rgb rgb4 = Rgb(Xyz{});

    constexpr int v = rgb1.m_i + rgb2.m_i + rgb3.m_i + rgb4.m_i;
    return v;
}
