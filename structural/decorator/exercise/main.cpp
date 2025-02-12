/*
   Roses can be red, blue or red and blue. Given the class interface Flower and
   class Rose, build decorators RedFlower and BlueFlower that would print the
   following:

    Rose rose;
    RedFlower red_rose{rose};
    RedFlower red_red_rose{red_rose};
    BlueFlower blue_red_rose{red_rose};
    cout << rose.str();          // "A rose"
    cout << red_rose.str();      // "A rose that is red"
    cout << red_red_rose.str();  // "A rose that is red"
    cout << blue_red_rose.str(); // "A rose that is red and blue"
*/

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct Flower {
  virtual string str() = 0;
};

struct Rose : Flower {
  string str() override { return "A rose"; }
};

struct RedFlower : Flower {
  Flower &flower;
  RedFlower(Flower &flower) : flower(flower) {}

  string str() override {

    if (flower.str().find("red") != string::npos) {
      return flower.str();
    }
    ostringstream oss;

    if (typeid(Rose) == typeid(flower)) {
      oss << flower.str() << " that is red";
    } else {
      oss << flower.str() << " and red";
    }

    return oss.str();
  }
};

struct BlueFlower : Flower {
  Flower &flower;
  BlueFlower(Flower &flower) : flower(flower) {}

  string str() override {
    ostringstream oss;

    if (typeid(RedFlower) == typeid(flower)) {
      oss << flower.str() << " and blue";
    } else {
      oss << flower.str() << " that is blue";
    }

    return oss.str();
  }
};

int main() {
  Rose rose;

  RedFlower red_rose{rose};
  BlueFlower blue_rose{rose};

  RedFlower red_red_rose{red_rose};

  BlueFlower blue_red_rose{red_rose};
  RedFlower red_blue_rose{blue_rose};

  RedFlower r_b_r_rose{blue_red_rose};

  cout << rose.str() << endl;         // "A rose"
  cout << red_rose.str() << endl;     // "A rose that is red"
  cout << blue_rose.str() << endl;    // "A rose that is blue"
  cout << red_red_rose.str() << endl; // "A rose that is red"

  cout << blue_red_rose.str() << endl; // "A rose that is red and blue"
  cout << red_blue_rose.str() << endl; // "A rose that is blue and red"
  cout << r_b_r_rose.str() << endl;    // "A rose that is red and blue"
}
