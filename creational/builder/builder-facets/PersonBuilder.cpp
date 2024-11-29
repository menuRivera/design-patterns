#include "PersonBuilder.hpp"
#include "PersonAddressBuilder.hpp"
#include "PersonJobBuilder.hpp"

// do we need this one?
PersonBuilderBase::PersonBuilderBase(Person &person) : person(person) {}

PersonAddressBuilder PersonBuilderBase::lives() const {
  return PersonAddressBuilder{person};
}
PersonJobBuilder PersonBuilderBase::works() const {
  return PersonJobBuilder{person};
}
