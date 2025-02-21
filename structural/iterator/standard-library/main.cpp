#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

int main() {
  vector<string> names{"john", "jane", "jill", "jack"};
  vector<string>::iterator it = names.begin(); // begin(names)
  cout << "first name is: " << *it << endl;

  ++it;
  it->append(string(" goodall"));

  cout << "second name is: " << *it << endl;

  while (++it != names.end()) {
    cout << "another name: " << *it << endl;
  }

  // reverse begin
  for (auto ri = rbegin(names); ri != rend(names); ++ri) {
    cout << *ri;
    if (ri + 1 != rend(names)) {
      cout << ", ";
    }
  }

  // crbegin() // constant

  cout << endl;

  // begin and end
  for (auto &&name : names)
    cout << "name = " << name << endl;

  cout << endl;

  return 0;
}
