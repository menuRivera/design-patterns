/*
 Implement the Account::process()  function to process different account
 commands. The rules are obvious:

    - success  indicates whether the operation was successful
    - You can only withdraw money if you have enough in your account
*/

#include <iostream>

using namespace std;

struct Command {
  enum Action { deposit, withdraw } action;
  int amount{0};
  bool success{false};
};

struct Account {
  int balance{0};

  void process(Command &cmd) {
    switch (cmd.action) {

    case Command::deposit:
      // this will always be successful
      balance += cmd.amount;
      cmd.success = true;
      break;

    case Command::withdraw:
      if (balance >= cmd.amount) {
        // proceeds
        balance -= cmd.amount;
        cmd.success = true;
      } else {
        cmd.success = false;
      }
      break;
    }
  }
};

int main() {
  Account acc;
  cout << "Balance: " << acc.balance << endl;

  Command deposit_cmd{Command::deposit, 100};
  acc.process(deposit_cmd);
  // should be 100
  cout << "Balance: " << acc.balance << endl;

  Command withdraw_cmd{Command::withdraw, 101};
  acc.process(withdraw_cmd);
  cout << "Balance: " << acc.balance << endl;
}
