# Singleton pattern
A component which is instantiated only once

## Motivation
- For some components it only makes sense to have one in the system
    - Database repo
    - Object factory
- For cases where the constructor call is expensive
    - We only do it once
- Want to prevent anyone creating additional copies
- Need to take care of lazy installation and thread safety
