#include "parse.hpp"

int main() {

  //  std::string str = "[\"he\\llo\",7,85868,true,false]";

  //  std::string str = "{\"Jacob\" : [\"hello\",7,8858,true,false]}";

  std::string input;
  std::string str;

  while (getline(std::cin,input))
    str += input;

  //std::cin >> str;

  //std::cout << "Parsing: " << str << '\n';

  //char* F = &str[0];
  //char* L = &str[str.length() - 1];

  std::string::iterator F = str.begin();
  std::string::iterator L = str.end();

  value* val = parse(-1,F,L);

  val->print(false);
  std::cout << "\nSuccess\n";
  std::cout << "Weight: " << val->weight() << '\n';

  delete val;

  /*
  array_value *arr = new array_value();

  arr->push_back(new bool_value(true));
  arr->push_back(new number_value(7.5));

  object_value *obj = new object_value();

  obj->insert({"fun",arr});
  obj->insert({"hello",arr});

  std::cout << "Weight: " << obj->weight() << '\n';
  */

  return 0;
}
