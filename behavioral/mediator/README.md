# Mediator pattern
A component that facilitates communication betwen other components without them necessarily being aware of each other or having direct reference to each other.

## Summary
- Create the mediator and have each object in the system refer to it
- Mediator engages in biderectional communication with its connected components
- Mediator has functions that components can call
- Components have functions the mediator can call
- Event processing libraries make communication easier to implement

## Motivation
- Components may go in and out of a system at any time
    - Chat room participants
    - Players in an MMORPG
- It makes no sense for them to have direct references to one another
    - Those references may go dead
- Solution: have them all refer to some central component that facilitates communication

