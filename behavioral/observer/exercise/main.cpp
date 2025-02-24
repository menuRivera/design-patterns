/*
Imagine a game where one or more rats can attack a player. Each individual rat
has an attack  value of 1. However, rats attack as a swarm, so each rat's attack
value is equal to the total number of rats in play.

Given that a rat enters play through the constructor and leaves play (dies) via
its destructor, please implement the Game  and Rat  classes so that, at any
point in the game, the attack  value of a rat is always consistent.
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

struct IRat {
  int attack;
  virtual void set_attack(int value) = 0;
};

struct Game {
  vector<IRat *> rats;

  void update_attack() {
    int attack_value = rats.size();
    for (auto &rat : rats) {
      rat->set_attack(attack_value);
    }
  }

  void add_rat(IRat &rat) {
    rats.push_back(&rat);
    update_attack();
  }

  void remove_rat(IRat &rat) {
    rats.erase(remove(rats.begin(), rats.end(), &rat), rats.end());
    update_attack();
  }
};
struct Rat : IRat {
  Game &game;
  int attack{1};

  Rat(Game &game) : game(game) { game.add_rat(*this); }
  ~Rat() { game.remove_rat(*this); }

  void set_attack(int value) override { attack = value; }
};

int main() {
  Game game;
  Rat rat{game};
  Rat rat2{game};

  assert(rat.attack == 2);

  Rat rat3{game};

  assert(rat.attack == 3);
  assert(rat2.attack == 3);
  assert(rat3.attack == 3);

  cout << "All good!" << endl;

  //
  return 0;
}
