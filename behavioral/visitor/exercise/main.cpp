/*
You are asked to implement a double-dispatch visitor called ExpressionPrinter
for printing different mathematical expressions. The range of expressions covers
addition and multiplication - please put round brackets around addition but not
around multiplication! Also, please avoid any blank spaces in output.

Example:

    Input: AdditionExpression{Literal{2}, Literal{3}}  -- btw, this is
pseudocode, you cannot inline those references unfortunately Output: (2+3)

Here is the corresponding unit test:

    Value v2{2};
    Value v3{3};
    AdditionExpression simple{v2,v3};
    ExpressionPrinter ep;
    ep.accept(simple);
    ASSERT_EQ("(2+3)", ep.str());
*/

// NOTE:
// I think the exercise has the naming of visit() and accept() swapped

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct Value;
struct AdditionExpression;
struct MultiplicationExpression;

struct ExpressionVisitor {
  virtual void accept(Value &v) = 0;
  virtual void accept(AdditionExpression &ae) = 0;
  virtual void accept(MultiplicationExpression &me) = 0;
};

struct Expression {
  // shouldn't it be called accept?
  virtual void visit(ExpressionVisitor &ev) = 0;
};

struct Value : Expression {
  int value;
  Value(int value) : value(value) {}
  void visit(ExpressionVisitor &ev) override { ev.accept(*this); }
};

struct AdditionExpression : Expression {
  Expression &lhs, &rhs;
  AdditionExpression(Expression &lhs, Expression &rhs) : lhs(lhs), rhs(rhs) {}
  void visit(ExpressionVisitor &ev) override { ev.accept(*this); }
};

struct MultiplicationExpression : Expression {
  Expression &lhs, &rhs;
  MultiplicationExpression(Expression &lhs, Expression &rhs)
      : lhs(lhs), rhs(rhs) {}
  void visit(ExpressionVisitor &ev) override { ev.accept(*this); }
};

struct ExpressionPrinter : ExpressionVisitor {
  ostringstream oss;

  string str() const { return oss.str(); }

  void accept(Value &v) override { oss << v.value; }
  void accept(AdditionExpression &ae) override {
    oss << "(";
    ae.lhs.visit(*this);
    oss << "+";
    ae.rhs.visit(*this);
    oss << ")";
  }
  void accept(MultiplicationExpression &me) override {
    me.lhs.visit(*this);
    oss << "*";
    me.rhs.visit(*this);
  };
};

int main(int argc, char *argv[]) {
  Value v2{2};
  Value v3{3};
  AdditionExpression addition{v2, v3};
  MultiplicationExpression mult{v2, v3};

  ExpressionPrinter ep, ep2;

  ep.accept(addition);
  assert("(2+3)" == ep.str());

  ep2.accept(mult);
  assert("2*3" == ep2.str());

  cout << "All good!" << endl;
  return 0;
}
