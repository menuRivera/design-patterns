#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

using namespace std;
using namespace boost;

struct Address {
  string street, city;
  int suite;

  Address() {}

  Address(const string &street, const string &city, int suite)
      : street(street), city(city), suite(suite) {}

  Address(const Address &address)
      : street(address.street), city(address.city), suite(address.suite) {}

  friend ostream &operator<<(ostream &os, Address &address) {
    return os << "street: " << address.street << " city: " << address.city
              << " suite: " << address.suite;
  }

private:
  friend class serialization::access;

  /**
   * Method to serialize Address instances
   */
  template <class archive> void serialize(archive &ar, const unsigned version) {
    ar & street;
    ar & city;
    ar & suite;
  }
};

struct Contact {
  string name;
  Address *address;

  Contact() {}

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

private:
  friend class serialization::access;

  /**
   * Method to serialize Contact instances
   */
  template <class archive> void serialize(archive &ar, const unsigned version) {
    ar & name;
    ar & address;
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
  auto clone = [](const Contact &c) {
    // serialize
    ostringstream oss;
    archive::text_oarchive oa(oss);
    oa << c;
    string s = oss.str();
    cout << s << endl;

    // deserialize
    istringstream iss(s);
    archive::text_iarchive ia(iss);
    Contact result;
    ia >> result;

    return result;
  };

  auto john = EmployeeFactory::new_main_office_employee("John", 50);
  auto jane = clone(*john);
  jane.name = "Jane";

  cout << *john << endl;
  cout << jane << endl;
}
