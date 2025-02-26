#include <boost/mpl/vector.hpp>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace msm::front;

vector<string> state_names{
    "off hook"s, "connecting"s, "connected"s, "on hold"s, "destroyed"s,
};

// triggers
struct CallDialed {};
struct HungUp {};
struct CallConnected {};
struct PlacedOnHold {};
struct TakenOffHold {};
struct LeftMessage {};
struct PhoneThrownIntoWall {};

struct PhoneStateMachine : state_machine_def<PhoneStateMachine> {
  bool angry{true};
  struct OffHook : state<> {};
  struct Connecting : state<> {
    // entry state function
    template <class Event, class FSM>
    void on_entry(const Event &event, FSM &fsm) {
      cout << "We are connecting" << endl;
    }
  };
  struct Connected : state<> {};
  struct OnHold : state<> {};
  struct PhoneDestroyed : state<> {};

  // transition definition
  struct PhoneBeingDestroyed {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const &, FSM &, SourceState &, TargetState &) {
      cout << "Phone breaks into a million pieces" << endl;
    };
  };

  // guard
  struct CanDestroyPhone {
    template <class EVT, class FSM, class SourceState, class TargetState>
    bool operator()(EVT const &, FSM &fsm, SourceState &, TargetState &) {
      return fsm.angry;
    };
  };

  // transition table
  struct transition_table
      : mpl::vector<Row<OffHook, CallDialed, Connecting>,
                    Row<Connecting, CallConnected, Connected>,
                    Row<Connected, PlacedOnHold, OnHold>,
                    Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed,
                        PhoneBeingDestroyed, CanDestroyPhone>> {};

  typedef OffHook initial_state;

  template <class FSM, class Event>
  void no_transition(Event const &e, FSM &, int state) {
    cout << "No transition from state " << state_names[state] << " on event "
         << typeid(e).name() << endl;
  }
};

int main(int argc, char *argv[]) {
  msm::back::state_machine<PhoneStateMachine> phone;

  auto info = [&]() {
    auto i = phone.current_state()[0];
    cout << "The phone is currently " << state_names[i] << endl;
  };

  info();
  phone.process_event(CallDialed{});
  info();
  phone.process_event(CallConnected{});
  info();
  phone.process_event(PlacedOnHold{});
  info();
  phone.process_event(PhoneThrownIntoWall{});
  info();

  // no transition example
  phone.process_event(CallDialed{});
  info();

  return 0;
}
