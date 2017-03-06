#ifndef PARSE_HPP
#define PARSE_HPP

#include "value.hpp"

value* parseObject(int,std::string::iterator&,std::string::iterator&);
value* parseArray(int,std::string::iterator&,std::string::iterator&);
value* parseString(int,std::string::iterator&,std::string::iterator&);
value* parseBool(int,bool,std::string::iterator&,std::string::iterator&);
value* parseNull(int,std::string::iterator&,std::string::iterator&);
value* parseNumber(int,std::string::iterator&,std::string::iterator&);

value* parse(int depth, std::string::iterator& F, std::string::iterator& L) {
  if (F != L) {
    switch(*F) {
    case '{': return parseObject(depth,F,L);
    case '[': return parseArray(depth,F,L);
    case '"': return parseString(depth,F,L);
    case 't': return parseBool(depth,true,F,L);
    case 'f': return parseBool(depth,false,F,L);
    case 'n': return parseNull(depth,F,L);
    case '-':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': return parseNumber(depth,F,L);
    case ' ':
    case '\n':
    case '\t':
    case '\\':
    case ',':
    case ':':
      return nullptr;
    }
  }
  else
    return nullptr;
}

value* parseObject(int depth,std::string::iterator& F, std::string::iterator& L) {
  object_value *obj = new object_value();
  obj->setDepth(depth);

  if (F != L)
      ++F;

  while(*F != '}' && F != L) {
    value* key = nullptr;
    value* value = nullptr;

    while (!key && *F != '}' && F != L) {
      key = parse(obj->depth,F,L);

      if (!key && *F != '}' && F != L)
	++F;
    }

    while (!value && *F != '}' && F != L) {
      value = parse(obj->depth,F,L);
      
      if (!value && *F != '}' && F != L)
	++F; 
    }

    if (key && value) {
      std::string str = dynamic_cast<string_value*>(key)->getString();
      
      obj->push_back(std::make_pair(str, value));	
    }

    if (*F != '}' && F != L)
      ++F;
  }

  if (*F == '}' && F != L)
    ++F;
  
  return obj;
}

value* parseArray(int depth, std::string::iterator& F, std::string::iterator& L) {
  array_value *arr = new array_value();
  arr->setDepth(depth);

  if (F != L)
    ++F;

  while(*F != ']' && F != L) {
    value* val = parse(arr->depth,F,L);

    if (val)
      arr->push_back(val);

    if (*F != ']' && F != L)
      ++F;
  }

  if (*F == ']' && F != L)
    ++F;

  return arr;
}

value* parseString(int depth, std::string::iterator& F, std::string::iterator& L) {
  string_value *str = new string_value();
  str->setDepth(depth);

  if (F != L)
    ++F;

  while (*F != '"' && F != L) { 
    if (*F == '\\' && F != L)
      ++F;

    if (F != L) {
      *str += *F;

      ++F;
    }
  }

  if (*F == '"' && F != L)
    ++F;

  return str;
}

value* parseBool(int depth, bool b, std::string::iterator& F, std::string::iterator& L) {
  if (b) {
    ++F;
    if (*F == 'r') {
      ++F;
      if (*F == 'u') {
	++F;
	if (*F == 'e') {
	  return new bool_value(depth,true);
	} 
      }
    }
  }
  else {
    ++F;
    if (*F == 'a') {
      ++F;
      if (*F == 'l') {
	++F;
	if (*F == 's') {
	  ++F;
	  if (*F == 'e') {
	    return new bool_value(depth,false);
	  }
	}
      }
    }
  }
}

value* parseNull(int depth, std::string::iterator& F, std::string::iterator& L) {
  ++F;
  if (*F == 'u') {
    ++F;
    if (*F == 'l') {
      ++F;
      if (*F == 'l') {
	return new null_value(depth);
      } 
    }
  }
}

value* parseNumber(int depth, std::string::iterator& F, std::string::iterator& L) {
  number_value *num = new number_value();
  num->setDepth(depth);

  while (F != L && (isdigit(*F) || *F == 'E' || *F == 'e' || *F == '-' || *F == '+' || *F == '.')) { 
    *num += *F;

    ++F;
  }

  return num;
}
#endif
