#include <iostream>

using namespace std;

// Property proxy here: it basically mocks the functionality of a regular prop
template <typename T> struct Property {
  T value;

  Property(T value) { *this = value; }

  operator T() { return value; }

  T operator=(T new_value) {
    cout << "Assignment" << endl;
    return value = new_value;
  }
};

struct Creature {
  // int strenght{10};
  Property<int> strenght{10};
};

int main() {
  // property usage remains the same
  Creature c;
  c.strenght = 15;
}
