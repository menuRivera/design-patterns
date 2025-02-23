/*
You are asked to write an expression processor for simple numeric expressions
with the following constraints:

- Expressions use integral values (e.g., "13" ), single-letter variables defined
in variables , as well as + and - operators only.
- There is no need to support braces or any other operations.
- If a variable is not found in Variables (or if we encounter a variable with >1
letter, e.g. ab), the evaluator returns 0 (zero)
- In case of any parsing failure, evaluator returns 0

Example:

    calculate("1+2+3")  should return 6
    calculate("1+2+xy")  should return 0
    calculate("10-2-x")  when x=3 is in variables should return 5
*/

#include <boost/lexical_cast.hpp>
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

struct ExpressionProcessor {
  map<char, int> variables;

  int calculate(const string &expression) {
    int result = 0;
    char current_operation = '+';

    for (size_t i = 0; i < expression.size(); i++) {
      char const &current_item = expression[i];
      cout << "current_item: " << current_item << endl;
      switch (current_item) {
      case '+':
        current_operation = '+';
        cout << "set operation to +" << endl;
        break;
      case '-':
        current_operation = '-';
        cout << "set operation to -" << endl;
        break;
      default: {
        // any other character
        ostringstream buffer;

        if (isdigit(current_item)) {
          // if it's a number
          cout << "isdigit" << endl;
          buffer << current_item;
        } else if (variables[current_item] != 0) {
          cout << "is a variable" << endl;
          // if it's a variable
          buffer << variables[current_item];
        } else {
          // not a number nor a variable
          return 0;
        }

        for (size_t j = i + 1; j < expression.size(); j++) {
          char const &next_item = expression[j];
          cout << "next_item: " << next_item << endl;
          // find subsequent numbers
          if (isdigit(next_item)) {
            cout << "isdigit" << endl;
            buffer << next_item;
            i++;
          } else if (variables[next_item] != 0) {
            cout << "is a variable" << endl;
            // it is a variable
            buffer << variables[next_item];
            i++;
          } else {
            // break loop
            break;
          }
        }

        if (current_operation == '+') {
          // result += boost::lexical_cast<int>(buffer.str());
          result += stoi(buffer.str());
        } else {
          // result -= boost::lexical_cast<int>(buffer.str());
          result -= stoi(buffer.str());
        }
        break;
      }
      }
    }

    return result;
  }
};

int main() {
  ExpressionProcessor processor;

  processor.variables['x'] = 3;

  int first_result = processor.calculate("10-2-3+x"); // should be 8

  cout << "result: " << first_result << endl;

  return 0;
}
