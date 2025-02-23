#include <boost/lexical_cast.hpp>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <vector>

using namespace std;

struct Token {
  enum Type { integer, plus, minus, lparen, rparen } type;
  string text;

  Token(Type type, const string &text) : type(type), text(text) {}

  friend ostream &operator<<(ostream &os, const Token &obj) {
    return os << "`" << obj.text << "`";
  }
};

/**
 * Separates a string (input) into tokens
 */
vector<Token> lex(const string &input) {
  vector<Token> result;

  for (int i = 0; i < input.size(); i++) {
    switch (input[i]) {
    case '+':
      result.push_back(Token{Token::plus, "+"});
      break;
    case '-':
      result.push_back(Token{Token::minus, "-"});
      break;
    case '(':
      result.push_back(Token{Token::lparen, "("});
      break;
    case ')':
      result.push_back(Token{Token::rparen, ")"});
      break;
    default:
      // an integer then
      ostringstream buffer;
      buffer << input[i];

      // why i + 1?
      for (int j = i + 1; j < input.size(); j++) {
        // lex every char that is an int
        if (isdigit(input[j])) {
          // if it's 1 and the next char is 5, both of them will be added to
          // buffer here
          buffer << input[j];
          // i incremented so input[j] is not handled twice
          ++i;
        } else {
          // if it's not an int anymore, push the whole number to result
          // (i is not incremented here so the upper for loop can handle it)
          result.push_back(Token{Token::integer, buffer.str()});
          break;
        }
      }
    }
  }

  return result;
}

struct Element {
  virtual int eval() const = 0;
};

struct IntElement : Element {
  int value;

  IntElement(int value) : value(value) {}

  int eval() const override { return value; }
};

struct BinaryOperation : Element {
  enum Type { addition, substraction } type;
  // left hand side, right hand side
  shared_ptr<Element> lhs, rhs;

  int eval() const override {
    auto left = lhs->eval();
    auto right = rhs->eval();

    if (type == addition) {
      return left + right;
    } else {
      return left - right;
    }
  }
};

/**
 * Take a vector of tokens and creates a BinaryOperation out of them
 * ([lhs][operation][rhs]) ready to be evaluated (calling eval()). It can call
 * itself recursively to handle parenthesis operations.
 */
shared_ptr<Element> parse(const vector<Token> &tokens) {
  auto result = make_unique<BinaryOperation>();
  bool have_lhs{false};

  for (size_t i = 0; i < tokens.size(); i++) {
    auto &token = tokens[i];

    switch (token.type) {
    case Token::integer: {
      // note: explicit scoping (using {}) is needed when declaring variables
      // inside case blocks
      int value = boost::lexical_cast<int>(token.text);
      auto integer = make_shared<IntElement>(value);

      if (!have_lhs) {
        result->lhs = integer;
        have_lhs = true;
      } else {
        result->rhs = integer;
      }
      break;
    }
    case Token::plus:
      result->type = BinaryOperation::addition;
      break;
    case Token::minus:
      result->type = BinaryOperation::substraction;
      break;
    case Token::lparen: {
      int j = i;
      for (; j < tokens.size(); ++j)
        if (tokens[j].type == Token::rparen)
          // found the right parenthesis
          break;

      vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
      auto element = parse(subexpression);
      if (!have_lhs) {
        result->lhs = element;
        have_lhs = true;
      } else {
        result->rhs = element;
      }
      i = j;
    } break;
    case Token::rparen:
      // no-op
      break;
    }
  }
  return result;
}

int main() {
  string input{"(13-4)-(12+1)"};

  auto tokens = lex(input);

  for (auto &t : tokens) {
    cout << " " << t << " ";
  }

  auto parsed = parse(tokens);
  cout << input << "=" << parsed->eval() << endl;

  cout << endl;

  return 0;
}
