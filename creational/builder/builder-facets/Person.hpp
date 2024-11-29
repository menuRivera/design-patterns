#pragma once

#include <ostream>
#include <string>

using namespace std;

// forward declare PersonBuilder so we can work with it ahead of the actual
// definition
struct PersonBuilder;

class Person {
  // address
  string street_address, post_code, city;

  // employment
  string company_name, position;
  int annual_income{0};

public:
  static PersonBuilder create();

  // friend classes
  friend class PersonBuilder;
  friend class PersonJobBuilder;
  friend class PersonAddressBuilder;

  // << operator overload so we can print the person correctly
  friend ostream &operator<<(ostream &os, const Person &obj) {
    return os << "street_address: " << obj.street_address
              << " post_code: " << obj.post_code << " city: " << obj.city
              << " company_name: " << obj.company_name
              << " position: " << obj.position
              << " annual_income: " << obj.annual_income;
  }
};
