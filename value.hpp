#ifndef VALUE_HPP
#define VALUE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class value {
public:
  virtual ~value() = default;
  
  virtual int weight() { return 1; }
  virtual void print() = 0;
};

class null_value : public value {
public:
  void print() { std::cout << "Null"; }
};

class bool_value : public value {
private:
  bool value;

public:
  bool_value(bool b) : value(b) {}

  bool getValue() { return value; }
  void print() { std::cout << "Bool: " << (value ? "true" : "false"); }
};

class string_value : public value, public std::string {
public:
  using std::string::string;

  void print() { std::cout << "String: " << *this; } 
};

class number_value : public value, public std::string {
public:
  using std::string::string;

  void print() { std::cout << "String: " << *this; } 
};

class array_value : public value, public std::vector<value*> {
public:
  using std::vector<value*>::vector;

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

  void print() {
    for (std::vector<value*>::iterator it = this->begin(); it != this->end(); ++it) {
      std::cout << '[';
      (*it)->print();
      std::cout << ']';
    }
  }
};

class object_value : public value, public std::unordered_map<std::string,value*> {
public:
  using std::unordered_map<std::string,value*>::unordered_map;

  ~object_value() {
    for (std::unordered_map<std::string,value*>::iterator it = this->begin(); it!= this->end(); ++it){
      delete it->second;
    }
  }

  int weight() {
    int total = 1;
    
    for (std::unordered_map<std::string,value*>::iterator it = this->begin(); it!= this->end(); ++it){
      total += (*it->second).weight();
    }
    return total;
  }

  void print() {
    for (std::unordered_map<std::string,value*>::iterator it = this->begin(); it!= this->end(); ++it){
      std::cout << '{' << it->first;
      std::cout  << ',';
      (*it->second).print();
      std::cout << '}';
    }
  }
};
#endif
