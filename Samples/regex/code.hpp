#include <iostream>
#include <regex>

int main() {
   std::string text = "Quick \"\"\"\" \"brown fox\".";
   std::regex re(R"((\"[^\"]*\")|\S+)");
   std::copy(std::sregex_token_iterator(text.cbegin(), text.cend(), re, 0),
             std::sregex_token_iterator(),
             std::ostream_iterator< std::string >(std::cout, "\n"));
   return 0;
}
