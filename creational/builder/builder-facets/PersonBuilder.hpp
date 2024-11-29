#pragma once

#include "Person.hpp"

// forward declarations
class PersonJobBuilder;
class PersonAddressBuilder;

class PersonBuilderBase {
protected:
  Person &person;
  // we only want derived classes to access this constructor, thus protected,
  // and we want it to call it explicitly, thus explicit
  // explicit PersonBuilderBase(Person &person) : person(person) {}

public:
  PersonBuilderBase(Person &person);

  operator Person() const { return std::move(person); }

  PersonJobBuilder works() const;
  PersonAddressBuilder lives() const;
};

class PersonBuilder : public PersonBuilderBase {
  Person p;

public:
  PersonBuilder() : PersonBuilderBase{p} {}
};
