#include <memory>
#include <ostream>

using namespace std;

struct BankAccount {
  virtual ~BankAccount() = default;
  virtual void deposit(int amount) = 0;
  virtual void withdraw(int amount) = 0;
};

struct CurrentAccount : BankAccount {
  explicit CurrentAccount(const int balance) : balance(balance) {}

  void deposit(int amount) override { balance += amount; }
  void withdraw(int amount) override {
    if (amount <= balance)
      balance -= amount;
  }

  friend ostream &operator<<(ostream &os, const CurrentAccount &obj) {
    return os << "Balance: " << obj.balance << endl;
  }

private:
  int balance;
};

int main() {
  // pointer to a new CurrentAccount
  BankAccount *a = new CurrentAccount(123);
  a->deposit(321);
  delete a;

  // b is the proxy here
  auto b = make_shared<CurrentAccount>(123);
  BankAccount *actual = b.get(); // enhancement
  // don't need to delete pointer (enhancement as well)

  return 0;
}
