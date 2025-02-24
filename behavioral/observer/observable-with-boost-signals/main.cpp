#include <boost/signals2.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace boost;
using namespace boost::signals2;

template <typename T> struct Observable {
  signal<void(T &, const string &)> field_changed;
};

class Person : public Observable<Person> {
  int age{0};

public:
  int get_age() const { return age; }
  void set_age(int age) {
    // Person::age = age;
    if (this->age == age)
      return;
    this->age = age;
    field_changed(*this, "age");
  }
};

int main() {
  Person p;
  auto conn = p.field_changed.connect([](Person &p, const string &field_name) {
    cout << field_name << " has changed" << endl;
  });

  p.set_age(20);

  conn.disconnect();

  p.set_age(30);

  return 0;
}
