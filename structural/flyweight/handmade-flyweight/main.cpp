#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>

using namespace boost;
using namespace flyweights;
using namespace std;

typedef uint32_t key;

struct User {
  User(const string &first_name, const string &last_name)
      : first_name{add(first_name)}, last_name{add(last_name)} {}

  auto &get_first_name() const { return names.left.find(first_name)->second; }
  auto &get_last_name() const { return names.left.find(last_name)->second; }

  key first_name, last_name;

protected:
  static bimap<key, string> names;
  static key seed;
  static key add(const string &s) {
    // searching the right hand side of the bimap
    auto it = names.right.find(s);
    if (it == names.right.end()) {
      // if no name found in the bimap
      key id = ++seed; // increment the seed (as id)
      // insert it
      names.insert({seed, s});
      return id;
    }
    // return the 'key' part of the iterator
    return it->second;
  }
};

// init static props
key User::seed{0};
bimap<key, string> User::names{};

ostream &operator<<(ostream &os, const User &user) {
  // prints the first_name and last_name along with their respective ids
  os << "first_name: " << user.get_first_name() << " (id: " << user.first_name
     << ")" << ", last_name: " << user.get_last_name()
     << " (id: " << user.last_name << ")" << endl;

  return os;
}

int main() {
  User user1{"John", "Smith"};
  User user2{"Jane", "Smith"};

  cout << user1 << user2 << endl;

  return 0;
}
