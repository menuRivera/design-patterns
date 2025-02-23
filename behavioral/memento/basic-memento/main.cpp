#include <iostream>
#include <ostream>

using namespace std;

class Memento {
  int balance;

public:
  Memento(int balance) : balance(balance) {}
  friend class BankAccount;
};

class BankAccount {
  int balance{};

public:
  BankAccount(int balance) : balance(balance) {}

  Memento deposit(int amount) {
    balance += amount;
    // take snapshot
    // return Memento{balance}; //  no need to write Memento here
    return {balance};
  }

  void restore(const Memento &m) { balance = m.balance; }

  friend ostream &operator<<(ostream &os, const BankAccount &obj) {
    return os << "balance: " << obj.balance << endl;
  }
};

int main() {
  BankAccount acc{100};
  auto m1 = acc.deposit(50); // 150
  auto m2 = acc.deposit(25); // 175

  cout << acc << endl;

  acc.restore(m1);
  cout << "back to m1: " << acc << endl;

  acc.restore(m2);
  cout << "back to m2: " << acc << endl;
}
