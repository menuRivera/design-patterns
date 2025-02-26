/*
Imagine a typical collectible card game which has cards representing creatures.
Each creature has two values: Attack and Health. Creatures can fight each other,
dealing their Attack damage, thereby reducing their opponent's health.

The class CardGame implements the logic for two creatures fighting one another.
However, the exact mechanics of how damage is dealt is different:

    TemporaryCardDamage : In some games (e.g., Magic: the Gathering), unless the
creature has been killed, its health returns to the original value at the end of
combat. PermanentCardDamage : In other games (e.g., Hearthstone), health damage
persists.

You are asked to implement classes TemporaryCardDamageGame  and
PermanentCardDamageGame  that would allow us to simulate combat between
creatures.

Some examples:

    With temporary damage, creatures 1/2 and 1/3 can never kill one another.
With permanent damage, second creature will win after 2 rounds of combat. With
either temporary or permanent damage, two 2/2 creatures kill one another.
*/

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

struct Creature {
  int attack, health;

  Creature(int attack, int health) : attack(attack), health(health) {}
  bool is_dead() { return health <= 0; }
};

struct CardGame {
  vector<Creature> creatures;

  CardGame(const vector<Creature> &creatures) : creatures(creatures) {}

  // return the index of the creature that won (is a live)
  // example:
  // - creature1 alive, creature2 dead, return creature1
  // - creature1 dead, creature2 alive, return creature2
  // - no clear winner: return -1
  // template method here
  int combat(int creature1, int creature2) {
    Creature &c1 = creatures[creature1];
    Creature &c2 = creatures[creature2];

    hit(c1, c2);
    hit(c2, c1);

    if (c1.is_dead() && c2.is_dead())
      return -1;
    else if (c1.is_dead())
      return creature2;
    else if (c2.is_dead())
      return creature1;

    return -1;
  }

  virtual void hit(Creature &attacker, Creature &other) = 0;
};

struct TemporaryCardDamageGame : CardGame {
  TemporaryCardDamageGame(const vector<Creature> &creatures)
      : CardGame(creatures) {}

  void hit(Creature &attacker, Creature &other) override {
    int old_health = other.health;
    other.health -= attacker.attack;

    if (other.health > 0)
      other.health = old_health;
  }
};

struct PermanentCardDamageGame : CardGame {
  PermanentCardDamageGame(const vector<Creature> &creatures)
      : CardGame(creatures) {}

  void hit(Creature &attacker, Creature &other) override {
    other.health -= attacker.attack;
  }
};

int main(int argc, char *argv[]) {
  Creature c1{1, 2};
  Creature c2{1, 3};
  Creature c3{2, 2};
  Creature c4{2, 2};

  vector<Creature> creatures{c1, c2, c3, c4};

  TemporaryCardDamageGame temporary{creatures};

  assert(temporary.combat(0, 1) == -1);
  assert(temporary.combat(0, 1) == -1);

  PermanentCardDamageGame permanent{creatures};

  assert(permanent.combat(0, 1) == -1);
  assert(permanent.combat(0, 1) == 1);
  assert(permanent.combat(2, 3) == -1);

  cout << "All good!" << endl;

  return 0;
}
