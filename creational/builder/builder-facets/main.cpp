#include "Person.hpp"
#include "PersonAddressBuilder.hpp"
#include "PersonBuilder.hpp"
#include "PersonJobBuilder.hpp"

#include <iostream>
#include <string>

using namespace std;

int main() {
  // Create a new person with the underlying builders
  Person p = Person::create()
                 // PersonAddressBuilder in action
                 .lives()
                 .at("123 Panama Ave")
                 .with_postcode("SW1 1GB")
                 .in("London")
                 // PersonJobBuilder in action
                 .works()
                 .at("PragmaSoft")
                 .as_a("Consultant")
                 .earning(10e6);

  cout << p << endl;

  return 0;
}
