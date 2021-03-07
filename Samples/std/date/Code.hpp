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
    std::chrono::year_month_day YearMonthDay() const noexcept;

    [[nodiscard]]
    std::chrono::year Year() const noexcept;
    
    [[nodiscard]]
    std::chrono::month Month() const noexcept;
    
    [[nodiscard]]
    std::chrono::day Day() const noexcept;

    [[nodiscard]]
    std::chrono::hh_mm_ss< std::chrono::milliseconds > HoursMinutesSeconds() const noexcept;
    
    [[nodiscard]]
    std::chrono::hours Hours() const noexcept;
    
    [[nodiscard]]
    std::chrono::minutes Minutes() const noexcept;
   
    [[nodiscard]]
    std::chrono::seconds Seconds() const noexcept;
    
    [[nodiscard]]
    std::chrono::milliseconds MilliSeconds() const noexcept;

    [[nodiscard]]
    std::strong_ordering operator <=>(const Date& rhs) const noexcept = default;

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

int main()
{
    Date date;

    return 0;
}
