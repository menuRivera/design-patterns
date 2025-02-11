#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Shape {
  virtual string str() const = 0;
};

struct Circle : Shape {
  float radius;

  Circle() {}
  Circle(float radius) : radius(radius) {}

  void resize(float factor) { radius *= factor; }

  string str() const override {
    ostringstream oss;
    oss << "A circle of radius " << radius;
    return oss.str();
  }
};

struct Square : Shape {
  float side;

  Square() {}
  Square(float side) : side(side) {}

  string str() const override {
    ostringstream oss;
    oss << "An square with side " << side;
    return oss.str();
  }
};

// we add functionality to the Shape class by inheriting it
struct ColoredShape : Shape {
  Shape &shape;
  string color;

  ColoredShape(Shape &shape, const string &color)
      : shape(shape), color(color) {}

  string str() const override {
    ostringstream oss;
    oss << shape.str() << " has the color " << color;
    return oss.str();
  }
};

struct TransparentShape : Shape {
  Shape &shape;
  uint8_t transparency;

  TransparentShape(Shape &shape, uint8_t transparency)
      : shape(shape), transparency(transparency) {}

  string str() const override {
    ostringstream oss;
    oss << shape.str() << " has "
        << static_cast<float>(transparency) / 255.f * 100.f << "% transparency";
    return oss.str();
  }
};

int main() {
  Square sq{4};
  ColoredShape red_sq{sq, "red"};

  cout << sq.str() << endl << red_sq.str() << endl;

  TransparentShape transparent_sq{red_sq, 51};

  cout << transparent_sq.str() << endl;
}
