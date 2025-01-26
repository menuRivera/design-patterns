#include "Person.hpp"
#include <iostream>

using namespace std;

// these implementations will be shipped as binaries
class Person::PersonImpl {
public:
  void greet(Person *p);
};

void Person::PersonImpl::greet(Person *p) {
  cout << "hello, my name is " << p->name << endl;
};

Person::Person() : impl(new PersonImpl) {}

Person::~Person() { delete impl; }

void Person::greet() { impl->greet(this); }
