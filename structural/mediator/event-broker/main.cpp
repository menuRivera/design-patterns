#include <boost/signals2.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace boost;
using namespace boost::signals2;

struct EventData {
  virtual void print() const = 0;
};

struct PlayerScoredData : EventData {
  string player_name;
  int goals_scored_so_far;

  PlayerScoredData(const string &player_name, int goals_scored_so_far)
      : player_name(player_name), goals_scored_so_far(goals_scored_so_far) {}

  void print() const override {
    cout << player_name << " has scored! " << goals_scored_so_far
         << " goals so far" << endl;
  }
};

// mediator
struct Game {
  signal<void(EventData *)> events;
};

struct Player {
  string name;
  int goals_scored{0};
  Game &game;

  Player(const string &name, Game &game) : name(name), game(game) {}
  void score() {
    goals_scored++;
    PlayerScoredData ps{name, goals_scored};
    game.events(&ps);
  }
};

struct Coach {
  Game &game;
  Coach(Game &game) : game(game) {
    game.events.connect([](EventData *e) {
      PlayerScoredData *ps = dynamic_cast<PlayerScoredData *>(e);
      ps->print();
      if (ps && ps->goals_scored_so_far < 3) {
        cout << "coach says: well done, " << ps->player_name << "!\n";
      } else {
        cout << "Unbelivable!" << endl;
      }
    });
  }
};

int main() {
  Game game;
  Player player{"Sam", game};
  Coach coach{game};

  player.score();
  player.score();
  player.score();
}
