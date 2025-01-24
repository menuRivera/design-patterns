/*
Here's a very synthetic example for you to try.
You are given a Rectangle  protocol and an extension method on it. Try to define
a SquareToRectangleAdapter  that adapts the Square  to the Rectangle  interface.
*/

#include <iostream>
struct Square {
  int side{0};

  explicit Square(const int side) : side(side) {}
};

struct Rectangle {
  virtual int width() const = 0;
  virtual int height() const = 0;

  int area() const { return width() * height(); }
};

struct SquareToRectangleAdapter : Rectangle {
  int w, h;
  SquareToRectangleAdapter(const Square &square) { w = h = square.side; }
  int width() const override { return w; }
  int height() const override { return h; }
};

int main() {
  Square sq(5);
  SquareToRectangleAdapter rec(sq);

  std::cout << rec.width() << std::endl;
  std::cout << rec.height() << std::endl;
}
