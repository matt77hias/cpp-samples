// std::copy
#include <algorithm>
// std::cout
#include <iostream>
// std::ostream_iterator
#include <iterator>
// std::regex
// std::sregex_token_iterator
#include <regex>
// std::string
#include <string>

auto main()
	-> int
{
   const std::string text = "Quick \"\"\"\" \"brown fox\".";
   std::regex re(R"((\"[^\"]*\")|\S+)");
   std::copy(std::sregex_token_iterator(text.begin(), text.end(), re, 0),
             std::sregex_token_iterator(),
             std::ostream_iterator< std::string >(std::cout, "\n"));
   
   return 0;
}
