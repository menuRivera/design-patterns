/*
Our system has any number of instances of Participant  classes. Each Participant
has a value  integer, initially zero.

A participant can say()  a particular value, which is broadcast to all other
participants. At this point in time, every other participant is obliged to
increase their value  by the value being broadcast.

Example:

    Two participants start with values 0 and 0 respectively
    Participant 1 broadcasts the value 3. We now have Participant 1 value = 0,
Participant 2 value = 3 Participant 2 broadcasts the value 2. We now have
Participant 1 value = 2, Participant 2 value = 3
*/

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

struct IParticipant {
  virtual void say(int value) = 0;
  virtual void increment_by(int value) = 0;
};

struct Mediator {
  vector<IParticipant *> participants;

  void handle_say(IParticipant *from, int value) {
    // increment <value> to all participants except p
    cout << "New message from: " << from << ", value: " << value << endl;
    for (auto p : participants) {
      if (p != from) {
        // increment
        p->increment_by(value);
      }
    }
  }
};

struct Participant : IParticipant {
  int value{0};
  Mediator &mediator;

  Participant(Mediator &mediator) : mediator(mediator) {
    mediator.participants.push_back(this);
  }

  void say(int value) override { mediator.handle_say(this, value); }
  void increment_by(int value) override { this->value += value; }
};

int main() {
  Mediator m;

  Participant p1{m};
  Participant p2{m};
  Participant p3{m};

  p1.say(3);

  assert(p1.value == 0);
  assert(p2.value == 3);
  assert(p3.value == 3);

  p2.say(1);

  assert(p1.value == 1);
  assert(p2.value == 3);
  assert(p3.value == 4);

  cout << "All good!\n";
}
