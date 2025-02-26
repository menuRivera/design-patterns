#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

struct DiscriminantStrategy {
  virtual double calculate_discriminant(double a, double b, double c) = 0;
};

// In OrdinaryDiscriminantStrategy , If the discriminant is negative, we return
// it as-is. This is OK, since our main API returns std::complex  numbers
// anyway.
struct OrdinaryDiscriminantStrategy : DiscriminantStrategy {
  double calculate_discriminant(double a, double b, double c) override {
    return pow(b, 2) - (4 * a * c);
  }
};

// In RealDiscriminantStrategy , if the discriminant is negative, the return
// value is NaN (not a number). NaN propagates throughout the calculation, so
// the equation solver gives two NaN values.
struct RealDiscriminantStrategy : DiscriminantStrategy {
  // todo
  double calculate_discriminant(double a, double b, double c) override {
    double result = pow(b, 2) - (4 * a * c);
    if (result < 0)
      return nan("");
    return result;
  }
};

class QuadraticEquationSolver {
  DiscriminantStrategy &strategy;

public:
  QuadraticEquationSolver(DiscriminantStrategy &strategy)
      : strategy(strategy) {}

  tuple<complex<double>, complex<double>> solve(double a, double b, double c) {
    double discriminant = strategy.calculate_discriminant(a, b, c);

    auto plus_result =
        (-complex<double>(b) + sqrt(complex<double>(discriminant))) /
        complex<double>(2 * a);
    auto minus_result =
        (-complex<double>(b) - sqrt(complex<double>(discriminant))) /
        complex<double>(2 * a);

    return {plus_result, minus_result};
  }
};

int main(int argc, char *argv[]) {
  OrdinaryDiscriminantStrategy ordinary;
  RealDiscriminantStrategy real;

  // QuadraticEquationSolver q{ordinary};
  QuadraticEquationSolver q{real};

  auto [plus, minus] = q.solve(1, 7, 12); // should be -3, -4
  // auto [plus, minus] = q.solve(1, 2, 5);

  cout << "Roots: " << plus << ", " << minus << endl;

  return 0;
}
