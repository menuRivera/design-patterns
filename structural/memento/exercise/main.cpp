/*
A TokenMachine  is in charge of keeping tokens. Each Token  is a reference type
with a single numerical value. The machine supports adding tokens and, when it
does, it returns a memento representing the state of that system at that given
time.

You are asked to fill in the gaps and implement the Memento design pattern for
this scenario. Pay close attention to the situation where a token is fed in as a
smart pointer and its value is subsequently changed on that pointer - you still
need to return the correct system snapshot!
*/

#include <iostream>
#include <memory>
#include <ostream>
#include <vector>
using namespace std;

struct Token {
  int value;
  Token(int value) : value(value) {}
};

struct Memento {
  vector<shared_ptr<Token>> tokens;

  friend ostream &operator<<(ostream &os, Memento &obj) {
    return os << "tokens.size(): " << obj.tokens.size()
              << ", tokens[0].value: " << obj.tokens[0]->value << endl;
  }
};

struct TokenMachine {
  vector<shared_ptr<Token>> tokens;

  Memento add_token(int value) { return add_token(make_shared<Token>(value)); }

  // adds the token to the set of tokens and returns the
  // snapshot of the entire system
  Memento add_token(const shared_ptr<Token> &token) {
    tokens.push_back(token);

    Memento m;
    for (auto t : tokens) {
      m.tokens.emplace_back(make_shared<Token>(t->value));
    }
    return m;

    // return {tokens};
  }

  // reverts the system to a state represented by the token
  void revert(const Memento &m) {
    // tokens = m.tokens;
    tokens.clear();

    for (auto t : m.tokens) {
      tokens.emplace_back(make_shared<Token>(t->value));
    }
  }

  friend ostream &operator<<(ostream &os, TokenMachine &obj) {
    return os << "tokens.size(): " << obj.tokens.size() << endl;
  }
};

int main() {
  TokenMachine tm;
  cout << tm;

  auto m1 = tm.add_token(10); // 1
  cout << tm;

  auto m2 = tm.add_token(20); // 2
  cout << tm;

  tm.revert(m1);
  cout << tm;
}
