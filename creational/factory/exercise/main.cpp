#include <iostream>
#include <string>
using namespace std;

struct Person {
  int id;
  string name;
};

class PersonFactory {
  int id_counter = 0;

public:
  Person create_person(const string &name) { return {id_counter++, name}; }
};

int main() {
  PersonFactory pf{};
  Person person1 = pf.create_person("John");
  Person person2 = pf.create_person("Mike");

  cout << person1.name << " " << person1.id << endl;
  cout << person2.name << " " << person2.id << endl;

  return 0;
}
