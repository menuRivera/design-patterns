#include <iostream>
#include <ostream>
#include <string>

using namespace std;

struct Address {
  string street, city;
  int suite;

  Address(const string &street, const string &city, int suite)
      : street(street), city(city), suite(suite) {}

  Address(const Address &address)
      : street(address.street), city(address.city), suite(address.suite) {}

  friend ostream &operator<<(ostream &os, Address &address) {
    return os << "street: " << address.street << " city: " << address.city
              << " suite: " << address.suite;
  }
};

struct Contact {
  string name;
  Address *address;

  Contact(const string &name, Address *address)
      : name(name), address(address) {}

  // copy constructor
  Contact(const Contact &other)
      : name{other.name},
        // address{new Address{other.address->street, other.address->city,
        // other.address->suite}} {}
        address{new Address{*other.address}} {}

  friend ostream &operator<<(ostream &os, const Contact &contact) {
    return os << "name: " << contact.name << " address: " << *contact.address;
  }
};

int main() {
  // same address, different suite
  // Contact jane{"jane doe", Address{"123 lele", "London", 103}};
  Contact john{"john doe", new Address{"123 lele", "London", 123}};

  // Contact jane = john; // shallow copy
  Contact jane{john};
  jane.name = "jane doe";
  jane.address->suite = 103;

  cout << john << endl;
  cout << jane << endl;

  return 0;
}
