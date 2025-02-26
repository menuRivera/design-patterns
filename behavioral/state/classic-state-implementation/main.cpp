#include <iostream>

using namespace std;

struct LightSwitch;

struct State {
  virtual void on(LightSwitch *ls) { cout << "Light is already on" << endl; }

  virtual void off(LightSwitch *ls) { cout << "Light is already off" << endl; }
};

struct OnState : State {
  OnState() { cout << "Light is turned on" << endl; }

  void off(LightSwitch *ls) override;
};

struct OffState : State {
  OffState() { cout << "Light is turned off" << endl; }
  void on(LightSwitch *ls) override;
};

class LightSwitch {
  State *state;

public:
  LightSwitch() { state = new OffState(); }

  void set_state(State *state) { this->state = state; }

  void on() { state->on(this); }
  void off() { state->off(this); }
};

void OnState::off(LightSwitch *ls) {
  cout << "Switching light off..." << endl;
  ls->set_state(new OffState());
  delete this;
}
void OffState::on(LightSwitch *ls) {
  cout << "Switching light on..." << endl;
  ls->set_state(new OnState());
  delete this;
}

int main() {
  LightSwitch ls;
  ls.on();
  ls.off();
  ls.off();
}
