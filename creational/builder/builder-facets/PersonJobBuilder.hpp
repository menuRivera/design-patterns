#pragma once
#include "PersonBuilder.hpp"
#include <string>

using namespace std;

// We use struct here because all methods are gonna be public
struct PersonJobBuilder : public PersonBuilderBase {
  typedef PersonJobBuilder Self;

  explicit PersonJobBuilder(Person &person) : PersonBuilderBase{person} {}

  // fluent builder methods
  Self &at(string company_name) {
    person.company_name = company_name;
    return *this;
  }
  Self &as_a(string position) {
    person.position = position;
    return *this;
  }
  Self &earning(int annual_income) {
    person.annual_income = annual_income;
    return *this;
  }
};
