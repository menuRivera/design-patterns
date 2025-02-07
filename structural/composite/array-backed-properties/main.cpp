#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>

using namespace std;

class Creature {
  // int strength, agility, intelligence;

  // we replace the individual props of the class by this enum + array

  enum Abilities { str, agl, intl, count };
  std::array<int, count> abilities;

public:
  int get_strength() const { return abilities[str]; }
  void set_strength(int value) { abilities[str] = value; }

  int get_agility() const { return abilities[agl]; }
  void set_agility(int value) { abilities[agl] = value; }

  int get_intelligence() const { return abilities[intl]; }
  void set_intelligence(int value) { abilities[intl] = value; }

  int sum() const {
    return std::accumulate(abilities.begin(), abilities.end(), 0);
  }

  // so we can use dynamically generated count prop
  double avarege() const { return sum() / (double)count; }

  // and use array-intended operations like max_element and accumulate
  int max() const {
    return *std::max_element(abilities.begin(), abilities.end());
  }
};

int main() {
  Creature orc;
  orc.set_strength(16);
  orc.set_agility(11);
  orc.set_intelligence(9);

  cout << "The orc has an avarege statistic of " << orc.avarege()
       << " and a maximum statistic of " << orc.max() << endl;

  return 0;
}
