#include <iostream>
#include <ostream>
#include <string>

using namespace std;

struct Creature {
  string name;
  int attack, defense;
  Creature(const string &name, int attack, int defense)
      : name(name), attack(attack), defense(defense) {}

  friend ostream &operator<<(ostream &os, const Creature &obj) {
    os << "name: " << obj.name << " attack: " << obj.attack
       << " defense: " << obj.defense << endl;
    return os;
  }
};

class CreatureModifier {
  CreatureModifier *next{nullptr};

protected:
  Creature &creature;

public:
  CreatureModifier(Creature &creature) : creature(creature) {}

  void add(CreatureModifier *cm) {
    if (next)
      next->add(cm);
    else
      next = cm;
  }

  virtual void handle() {
    if (next)
      next->handle();
  }
};

class DoubleAttackModifier : public CreatureModifier {
public:
  DoubleAttackModifier(Creature &creature) : CreatureModifier(creature) {}
  void handle() override {
    creature.attack += 2;
    CreatureModifier::handle(); // allows us to walk the CoR
  }
};

class IncreasedDefenseModificier : public CreatureModifier {
public:
  IncreasedDefenseModificier(Creature &creature)
      : CreatureModifier(creature) {};

  void handle() override {
    if (creature.attack <= 2)
      creature.defense++;

    CreatureModifier::handle(); // allows us to walk the CoR
  }
};

class NoBonusesModifier : public CreatureModifier {
public:
  NoBonusesModifier(Creature &creature) : CreatureModifier(creature) {}

  void handle() override { return; }
};

int main() {
  Creature goblin{"Goblin", 1, 1};

  CreatureModifier root{goblin};

  DoubleAttackModifier r1{goblin};
  DoubleAttackModifier r1_2{goblin};
  IncreasedDefenseModificier r2{goblin};

  NoBonusesModifier curse{goblin};

  root.add(&r1);
  root.add(&curse); // stops CoR
  root.add(&r1_2);
  root.add(&r2);

  root.handle();

  cout << goblin << endl;
}
