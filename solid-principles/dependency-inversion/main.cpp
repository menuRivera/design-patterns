/**
 * a. High-level modules should not depend on low-level modules. Both should
 * depend on abstractions.
 * b. Abstractions should not depend on details. Details should depend on
 * abstractions.
 */
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct Person {
  string name;
};

enum class Relationship {
  parent,
  child,
  sibling,
};

// Abstraction
struct RelationshipBrowser {
  virtual vector<Person> find_children_of(const string &name) = 0;
};

// Low level module
struct Relationships : RelationshipBrowser {
  vector<tuple<Person, Relationship, Person>> relationships;

  void add_parent_rel(Person &parent, Person &child) {
    relationships.push_back({parent, Relationship::parent, child});
    relationships.push_back({child, Relationship::child, parent});
  }

  vector<Person> find_children_of(const string &name) override {
    vector<Person> result;

    // fancy syntax for destructuring the tuples inside of `relationships`
    for (auto &&[first, rel, second] : relationships) {
      if (first.name == name && rel == Relationship::parent) {
        result.push_back(second);
      }
    }

    return result;
  }
};

// High level module, depends on an abstraction of Relationships
// (RelationshipBrowser)
struct Research {
  Research(RelationshipBrowser &browser) {
    // we don't really care about this class, it will only call the
    // find_children_of method
    for (auto &child : browser.find_children_of("John")) {
      cout << "John is parent of " << child.name << endl;
    }
  }
};

int main() {
  Person parent{"John"}, child1{"Mathew"}, child2{"Eric"};

  Relationships relationships;
  relationships.add_parent_rel(parent, child1);
  relationships.add_parent_rel(parent, child2);

  Research _{relationships};

  return 0;
}
