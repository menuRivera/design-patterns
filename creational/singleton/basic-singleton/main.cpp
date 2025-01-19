#include <boost/lexical_cast.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;
using namespace boost;

class SingletonDatabase {
  map<string, int> capitals;

  SingletonDatabase() {
    // cout << "Initializing database..." << endl;
    ifstream ifs("capitals.txt");
    string s, s2;

    while (getline(ifs, s)) {
      // cout << s << endl;
      getline(ifs, s2);
      int population = lexical_cast<int>(s2);
      // cout << population << endl;
      capitals[s] = population;
    }
  }

public:
  // assure nobody can replicate the thing
  SingletonDatabase(SingletonDatabase const &) = delete;
  void operator=(SingletonDatabase const &) = delete;

  static SingletonDatabase &get() {
    static SingletonDatabase db;
    return db;
  }

  int get_population(const string &name) { return capitals[name]; }
};

int main() {
  string city = "Osaka";
  cout << city << " has a population "
       << SingletonDatabase::get().get_population(city) << endl;

  return 0;
}
