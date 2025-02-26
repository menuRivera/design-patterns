/*
A combination lock is a lock that opens after the right digits have been
entered. A lock is preprogrammed with a combination (e.g., 12345 ) and the user
is expected to enter this combination to unlock the lock.

The lock has a status  field that indicates the state of the lock. The rules
are:

    If the lock has just been locked (or at startup), the status is LOCKED.
    If a digit has been entered, that digit is shown on the screen. As the user
enters more digits, they are added to Status. If the user has entered the
correct sequence of digits, the lock status changes to OPEN. If the user enters
an incorrect sequence of digits, the lock status changes to ERROR.

Please implement the CombinationLock  class to enable this behavior. Be sure to
test both correct and incorrect inputs.

Here is an example unit test for the lock:

    CombinationLock cl({1,2,3});
    ASSERT_EQ("LOCKED", cl.status);
    cl.enter_digit(1);
    ASSERT_EQ("1", cl.status);
    cl.enter_digit(2);
    ASSERT_EQ("12", cl.status);
    cl.enter_digit(3);
    ASSERT_EQ("OPEN", cl.status);
*/

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CombinationLock {
  vector<int> combination;

public:
  string status{"LOCKED"};

  CombinationLock(const vector<int> &combination) : combination(combination) {}

  void enter_digit(int digit) {
    string combination_as_string;
    for (int d : combination) {
      combination_as_string += to_string(d);
    }

    if (status == "LOCKED") {
      status = to_string(digit);
    } else {
      status += to_string(digit);
    }

    if (status == combination_as_string) {
      status = "OPEN";
      return;
    }

    if (status.length() == combination_as_string.length()) {
      status = "ERROR";
    }
  }
};

int main(int argc, char *argv[]) {
  CombinationLock cl({1, 2, 3});
  assert("LOCKED" == cl.status);

  cout << cl.status << endl;
  cl.enter_digit(1);
  assert("1" == cl.status);

  cout << cl.status << endl;

  cl.enter_digit(2);
  assert("12" == cl.status);
  cout << cl.status << endl;

  cl.enter_digit(3);
  assert("OPEN" == cl.status);
  cout << cl.status << endl;

  cout << "All good!" << endl;
  return 0;
}
