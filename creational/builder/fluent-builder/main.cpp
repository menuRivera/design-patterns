#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct HtmlBuilder;

class HtmlElement {
  friend class HtmlBuilder;
  string name, text;
  vector<HtmlElement> elements;
  const size_t indent_size = 2;

  HtmlElement() {}
  HtmlElement(const string &name, const string &text)
      : name(name), text(text) {}

public:
  string str(int indent = 0) const {
    ostringstream oss;
    string i(indent_size * indent, ' ');

    oss << i << "<" << name << ">" << endl;

    if (text.size() > 0) {
      oss << string(indent_size * (indent + 1), ' ') << text << endl;
    }

    for (const auto &e : elements) {
      oss << e.str(indent + 1);
    }

    oss << i << "</" << name << ">" << endl;

    return oss.str();
  }

  // doesn't work bc HtmlBuilder is defined below this line
  // static HtmlBuilder build(string root_name) {
  //   // return type is inferred
  //   return {root_name};
  // }

  // we only define the signature of the build() method
  static HtmlBuilder build(string root_name);
};

struct HtmlBuilder {
  HtmlElement root;

  HtmlBuilder(string root_name) { root.name = root_name; }

  /**
   * Here, you basically return the object you are working with
   */
  HtmlBuilder &add_child(string child_name, string child_text) {
    HtmlElement e{child_name, child_text};
    root.elements.emplace_back(e);
    return *this;
  }
  string str() const { return root.str(); }

  /**
   * We use this to return the HtmlElement when expected
   */
  operator HtmlElement() { return root; }
};

/**
 * We define the build method here bc HtmlBuilder is below HtmlElement
 */
HtmlBuilder HtmlElement::build(string root_name) { return {root_name}; };

int main() {
  /*
   * Example without Builder pattern
   */
  string text = "hello";
  string output;
  output += "<p>";
  output += text;
  output += "</p>";
  cout << output << endl;

  string words[] = {"Hello", "world"};
  ostringstream oss;
  oss << "<ul>";
  for (auto w : words) {
    oss << "<li>" << w << "</li>";
  }
  oss << "</ul>";
  cout << oss.str() << endl;

  /*
   * Using Builder pattern
   */
  HtmlBuilder builder{"ul"};
  builder.add_child("li", "hello");
  builder.add_child("li", "world");

  cout << builder.str() << endl;

  /*
   * Using a Fluent Builder pattern
   */
  HtmlBuilder fluent{"ul"};
  fluent.add_child("li", "hello")
      .add_child("li", "world")
      .add_child("li", "onemore");

  cout << fluent.str() << endl;

  // with the build() method
  HtmlBuilder builder2 = HtmlElement::build("body")
                             .add_child("p", "hello")
                             .add_child("p", "world");

  cout << builder2.str() << endl;

  return 0;
}
