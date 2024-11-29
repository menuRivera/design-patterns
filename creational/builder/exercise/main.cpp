#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

using namespace std;

class CodeBuilder {
  string code;
  string indent_block = "  ";

public:
  CodeBuilder(const string &class_name) {
    ostringstream oss;
    oss << "class " << class_name << "\n";
    oss << "{\n";

    code = oss.str();
  }

  CodeBuilder &add_field(const string &name, const string &type) {
    ostringstream oss;
    oss << indent_block << type << " " << name << ";\n";

    code += oss.str();
    return *this;
  }

  friend ostream &operator<<(ostream &os, const CodeBuilder &obj) {
    return os << obj.code << "};";
  }
};

int main() {
  auto cb =
      CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");

  cout << cb;

  return 0;
}
