#include <cmath>
#include <iostream>
#include <ostream>

using namespace std;

enum class PointType { cartesian, polar };

class Point {
  float x, y;
  Point(float x, float y) : x(x), y(y) {}
  // a private inner factory class is defined to instantiate Points. I think the
  // approach of factory methods is better than this in this case
  class PointFactory {
  public:
    static Point NewCartesian(float x, float y) { return {x, y}; }
    static Point NewPolar(float rho, float theta) {
      return {rho * cos(theta), rho * sin(theta)};
    }
  };

public:
  // We expose the inner Factory through an static instance
  static PointFactory Factory;
  friend ostream &operator<<(ostream &os, const Point &point) {
    return os << "x: " << point.x << "\ny: " << point.y << endl;
  }

  /**
   * Traditional constructor
   * The issue with this approach is that the parameters a and b are barely
   * telling what they are representing, as they could be representing x and y
   * for cartesian coordinates or rho and theta for polar coordinates
   */
  // Point(float a, float b, PointType type = PointType::cartesian) {
  //   if (type == PointType::cartesian) {
  //     x = a;
  //     y = b;
  //   } else {
  //     x = a * cos(b);
  //     y = a * sin(b);
  //   }
  // }

  // Factory methods (moved outside the Point class to PointFactory)
  // static Point NewCartesian(float x, float y) { return {x, y}; }
  // static Point NewPolar(float rho, float theta) {
  //   return {rho * cos(theta), rho * sin(theta)};
  // }
};

// this one requires either add PointFactory as a friend class in Point or make
// the constructor public
// struct PointFactory {
//   static Point NewCartesian(float x, float y) { return {x, y}; }
//   static Point NewPolar(float rho, float theta) {
//     return {rho * cos(theta), rho * sin(theta)};
//   }
// };

int main() {
  // auto point = PointFactory::NewPolar(5, M_PI_4);
  auto point = Point::Factory.NewPolar(5, M_PI_4);

  cout << point << endl;

  return 0;
}
