#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

using namespace std;

class Memento {
  int balance;

public:
  Memento(int balance) : balance(balance) {}
  friend class BankAccount2;
};

class BankAccount2 {
  int balance{0};
  vector<shared_ptr<Memento>> changes;
  int current;

public:
  BankAccount2(int balance) : balance(balance) {
    changes.emplace_back(make_shared<Memento>(balance));
    current = 0;
  }

  shared_ptr<Memento> deposit(int amount) {
    balance += amount;
    auto m = make_shared<Memento>(balance);
    changes.push_back(m);
    ++current;
    return m;
  }

  void restore(const shared_ptr<Memento> &m) {
    if (m) {
      balance = m->balance;
      changes.push_back(m);
      current = changes.size() - 1;
    }
  }

  shared_ptr<Memento> undo() {
    if (current <= 0)
      return {};

    --current;
    auto m = changes[current];
    balance = m->balance;
    return m;
  }

  shared_ptr<Memento> redo() {
    if (current + 1 >= changes.size())
      return {};

    ++current;
    auto m = changes[current];
    balance = m->balance;
    return m;
  }

  friend ostream &operator<<(ostream &os, const BankAccount2 &obj) {
    return os << "balance: " << obj.balance << endl;
  }
};

int main() {
  BankAccount2 acc{100};

  cout << "initial balance: " << acc << endl;
  acc.deposit(12);
  cout << "+ 12: " << acc << endl;
  acc.deposit(54);
  cout << "+ 54: " << acc << endl;

  cout << acc << endl;

  acc.undo();
  cout << "undo(): " << acc << endl;
  acc.undo();
  cout << "undo(): " << acc << endl;

  acc.redo();
  cout << "redo(): " << acc << endl;
}
