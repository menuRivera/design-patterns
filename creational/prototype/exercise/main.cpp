/**
 * Prototype Coding Exercise
 *
 * Given the provided code, you are asked to implement Line::deep_copy()  to
 * perform a deep copy of the current Line  object.
 *
 * Beware memory leaks!
 */

#include <cassert>
#include <iostream>

using namespace std;

struct Point {
  int x{0}, y{0};

  Point() {}

  Point(const int x, const int y) : x{x}, y{y} {}
};

struct Line {
  Point *start, *end;

  Line(Point *const start, Point *const end) : start(start), end(end) {}

  Line deep_copy() const {
    return {new Point{start->x, start->y}, new Point{end->x, end->y}};
  }
};

int main() {
  Line line{new Point{1, 5}, new Point{6, 8}};
  Line copied = line.deep_copy();
  copied.start->y = 1;

  assert(line.start->y != copied.start->y);

  cout << "Success" << endl;
}
