#include <fmt/format.h>
#include <string_view>

struct UTF16toUTF8 {

    explicit UTF16toUTF8([[maybe_unused]] std::wstring_view) {}
    
    explicit operator std::string_view() const noexcept {
        return m_str;
    }

    std::string m_str = "string";
};

struct UTF8toUTF16 {

    explicit UTF8toUTF16([[maybe_unused]] std::string_view) {}
    
    explicit operator std::wstring_view() const noexcept {
        return m_str;
    }

    std::wstring m_str = L"wstring";
};

namespace fmt {

	template<>
	struct formatter< std::wstring_view, char > {

		template< typename ParseContextT >
		typename ParseContextT::iterator parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::wstring_view& wstr, FormatContextT& ctx) {
			const UTF16toUTF8 str(wstr);
			return format_to(ctx.out(), "{}", std::string_view(str));
		}
	};

	template<>
	struct formatter< std::wstring, char > {

		template< typename ParseContextT >
		typename ParseContextT::iterator parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::wstring& wstr, FormatContextT& ctx) {
			const UTF16toUTF8 str(wstr);
			return format_to(ctx.out(), "{}", std::string_view(str));
		}
	};

	template<>
	struct formatter< std::string_view, wchar_t > {

		template< typename ParseContextT >
		typename ParseContextT::iterator parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::string_view& str, FormatContextT& ctx) {
			const UTF8toUTF16 wstr(str);
			return format_to(ctx.out(), L"{}", std::wstring_view(wstr));
		}
	};

	template<>
	struct formatter< std::string, wchar_t > {

		template< typename ParseContextT >
		typename ParseContextT::iterator parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::string& str, FormatContextT& ctx) {
			const UTF8toUTF16 wstr(str);
			return format_to(ctx.out(), L"{}", std::wstring_view(wstr));
		}
	};
}

template< typename... ArgsT >
inline void Print(std::string_view format_str, const ArgsT&... args) {
    return fmt::print(format_str, args...);
}

template< typename... ArgsT >
inline void Print(std::wstring_view format_str, const ArgsT&... args) {
    return fmt::print(format_str, args...);
}

int main() {
    std::string s = "foo";
    std::string_view sv = s;

    std::wstring ws = L"bar";
    std::wstring_view wsv = ws;

    Print( "{}", s);
    Print( "{}", sv);
    Print(L"{}", s);
    Print(L"{}", sv);

    Print( "{}", ws);
    Print( "{}", wsv);
    Print(L"{}", ws);
    Print(L"{}", wsv);

    return 0;
}
