# Strategy pattern
Enables the exact behavior of a system to be slected either at run-time (dynamic) or compile-time (static).
It is also kwown as policy.

## Motivation 
- Many algorithms can be decomposed into higher and lower level parts
- Making tea can be decomposed into 
    - The process of making a hot beverage (boil water, pour into cup); and
    - Tea specific things (put teabag into water).
- The high level algorithm can then be reused for making coffee or hot chocolate
    - Supported by beverage-specific strategies
