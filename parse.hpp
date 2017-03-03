#ifndef PARSE_HPP
#define PARSE_HPP

#include "value.hpp"

value* parseObject();
value* parseArray(char*,char*);
value* parseString(char*,char*);
value* parseBool(bool);
value* parseNull();
value* parseNumber();

/*
class Parser {
private:
  char* first;
  char* last;
  std::string buff;

  bool eof() const { return first == last; }
  char lookahead() const { return(eof() ? 0 : *first); }
  char ignore() { return (eof() ? 0 : *first++); }
  void consume() { ++first; }
  char buffer();

public:
  Parser(char* first, char* last) : first(first), last(last) {}
  ~Parser() = default;

  value* parse();
};
*/

value* parse(char* F, char* L) {
  switch(*F) {
  case '{': return parseObject();
  case '[': return parseArray(F,L);
  case '"': return parseString(F,L);
  case 'T': return parseBool(true);
  case 'F': return parseBool(false);
  case 'N': return parseNull();
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9': return parseNumber();
  case ' ':
  case '\n':
  case '\t':
    break;
  }
}

value* parseObject() {
  //++F;
  object_value *obj = new object_value();
}

value* parseArray(char* F, char* L) {
  ++F;
  array_value *arr = new array_value();

  while(*F != ']')
    value* v = parse(F,L);

  return arr;
}

value* parseString(char* F, char* L) {
  char* temp = F;

  while (*F != '"') 
    ++F;

  string_value *str = new string_value(temp);

  return str;
}

value* parseBool(bool b) {
  if (b) {
  }
  else {
  }
}

value* parseNull() {
}

value* parseNumber() {
}
#endif
