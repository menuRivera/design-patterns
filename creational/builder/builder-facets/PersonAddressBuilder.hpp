#pragma once
#include "PersonBuilder.hpp"
#include <string>

using namespace std;

// We use struct here because all methods are gonna be public
struct PersonAddressBuilder : public PersonBuilderBase {
  typedef PersonAddressBuilder Self;

  explicit PersonAddressBuilder(Person &person) : PersonBuilderBase{person} {}

  // fluent builder methods
  Self &at(string street_address) {
    person.street_address = street_address;
    return *this;
  }
  Self &with_postcode(string post_code) {
    person.post_code = post_code;
    return *this;
  }
  Self &in(string city) {
    person.city = city;
    return *this;
  }
};
