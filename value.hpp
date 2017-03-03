#ifndef VALUE_HPP
#define VALUE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <utility>

enum type {
  null_type,
  bool_type,
  string_type,
  number_type,
  array_type,
  object_type
};

class value {
public:
  int depth = 0;
  int type;

  virtual ~value() = default;

  virtual int weight() { return 1; }
  virtual void print(bool b) = 0;
};

class null_value : public value {
public:
  null_value(int d) { this->depth = ++d; type = null_type; }

  void print(bool b) { std::cout << "null"; }
};

class bool_value : public value {
private:
  bool value;

public:
  bool_value(int d, bool b) : value(b) { this->depth = ++d; type = bool_type; }

  bool getValue() { return value; }
  void print(bool b) { std::cout << (value ? "true" : "false"); }
};

class string_value : public value, public std::string {
public:
  using std::string::string;

  void setDepth(int d) { this->depth = ++d; type = string_type; }
  void print(bool b) { std::cout << '"' << *this << '"'; }
  std::string getString() { return *this; }
};

class number_value : public value, public std::string {
public:
  using std::string::string;

  void setDepth(int d) { this->depth = ++d; type = number_type; }
  void print(bool b) { std::cout << *this; }
};

class array_value : public value, public std::vector<value*> {
public:
  using std::vector<value*>::vector;

  void setDepth(int d) { this->depth = ++d; type = array_type; }
  ~array_value() {
    for (std::vector<value*>::iterator it = this->begin(); it != this->end(); ++it) {
      delete *it;
    }
  }

  int weight() {
    int total = 1;

    for (std::vector<value*>::iterator it = this->begin(); it != this->end(); ++it) {
      total += (*it)->weight();
    }

    return total;
  }

  void print(bool b) {
    if (!this->size())
      std::cout << "[]";
    else {
      std::string str;
      
      for (int i; i <= depth; ++i)
	str += " ";
      
      std::cout << "[\n";
      for (std::vector<value*>::iterator it = this->begin(); it != this->end(); ++it) {
	(*it)->print(true);
	
	if (std::next(it) != this->end())
	  std::cout << ",\n";
      }
      std::cout << '\n' << str << ']';
    }
  }
};

class object_value : public value, public std::vector<std::pair<std::string,value*>> {
public:
  using std::vector<std::pair<std::string,value*>>::vector;

  void setDepth(int d) { this->depth = ++d; type = object_type; }
  ~object_value() {
    for (std::vector<std::pair<std::string,value*>>::iterator it = this->begin(); it!= this->end(); ++it) {
      delete it->second;
    }
  }

  int weight() {
    int total = 1;

    for (std::vector<std::pair<std::string,value*>>::iterator it = this->begin(); it!= this->end(); ++it) {  
      total += (*it->second).weight();
    }
    return total;
  }

  void print(bool b) {
    std::string str = "";

    if (!this->size())
      std::cout << "{}";
    else {
      for (int i = 0; i <= depth; ++i)
	str += " ";
      
      std::cout << (b ? str : "") << "{\n";  

      for (std::vector<std::pair<std::string,value*>>::iterator it = this->begin(); it!= this->end(); ++it) {
	std::cout << str << " \"" << it->first;  
	std::cout << "\" : ";
	if ((*it->second).type == object_type)
	  (*it->second).print(false);
	else
	  (*it->second).print(true);	
	
	if (std::next(it) != this->end())
	  std::cout << ",\n";
      }
      std::cout << '\n' << (depth > 0 ? str : "") << '}';
    }
  }
};
#endif
