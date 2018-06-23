#include <iostream>
#include <regex>

int main() {
    std::string text = "Quick \"\"\"\" \"brown fox\".";
    std::regex re(R"((\"([^\"]*)\")|(\S+))");
    std::transform(std::sregex_iterator(text.cbegin(), text.cend(), re), 
                   std::sregex_iterator(), 
                   std::ostream_iterator< std::string >(std::cout, "\n"), 
                   [](const std::smatch& m) { return m[2].length() ? m[2] : m[3]; });
    return 0;
}
