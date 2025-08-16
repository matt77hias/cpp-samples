// std::day
// std::days
// std::floor
// std::hh_mm_ss
// std::hours
// std::milliseconds
// std::minutes
// std::month
// std::seconds
// std::system_clock
// std::year
// std::year_month_day
#include <chrono>
// std::strong_ordering
#include <compare>

struct Date
{
    using Clock = std::chrono::system_clock;

	using time_point = typename Clock::time_point;

	using duration = typename Clock::duration;
    
    [[nodiscard]]
    auto YearMonthDay() const
        noexcept -> std::chrono::year_month_day;

    [[nodiscard]]
    auto Year() const
        noexcept -> std::chrono::year;
    
    [[nodiscard]]
    auto Month() const
        noexcept -> std::chrono::month;
    
    [[nodiscard]]
    auto Day() const
        noexcept -> std::chrono::day;

    [[nodiscard]]
    auto HoursMinutesSeconds() const
        noexcept -> std::chrono::hh_mm_ss< std::chrono::milliseconds >;
    
    [[nodiscard]]
    auto Hours() const
        noexcept -> std::chrono::hours;
    
    [[nodiscard]]
    auto Minutes() const
        noexcept -> std::chrono::minutes;
   
    [[nodiscard]]
    auto Seconds() const
        noexcept -> std::chrono::seconds;
    
    [[nodiscard]]
    auto MilliSeconds() const
        noexcept -> std::chrono::milliseconds;

    [[nodiscard]]
    auto operator <=>(const Date& rhs) const
        noexcept -> std::strong_ordering = default;

    time_point m_time_point = Clock::now();
};

[[nodiscard]]
inline auto Date
    ::YearMonthDay() const
	noexcept -> std::chrono::year_month_day
{
    const auto day_point = std::chrono::floor< std::chrono::days >(m_time_point);
    return std::chrono::year_month_day{ day_point };
}

[[nodiscard]]
inline auto Date
    ::Year() const
	noexcept -> std::chrono::year
{
    const auto year_month_day = YearMonthDay();
    return year_month_day.year();
}
    
[[nodiscard]]
inline auto Date
    ::Month() const
	noexcept -> std::chrono::month
{
    const auto year_month_day = YearMonthDay();
    return year_month_day.month();
}
    
[[nodiscard]]
inline auto Date
    ::Day() const
	noexcept -> std::chrono::day
{
    const auto year_month_day = YearMonthDay();
    return year_month_day.day();
}

[[nodiscard]]
inline auto Date
    ::HoursMinutesSeconds() const
	noexcept -> std::chrono::hh_mm_ss< std::chrono::milliseconds >
{
    const auto day_point   = std::chrono::floor< std::chrono::days >(m_time_point);
    const auto ms_duration = std::chrono::floor< std::chrono::milliseconds >(
                                m_time_point - day_point);
    return std::chrono::hh_mm_ss{ ms_duration };
}
    
[[nodiscard]]
inline auto Date
    ::Hours() const
	noexcept -> std::chrono::hours
{
    const auto hh_mm_ss = HoursMinutesSeconds();
    return hh_mm_ss.hours();
}
    
[[nodiscard]]
inline auto Date
    ::Minutes() const
	noexcept -> std::chrono::minutes
{
    const auto hh_mm_ss = HoursMinutesSeconds();
    return hh_mm_ss.minutes();
}
   
[[nodiscard]]
inline auto Date
    ::Seconds() const
	noexcept -> std::chrono::seconds
{
    const auto hh_mm_ss = HoursMinutesSeconds();
    return hh_mm_ss.seconds();
}
    
[[nodiscard]]
inline auto Date
    ::MilliSeconds() const
	noexcept -> std::chrono::milliseconds
{
    const auto hh_mm_ss = HoursMinutesSeconds();
    return hh_mm_ss.subseconds();
}

auto main()
    -> int
{
    [[maybe_unused]] Date date;

    return 0;
}
