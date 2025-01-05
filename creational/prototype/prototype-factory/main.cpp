#include <iostream>
#include <memory>
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

struct EmployeeFactory {
  static unique_ptr<Contact> new_main_office_employee(const string &name,
                                                      const int suite) {
    // make main office employee proto prototype?
    static Contact p{"", new Address{"123 East Dr.", "London", 0}};

    // use new_employee method to create a copy of it
    return new_employee(name, suite, p);
  }

private:
  static unique_ptr<Contact> new_employee(const string &name, const int suite,
                                          const Contact &prototype) {
    auto result = make_unique<Contact>(prototype);

    result->name = name;
    result->address->suite = suite;
    return result;
  }
};

int main() {
  auto john = EmployeeFactory::new_main_office_employee("John", 44);

  cout << *john << endl;

  return 0;
}
