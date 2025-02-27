#include <iostream>
#include <sstream>

using namespace std;

struct Expression {
  virtual ~Expression() = default;
  virtual void print(ostringstream &oss) = 0;
};

struct DoubleExpression : Expression {
  double value;
  DoubleExpression(double value) : value(value) {}
  void print(ostringstream &oss) override { oss << value; }
};

/**
 *			1+2+3
 *			  +
 *			/   \
 *		   1     +
 *		        /  \
 *		       2    3
 */
struct AdditionExpression : Expression {
  Expression *left, *right;
  AdditionExpression(Expression *left, Expression *right)
      : left(left), right(right) {}

  ~AdditionExpression() {
    delete left;
    delete right;
  }

  void print(ostringstream &oss) override {
    oss << "(";
    left->print(oss);
    oss << "+";
    right->print(oss);
    oss << ")";
  }
};

// print() is the visitor here as far as I understood
int main(int argc, char *argv[]) {
  // (1+(2+3))
  auto e = new AdditionExpression{
      new DoubleExpression{1},
      new AdditionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};

  ostringstream oss;

  e->print(oss);

  cout << oss.str() << endl;

  delete e;
  return 0;
}
