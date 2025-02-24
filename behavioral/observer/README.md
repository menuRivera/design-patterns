# Observer pattern
Getting notification when things happen

An observer is an object that wishes to be informed about events happening in the system. The entity generating the events is an observable.

## Motiviation
- We need to be informed when certain things happen
    - Object does someting
    - Some external event occurs
- We want to listen to events and notified when they ocurr

## Terminology 
- event / subscriber
- signal / slot
(they are the same)

## Summary
- Two participants:
    - Observable provides a way of subscribing to an event
    - Observer performs the subscription
- Observable implementation is always intrusive (observer doesn't need to be)
- Multhreading/reentrant use can cause issues
- Ready-made implementations are available
