#include <initializer_list>
#include <iostream>
#include <vector>

using namespace std;

struct BankAccount {
  int balance{0};
  int overdraft_limit{-500};

  void deposit(int amount) {
    balance += amount;
    // cout << "deposited " << amount << ", balance is now " << balance << endl;
  }

  bool withdraw(int amount) {
    if (balance - amount >= overdraft_limit) {
      balance -= amount;
      // cout << "withdrew " << amount << ", balance is now " << balance <<
      // endl;
      return true;
    }
    cout << "Exceeded overdraft limit" << endl;
    return false;
  }

  friend ostream &operator<<(ostream &os, const BankAccount &obj) {
    return os << "balance: " << obj.balance;
  }
};

/**
 * Command abstract class
 */
struct Command {
  bool succeeded;
  virtual void call() = 0;
  virtual void undo() = 0;
};

struct BankAccountCommand : Command {
  BankAccount &account;
  enum Action { deposit, withdraw } action;
  int amount;

  BankAccountCommand(BankAccount &account, Action action, int amount)
      : account(account), action(action), amount(amount) {
    succeeded = false; // default
  }

  void call() override {
    switch (action) {
    case deposit:
      account.deposit(amount);
      succeeded = true;
      break;
    case withdraw:
      succeeded = account.withdraw(amount);
      break;
    }
  }
  void undo() override {
    // naive implementation
    if (!succeeded)
      return;
    switch (action) {
    case deposit:
      account.withdraw(amount);
      break;
    case withdraw:
      account.deposit(amount);
      break;
    }
  }
};

struct CompositeBankAccountCommand : vector<BankAccountCommand>, Command {
  CompositeBankAccountCommand(const initializer_list<BankAccountCommand> &items)
      : vector(items) {}

  void call() override {
    for (auto &cmd : *this) {
      cmd.call();
    }
  }

  void undo() override {
    // rbegin and rend are members of vector, nice
    for (auto it = rbegin(); it != rend(); ++it) {
      it->undo();
    }
  }
};

struct DependentCompositeCommand : CompositeBankAccountCommand {
  DependentCompositeCommand(const initializer_list<BankAccountCommand> &items)
      : CompositeBankAccountCommand(items) {}

  void call() override {
    bool ok = true;
    for (auto &cmd : *this) {
      if (ok) {
        cmd.call();
        ok = cmd.succeeded;
      } else {
        cmd.succeeded = false;
      }
    }
  }
};

// struct MoneyTransferCommand : CompositeBankAccountCommand {
struct MoneyTransferCommand : DependentCompositeCommand {
  MoneyTransferCommand(BankAccount &from, BankAccount &to, int amount)
      // : CompositeBankAccountCommand(
      : DependentCompositeCommand(
            {BankAccountCommand{from, BankAccountCommand::withdraw, amount},
             BankAccountCommand{to, BankAccountCommand::deposit, amount}}) {}
};

int main() {
  BankAccount ba, ba2;
  ba.deposit(100);
  cout << "Initial balance: " << ba << endl;

  // must exceed overdraft_limit (500)
  MoneyTransferCommand mt_cmd{ba, ba2, 5000};
  mt_cmd.call();

  cout << "transfer made" << endl;
  cout << ba << endl;
  cout << ba2 << endl;

  mt_cmd.undo();

  cout << "transfer undo" << endl;
  cout << ba << endl;
  cout << ba2 << endl;
}
