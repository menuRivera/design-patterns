#include <iostream>
#include <vector>

using namespace std;

struct GraphicObject {
  virtual void draw() = 0;
};

/**
 * This funges as the individual (scalar) object
 */
struct Circle : GraphicObject {
  void draw() override { cout << "Circle" << endl; }
};

/**
 * This is, therefore, the collection of objects with the some shared properties
 * with Circle
 */
struct Group : GraphicObject {
  string name;
  vector<GraphicObject *> objects;

  Group(const string &name) : name(name) {}
  void draw() override {
    cout << "Group " << name.c_str() << " contains: " << endl;
    for (auto &&o : objects) {
      o->draw();
    }
  }
};

int main() {
  Circle c1, c2;

  Group root("root");
  root.objects.push_back(&c1);

  Group subgroup("subgroup");
  subgroup.objects.push_back(&c2);

  // we can add sort of nested Group objects because they are also
  // GraphicObjects. This is the idea behind composites basically
  root.objects.push_back(&subgroup);

  root.draw();
}
