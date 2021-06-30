// format_to, formatter, print
#include <fmt/format.h>
// string, wstring
#include <string>
// string_view, wstring_view
#include <string_view>

struct UTF16toUTF8
{
    [[nodiscard]]
	explicit UTF16toUTF8(std::wstring_view)
	{}
    
	[[nodiscard]]
    explicit operator std::string_view() const noexcept
	{
        return m_str;
    }

    std::string m_str = "string";
};

struct UTF8toUTF16
{
    [[nodiscard]]
	explicit UTF8toUTF16(std::string_view)
	{}
    
	[[nodiscard]]
    explicit operator std::wstring_view() const noexcept
	{
        return m_str;
    }

    std::wstring m_str = L"wstring";
};

namespace fmt
{
	template<>
	struct formatter< UTF16toUTF8, char >
	{
		template< typename ParseContextT >
		typename ParseContextT::iterator parse(ParseContextT& ctx)
		{
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const UTF16toUTF8& wstr, FormatContextT& ctx)
		{
			return format_to(ctx.out(), "{}", std::string_view(wstr));
		}
	};

	template<>
	struct formatter< UTF8toUTF16, wchar_t >
	{
		template< typename ParseContextT >
		typename ParseContextT::iterator parse(ParseContextT& ctx)
		{
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const UTF8toUTF16& str, FormatContextT& ctx)
		{
			return format_to(ctx.out(), L"{}", std::wstring_view(str));
		}
	};
}

template< typename... ArgsT >
inline void Print(std::string_view format_str, const ArgsT&... args)
{
    return fmt::print(format_str, args...);
}

template< typename... ArgsT >
inline void Print(std::wstring_view format_str, const ArgsT&... args)
{
    return fmt::print(format_str, args...);
}

int main()
{
    std::string s = "foo";
    std::string_view sv = s;

    std::wstring ws = L"bar";
    std::wstring_view wsv = ws;

    Print( "{}", s);
    Print( "{}", sv);
    Print(L"{}", UTF8toUTF16(s));
    Print(L"{}", UTF8toUTF16(sv));

    Print( "{}", UTF16toUTF8(ws));
    Print( "{}", UTF16toUTF8(wsv));
    Print(L"{}", ws);
    Print(L"{}", wsv);

    return 0;
}
