#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <typename Visitable> struct Visitor {
  virtual void visit(Visitable &obj) = 0;
};

struct VisitorBase {
  virtual ~VisitorBase() = default;
};

struct Expression {
  ~Expression() = default;

  // make sure obj is of type Visitor<T> where T is Expression
  virtual void accept(VisitorBase &obj) {
    using EV = Visitor<Expression>;
    if (auto ev = dynamic_cast<EV *>(&obj))
      ev->visit(*this);
  }
};

struct DoubleExpression : Expression {
  double value;
  DoubleExpression(double value) : value(value) {}

  void accept(VisitorBase &obj) {
    using DE = Visitor<DoubleExpression>;
    if (auto ev = dynamic_cast<DE *>(&obj))
      ev->visit(*this);
  }
};

struct AdditionExpression : Expression {
  Expression *left, *right;
  AdditionExpression(Expression *left, Expression *right)
      : left(left), right(right) {}

  ~AdditionExpression() {
    delete left;
    delete right;
  }

  void accept(VisitorBase &obj) {
    using AE = Visitor<AdditionExpression>;
    if (auto ev = dynamic_cast<AE *>(&obj))
      ev->visit(*this);
  }
};

struct ExpressionPrinter : VisitorBase,
                           Visitor<DoubleExpression>,
                           Visitor<AdditionExpression> {
  void visit(DoubleExpression &obj) override { oss << obj.value; }
  void visit(AdditionExpression &obj) override {
    oss << "(";
    obj.left->accept(*this);
    oss << "+";
    obj.right->accept(*this);
    oss << ")";
  }

  string str() const { return oss.str(); }

private:
  ostringstream oss;
};

int main(int argc, char *argv[]) {
  auto e = new AdditionExpression{
      new DoubleExpression{1},
      new AdditionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};

  ExpressionPrinter ep;
  ep.visit(*e);

  cout << ep.str() << endl;

  return 0;
}
