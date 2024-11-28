#include <boost/lexical_cast.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace boost;

struct Journal {
  string title;
  vector<string> entries;

  // constructor
  Journal(const string &title) : title(title) {}

  void add_entry(const string &entry) {
    static int count = 1;
    entries.push_back(lexical_cast<string>(count++) + ": " + entry);
  }

  /**
   * This breaks the single responsability principle, as it's adding more
   * 'jobs' to the atomic and well-defined Journal class
   */
  // void save(const string &filename) {
  //   ofstream ofs(filename);
  //   for (auto &e : entries) {
  //     ofs << e << endl;
  //   }
  // }
};

struct PersistanceManager {
  static void save(const Journal &j, const string &filename) {
    ofstream ofs(filename);
    for (auto &e : j.entries) {
      ofs << e << endl;
    }
  }
};

int main() {
  Journal journal{"Dear diary"};

  journal.add_entry("I ate a bug");
  journal.add_entry("I cried today");

  PersistanceManager pm;
  pm.save(journal, "my_diary.txt");

  getchar();
  return 0;
}
