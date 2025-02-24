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
  // how to notify about this prop changed?
  bool get_can_vote() const { return age >= 16; }
  int get_age() const { return age; }
  void set_age(int age) {
    if (this->age == age)
      return;

    // cache old value
    auto old_can_vote = get_can_vote();

    this->age = age;
    field_changed(*this, "age");

    // get prop again now with age updated
    if (old_can_vote != get_can_vote()) {
      field_changed(*this, "can_vote");
    }
  }
};

int main() {
  Person p;
  auto conn = p.field_changed.connect([](Person &p, const string &field_name) {
    cout << field_name << " has changed" << endl;
  });

  p.set_age(14);
  p.set_age(15);
  p.set_age(16);
  p.set_age(17);

  conn.disconnect();

  p.set_age(30);

  return 0;
}
