#include <iostream>
#include <sstream>

using namespace std;

struct Expression {
  virtual ~Expression() = default;
  // virtual void print(ostringstream &oss) = 0; // no need for this anymore
};

struct DoubleExpression : Expression {
  double value;
  DoubleExpression(double value) : value(value) {}
};

struct AdditionExpression : Expression {
  Expression *left, *right;
  AdditionExpression(Expression *left, Expression *right)
      : left(left), right(right) {}

  ~AdditionExpression() {
    delete left;
    delete right;
  }
};

struct ExpressionPrinter {
  ostringstream oss;
  void print(Expression *e) {
    // downsides of this approach:
    // runtime cost of dynamic_cast
    // need to add if statements for every type of expression
    if (auto de = dynamic_cast<DoubleExpression *>(e)) {
      oss << de->value;
    } else if (auto ae = dynamic_cast<AdditionExpression *>(e)) {
      oss << "(";
      print(ae->left);
      oss << "+";
      print(ae->right);
      oss << ")";
    }
  }
  string str() const { return oss.str(); }
};

// print() is the visitor here as far as I understood
int main(int argc, char *argv[]) {
  // (1+(2+3))
  auto e = new AdditionExpression{
      new DoubleExpression{1},
      new AdditionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};

  ExpressionPrinter ep;
  ep.print(e);
  cout << ep.str();

  delete e;
  return 0;
}
