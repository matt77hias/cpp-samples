// day, days, floor, hh_mm_ss, hours, milliseconds, minutes, month, seconds,
// system_clock, year, year_month_day
#include <chrono>
// strong_ordering
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
inline std::chrono::year_month_day Date
    ::YearMonthDay() const noexcept
{
    const auto day_point = std::chrono::floor< std::chrono::days >(m_time_point);
    return std::chrono::year_month_day{ day_point };
}

[[nodiscard]]
inline std::chrono::year Date
    ::Year() const noexcept
{
    const auto year_month_day = YearMonthDay();
    return year_month_day.year();
}
    
[[nodiscard]]
inline std::chrono::month Date
    ::Month() const noexcept
{
    const auto year_month_day = YearMonthDay();
    return year_month_day.month();
}
    
[[nodiscard]]
inline std::chrono::day Date
    ::Day() const noexcept
{
    const auto year_month_day = YearMonthDay();
    return year_month_day.day();
}

[[nodiscard]]
inline auto Date
    ::HoursMinutesSeconds() const noexcept -> std::chrono::hh_mm_ss< std::chrono::milliseconds >
{
    const auto day_point   = std::chrono::floor< std::chrono::days >(m_time_point);
    const auto ms_duration = std::chrono::floor< std::chrono::milliseconds >(
                                m_time_point - day_point);
    return std::chrono::hh_mm_ss{ ms_duration };
}
    
[[nodiscard]]
inline std::chrono::hours Date
    ::Hours() const noexcept
{
    const auto hh_mm_ss = HoursMinutesSeconds();
    return hh_mm_ss.hours();
}
    
[[nodiscard]]
inline std::chrono::minutes Date
    ::Minutes() const noexcept
{
    const auto hh_mm_ss = HoursMinutesSeconds();
    return hh_mm_ss.minutes();
}
   
[[nodiscard]]
inline std::chrono::seconds Date
    ::Seconds() const noexcept
{
    const auto hh_mm_ss = HoursMinutesSeconds();
    return hh_mm_ss.seconds();
}
    
[[nodiscard]]
inline std::chrono::milliseconds Date::MilliSeconds() const noexcept
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
