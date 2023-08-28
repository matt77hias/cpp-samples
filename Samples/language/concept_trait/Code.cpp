template< typename T >
struct Adapter
{
    using Container = T;
};

template< typename T >
inline constexpr bool IsAdapter = false;
template< typename T >
inline constexpr bool IsAdapter< Adapter< T > > = true;

template< typename T >
struct Widget
{};

template< typename T >
inline constexpr bool IsWidget = false;
template< typename T >
inline constexpr bool IsWidget< Widget< T > > = true;

template< typename T >
using WidgetAdapter = Adapter< Widget< T > >;

template< typename T >
//inline constexpr bool IsWidgetAdapter = IsAdapter< T > and IsWidget< typename T::Container >;
concept IsWidgetAdapter = IsAdapter< T > and IsWidget< typename T::Container >;

static_assert(IsWidgetAdapter< WidgetAdapter< int > >);
static_assert(not IsWidgetAdapter< int >);

auto main()
    -> int
{
    [[maybe_unused]] constexpr auto _ = IsWidgetAdapter< int >;
    
    return 0;
}
