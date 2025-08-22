// std::transform
#include <algorithm>
// std::cout
#include <iostream>
// std::ostream_iterator
#include <iterator>
// std::regex
// std::smatch
// std::sregex_iterator
#include <regex>
// std::string
#include <string>

auto main()
	-> int
{
   const std::string text = "Quick \"\"\"\" \"brown fox\".";
   std::regex re(R"((\"([^\"]*)\")|(\S+))");
   std::transform(std::sregex_iterator(text.begin(), text.end(), re),
                  std::sregex_iterator(),
                  std::ostream_iterator< std::string >(std::cout, "\n"),
                  [](const std::smatch& m) { return m[2u].length() ? m[2u] : m[3u]; });
   
   return 0;
}
