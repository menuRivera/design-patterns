// event broker = cor + observer (signals2) + cqs
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

#include <boost/algorithm/string.hpp>
#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/signals2.hpp> // events

using namespace boost;
using namespace boost::signals2;

/**
 * Payload for emitted events
 */
struct Query {
  string creature_name;
  enum Argument { attack, defense } argument;
  int result;
  Query(const string &creature_name, Argument argument, int result)
      : creature_name(creature_name), argument(argument), result(result) {}
};

/**
 * Mediator
 */
struct Game {
  // for events
  signal<void(Query &)> queries;
};

/**
 * Actor
 */
struct Creature {
  Game &game;
  int attack, defense;
  string name;

public:
  Creature(Game &game, int attack, int defense, const string &name)
      : game(game), attack(attack), defense(defense), name(name) {}

  /**
   * Creates a new query and propagates it among subscribers for them to modify
   * it(?)
   */
  int get_attack() const {
    Query q{name, Query::Argument::attack, attack};
    game.queries(q);
    return q.result;
  }

  friend ostream &operator<<(ostream &os, const Creature &creature) {
    return os << "attack: " << creature.get_attack()
              << " name: " << creature.name;
  }
};

/**
 * Base Modifier class, meant to be inherited.
 */
class CreatureModifier {
  Game &game;
  Creature &creature;

public:
  CreatureModifier(Game &game, Creature &creature)
      : game(game), creature(creature) {}

  virtual ~CreatureModifier() = default;
};

/**
 * This will subscribe to game.queries to add (or remove) stats to creatures
 */
class DoubleAttackModifier : public CreatureModifier {
  connection conn;

public:
  // constructor
  DoubleAttackModifier(Game &game, Creature &creature)
      : CreatureModifier(game, creature) {
    conn = game.queries.connect([&](Query &q) {
      // must match creature name
      // must be attack modifier (Query::Argument::attack)
      if (q.creature_name == creature.name &&
          q.argument == Query::Argument::attack) {
        // modify query result.
        // remember that Creature.get_attack() will return `result` instead of
        // the attack prop directly
        q.result += 2;
      }
    });
  }

  ~DoubleAttackModifier() { conn.disconnect(); }
};

int main() {
  Game game;

  Creature goblin{game, 2, 2, "Strong Goblin"};
  // default values
  cout << goblin << endl;

  {
    // temporary, will deconstruct 'dam' when reaching out of scope
    DoubleAttackModifier dam{game, goblin};
    cout << goblin << endl;
  }

  // should be back to normal
  cout << goblin << endl;
}
