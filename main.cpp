#include "parse.hpp"
#include <sstream>
#include <algorithm>

int main() {
  std::string input, str;
  std::stringstream stream;

  while (getline(std::cin,input)) {
    if (input != "")
      stream << input;
    else {
      std::cout << "Please provide input file when running this program.\n";
      return 1;
    }
  }

  str = stream.str();

  std::string::iterator F = str.begin();
  std::string::iterator L = str.end();

  value* val = parse(-1,F,L);

  val->print(false);
  std::cout << "\nSuccess\n";
  std::cout << "Weight: " << val->weight() << '\n';

  delete val;
  return 0;
}
