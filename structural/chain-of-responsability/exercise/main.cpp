/*
You are given a game scenario with classes Goblin  and GoblinKing . Please
implement the following rules:

    A goblin has base 1 attack/1 defense (1/1),
        a goblin king is 3/3.
    When the Goblin King is in play, every other goblin gets +1 Attack.
    Goblins get +1 to Defense for every other Goblin in play (a GoblinKing is a
Goblin!).

Example:

    Suppose you have 3 ordinary goblins in play. Each one is a 1/3 (1/1 + 0/2
defense bonus). A goblin king comes into play. Now every ordinary goblin is a
2/4 (1/1 + 0/3 defense bonus from each other + 1/0 from goblin king) Meanwhile,
the goblin king itself is 3/6 (3/3 + 0/3 defense bonus from other goblins)

Here is an example of the kind of test that will be run on the system:

    Game game;
    Goblin goblin(game);
    game.creatures.push_back(&goblin);
    ASSERT_EQ(1, goblin.get_attack());
    ASSERT_EQ(1, goblin.get_defense());
*/

#include <iostream>
#include <vector>

using namespace std;

struct Creature;

struct Game {
  vector<Creature *> creatures;
};

// wtf is this for?
// nvm
struct StatQuery {
  enum Statistic { attack, defense } statistic;
  int result;
};

struct Creature {
protected:
  Game &game;
  int base_attack, base_defense;

public:
  Creature(Game &game, int base_attack, int base_defense)
      : game(game), base_attack(base_attack), base_defense(base_defense) {
    game.creatures.push_back(this);
  }
  virtual int get_attack() = 0;
  virtual int get_defense() = 0;
  virtual void query(void *source, StatQuery &sq) = 0;
};

class Goblin : public Creature {
  int get_statistic(StatQuery::Statistic stat) {
    StatQuery q{stat, 0};
    for (auto c : game.creatures) {
      c->query(this, q);
    }

    return q.result;
  }

public:
  Goblin(Game &game, int base_attack, int base_defense)
      : Creature(game, base_attack, base_defense) {}

  Goblin(Game &game) : Creature(game, 1, 1) {}

  int get_attack() override { return get_statistic(StatQuery::attack); }
  int get_defense() override { return get_statistic(StatQuery::defense); }

  void query(void *source, StatQuery &sq) override {
    if (source == this) {
      switch (sq.statistic) {
      case StatQuery::attack:
        sq.result += base_attack;
        break;
      case StatQuery::defense:
        sq.result += base_defense;
        break;
      }
    } else {
      if (sq.statistic == StatQuery::defense) {
        sq.result++;
      }
    }
  }

  friend ostream &operator<<(ostream &os, Goblin &obj) {
    return os << obj.get_attack() << "/" << obj.get_defense();
  }
};

class GoblinKing : public Goblin {
public:
  GoblinKing(Game &game) : Goblin(game, 3, 3) {}

  void query(void *source, StatQuery &sq) override {
    if (source != this && sq.statistic == StatQuery::attack) {
      sq.result++;
    } else {
      Goblin::query(source, sq);
    }
  }
};

int main() {
  Game game;
  Goblin goblin(game);
  Goblin goblin2(game);
  Goblin goblin3(game);
  GoblinKing king(game);
  Goblin goblin4(game);

  // game.creatures.push_back(&goblin);

  cout << "Goblin1: " << goblin << endl;
  cout << "Goblin2: " << goblin2 << endl;
  cout << "Goblin3: " << goblin3 << endl;
  cout << "King: " << king << endl;
  cout << "Goblin4: " << goblin4 << endl;
}
