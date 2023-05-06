// copy
#include <algorithm>
// cout
#include <iostream>
// ostream_iterator
#include <iterator>
// regex, sregex_token_iterator
#include <regex>
// string
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
