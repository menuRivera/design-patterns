#include <iostream>
#include <string>
#include <variant>

using namespace std;

struct AddressPrinter {
  void operator()(const string &house_name) const {
    cout << "A house called " << house_name << endl;
  }
  void operator()(const int house_number) const {
    cout << "House number " << house_number << endl;
  }
};

using namespace std;

int main(int argc, char *argv[]) {
  variant<string, int> house;
  // house = 123;
  house = "Blue House";

  // visit(Visitor &&, Variants &&...)
  AddressPrinter ap;
  visit(ap, house);

  return 0;
}
