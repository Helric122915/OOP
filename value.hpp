#ifndef VALUE_HPP
#define VALUE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class value {
public:
  virtual ~value() = default;
};

class null_value : public value {};

class bool_value : public value {
private:
  bool value;

public:
  bool_value(bool b) : value(b) {}

  bool getValue() { return value; }
};

class string_value : public value, public std::string {
  using std::string::string;
};

class number_value : public value {
private:
  double value;

public:
  number_value(double d) : value(d) {}

  double getValue() { return value; }
};

class array_value : public value, public std::vector<value*> {
  using std::vector<value*>::vector;
};

class object_value : public value, public std::unordered_map<std::string,value*> {
  using std::unordered_map<std::string,value*>::unordered_map;
};
#endif
