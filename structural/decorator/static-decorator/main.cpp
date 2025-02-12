#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

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

// -std=c++20 flag needed to compile this with g++
// see .clangd
template <typename T>
concept IsAShape = std::is_base_of<Shape, T>::value;

template <IsAShape T> struct ColoredShape2 : T {
  string color;

  // perfect forwarding
  template <typename... Args>
  ColoredShape2(const string &color, Args... args)
      : T(std::forward<Args>(args)...), color(color) {}

  string str() const override {
    ostringstream oss;
    oss << T::str() << " has the color " << color;
    return oss.str();
  }
};

template <IsAShape T> struct TransparentShape2 : T {
  uint8_t transparency;

  template <typename... Args>
  TransparentShape2(uint8_t transparency, Args... args)
      : T(std::forward<Args>(args)...), transparency(transparency) {}

  string str() const override {
    ostringstream oss;
    oss << T::str() << " has "
        << static_cast<float>(transparency) / 255.f * 100.f << "% transparency";

    return oss.str();
  }
};

int main() {
  ColoredShape2<Circle> green_circle{"green", 5};
  cout << green_circle.str() << endl;

  TransparentShape2<Square> transparent_sq{51, 5};
  cout << transparent_sq.str() << endl;

  TransparentShape2<ColoredShape2<Square>> crazy_sq{0, "blue", 5};
  crazy_sq.color = "light blue";
  cout << crazy_sq.str() << endl;
}
