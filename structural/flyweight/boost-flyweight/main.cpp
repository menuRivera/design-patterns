#include <boost/flyweight.hpp>
#include <iostream>
#include <string>

using namespace boost;
using namespace std;

typedef uint32_t key;

struct User {
  flyweight<string> first_name, last_name;

  User(const string &first_name, const string &last_name)
      : first_name(first_name), last_name(last_name) {}
};

int main() {
  User first{"John", "Smith"};
  User second{"Jane", "Smith"};

  cout << boolalpha;
  cout << (&first.first_name.get() == &second.first_name.get()) << endl;
  cout << (&first.last_name.get() == &second.last_name.get()) << endl;

  cout << "Same pointers" << endl;
  cout << &first.last_name.get() << endl;
  cout << &second.last_name.get() << endl;
}
