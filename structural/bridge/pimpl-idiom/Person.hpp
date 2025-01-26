#pragma once
#include <string>

class Person {
public:
  std::string name;

  // we hide the actual implementation to whoever is using this header file
  class PersonImpl;
  PersonImpl *impl;

  Person();
  ~Person();

  void greet();
};
