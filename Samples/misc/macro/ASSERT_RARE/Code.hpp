// atomic, memory_order_relaxed
#include <atomic>
// floating_point
#include <concepts>
// cout, endl
#include <iostream>
// final_action
#include <gsl/util>
// source_location
#include <source_location>
// remove_cvref_t
#include <type_traits>

using U64 = unsigned long long;

#define MAGE_ASSERT_RARE(frequency, expression, ...)                          \
	do                                                                        \
	{                                                                         \
        using MAGE_FLOAT = std::remove_cvref_t< decltype(frequency) >;        \
        static_assert(std::floating_point< MAGE_FLOAT >);                     \
        static_assert(MAGE_FLOAT{} < frequency);                              \
                                                                              \
        static std::atomic< U64 > MAGE_COUNT      = {};                       \
        static std::atomic< U64 > MAGE_TRUE_COUNT = {};                       \
        MAGE_COUNT.fetch_add(U64{ 1u }, std::memory_order_relaxed);           \
        if ((expression) == true) [[unlikely]]                                \
        {                                                                     \
            MAGE_TRUE_COUNT.fetch_add(U64{ 1u }, std::memory_order_relaxed);  \
        }                                                                     \
                                                                              \
        static gsl::final_action MAGE_REPORTER(                               \
            [source_location = std::source_location::current()]()             \
        {                                                                     \
            const auto frequency_estimate                                     \
                = static_cast< MAGE_FLOAT >(MAGE_TRUE_COUNT.load())           \
                / static_cast< MAGE_FLOAT >(MAGE_TRUE_COUNT.load());          \
            const auto variance_estimate                                      \
                = frequency_estimate * (MAGE_FLOAT{ 1 } - frequency_estimate) \
                / static_cast< MAGE_FLOAT >(MAGE_TRUE_COUNT.load() - 1u);     \
            const auto frequency_threshold                                    \
                = frequency_estimate - (MAGE_FLOAT{ 2 } * variance_estimate); \
            if (frequency <= frequency_threshold)                             \
            {                                                                 \
                std::cout << source_location.function_name() << std::endl;    \
            }                                                                 \
        });                                                                   \
	}                                                                         \
	while(false)

auto f(bool flag)
	noexcept -> bool
{
    MAGE_ASSERT_RARE(0.0001f, flag);

    return flag;
}

auto g(bool flag)
	noexcept -> bool
{
    MAGE_ASSERT_RARE(0.0001f, flag);
   
    return flag;
}

auto main()
    -> int
{
    f(true);
    f(true);
    g(true);
    g(true);
    
    return 0;
}
