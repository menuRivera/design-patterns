#include "ChatRoom.hpp"
#include "Person.hpp"

int main() {
  ChatRoom room;
  Person john{"John"};
  Person jane{"Jane"};

  room.join(&john);
  room.join(&jane);

  john.say("hi room");
  jane.say("hi there");

  Person simon{"Simon"};

  room.join(&simon);

  john.pm("Jane", "hi jane");

  simon.say("Hello everyone");
}
