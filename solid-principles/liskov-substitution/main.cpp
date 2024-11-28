/**
 * Subtypes should be immediatly substituable from their base types
 */
#include <boost/lexical_cast.hpp>
#include <boost/mpl/assert.hpp>
#include <cstdio>
#include <iostream>

using namespace std;
using namespace boost;

/**
 * Base class
 */
class Rectangle {
protected:
  int width, height;

public:
  Rectangle(int width, int height) : width(width), height(height) {}

  int getWidth() { return width; }
  virtual void setWidth(int width) { Rectangle::width = width; }

  int getHeight() { return height; }
  virtual void setHeigth(int height) { Rectangle::height = height; }

  int area() const { return width * height; }
};

/**
 * Derived class
 */
class Square : public Rectangle {
public:
  Square(int size) : Rectangle(size, size) {}
  void setWidth(int width) override { this->width = this->height = width; }
  void setHeigth(int height) override { this->width = this->height = height; }
};

/**
 * Example function that demostrates why this design is breaking the liskov
 * substitution principle
 */
void process(Rectangle &r) {
  // this will work perfectly with base rectangles, but not with the custom
  // Square subtype
  int w = r.getWidth();
  r.setHeigth(10);

  cout << "expected area = " << (w * 10) << ", got " << r.area() << endl;
}

int main() {
  Rectangle r{5, 15};
  process(r);

  Square sq{8};
  process(sq);

  return 0;
}
