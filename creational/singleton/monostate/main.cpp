#include <iostream>

using namespace std;

struct Printer {
  static int id;

  int get_id() const { return id; }
  void set_id(int value) { id = value; }
};

int Printer::id = 0;

int main() {
  Printer p;
  p.set_id(1);
  cout << p.get_id() << endl;

  Printer p2;
  cout << p2.get_id() << endl;
}
