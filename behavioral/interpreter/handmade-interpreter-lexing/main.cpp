#include <iostream>
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

int main() {
  string input{"(13-4)-(12+1)"};

  auto tokens = lex(input);

  for (auto &t : tokens) {
    cout << " " << t << " ";
  }

  cout << endl;

  return 0;
}
