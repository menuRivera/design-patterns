#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace html {
struct Tag {
  string name;
  string text;
  vector<Tag> children;
  vector<pair<string, string>> attributes;

  /**
   * Overload the << operator so the Tag class can be correctly printed to
   * output streams
   */
  friend ostream &operator<<(ostream &os, const Tag &tag) {
    os << "<" << tag.name;

    for (const auto &att : tag.attributes)
      os << " " << att.first << "=\"" << att.second << "\"";

    if (tag.children.size() == 0 && tag.text.length() == 0) {
      os << "/>" << endl;
    } else {
      os << ">" << endl;

      if (tag.text.length())
        os << tag.text << endl;

      for (const auto &child : tag.children)
        os << child;

      os << "</" << tag.name << ">" << endl;
    }

    return os;
  }

  // we protect the constructors so that only deried classes can create Tag
  // elements
protected:
  Tag(const string &name, const string &text) : name{name}, text{text} {}
  Tag(const string &name, const vector<Tag> &children)
      : name{name}, children{children} {}
};

// Derived classes
struct P : Tag {
  explicit P(const string &text) : Tag{"p", text} {}
  P(initializer_list<Tag> children) : Tag("p", children) {}
};
struct IMG : Tag {
  explicit IMG(const string &url) : Tag{"img", ""} {
    attributes.emplace_back(make_pair("src", url));
  }
};
} // namespace html

int main() {
  using namespace html;

  cout <<

      P{IMG{"http://pokemon.com/pikachu.png"}}

       << endl;

  return 0;
}
