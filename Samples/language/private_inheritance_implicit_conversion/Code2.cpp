// is_base_of_v, remove_reference_t
#include <type_traits>

template< typename T >
struct Span
{
    using element_type = T;

    Span() = default;

    template< typename R>
    Span(R&&) {};
};

template< typename C >
struct StringView : private Span< const C >
{
    // StringViews always have an infinite extent
    // E.g., std::span::first< std::size_t > won't work.
    
    using Container = Span< const C >;

    using typename Container::element_type;

    StringView() = default;

    template< typename R >
    requires(not std::is_base_of_v< StringView, std::remove_reference_t< R > >)
    explicit StringView(R&&) {};
};

template< typename C >
struct NullTerminatedStringView : private StringView< C >
{
    // NullTerminatedStringView always have an implicit null-terminating character
    // E.g., std::basic_string_view::remove_suffix won't work.

    using Container = StringView< C >;

    using typename Container::element_type;

    [[nodiscard]]
    constexpr operator Container() const // std::basic_string_view has an explicit range constructor
        noexcept
    {
        return {};
    }
};

auto main()
    -> int
{
    [[maybe_unused]] NullTerminatedStringView< char > s;
    //[[maybe_unused]] auto sv0 = static_cast< StringView< char > >(s);
    //[[maybe_unused]] auto sv1 = StringView< char >{ s };
    [[maybe_unused]] auto sv2 = s.operator StringView< char >();

    [[maybe_unused]] StringView< char > sv;
    [[maybe_unused]] auto sp0 = static_cast< Span< const char > >(sv);
    [[maybe_unused]] auto sp1 = Span< const char >{ sv };

    return 0;
}
