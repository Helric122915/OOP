#include "parse.hpp"

int main() {

  std::string str = "\"hello\"  7";

  char* F = &str[0];
  char* L = &str[str.length() - 1];

  value* val = parse(F,L);

  val->print();
  std::cout << '\n';

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
