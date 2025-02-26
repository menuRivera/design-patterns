# State pattern
A pattern in which the object's behavior is determined by tis state. An object transitions from one state to another (something needs to trigger a transition).
A formalized construct which manages state and transitions is called a state machine.

## Motivation
- Consider an ordinary telephone
    - What you with it depends on the state of the phone/line
    - If it's ringing or you want to make a call, you can pick it up
    - Phone must be off the hook to talk / make a call
    - If you try calling someone, and it's busy, you put the handset down
- Changes in state can be explicit or in response to event (observer pattern)

## Summary
- **Given sufficient complexity**, it pays to formally define possible states and events/triggers
- Can define 
    - State entry/exit behaviors
    - Action when a particular event causes a transition
    - Guard contitions enabling/disabling transitions
    - Default action when no transitions are found for an event
