#include <iostream>

using namespace std;

// skeleton of the algorithm
// Base class
class Game {
public:
  Game(int number_of_players) : number_of_players(number_of_players) {}

  // template method
  void run() {
    start();
    while (!have_winner()) {
      take_turn();
    }
    cout << "Player " << get_winner() << " wins." << endl;
  }

protected:
  int number_of_players;
  int current_player{0};

  virtual void start() = 0;
  virtual bool have_winner() = 0;
  virtual void take_turn() = 0;
  virtual int get_winner() = 0;
};

class Chess : public Game {
public:
  Chess() : Game(2) {}

protected:
  void start() override {
    cout << "Starting a game of chess with " << number_of_players << " players"
         << endl;
  }
  bool have_winner() override { return turn == max_turns; }
  void take_turn() override {
    cout << "Turn " << turn << " taken by " << current_player << endl;
    ++turn;
    current_player = (current_player + 1) % number_of_players;
  }
  int get_winner() override { return current_player; }

private:
  int turn{0}, max_turns{10};
};

int main(int argc, char *argv[]) {
  Chess chess;
  chess.run();

  return 0;
}
