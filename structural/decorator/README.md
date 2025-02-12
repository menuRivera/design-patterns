# Decorator pattern
Add functionality to already written classes.
Facilitates the addition of behaviours to individual objects.

- Want to augment an object with additional functionality
- Do not want to rewrite or alter existing code (OCP)
- Want to keep new functionality separate (SRP)
- Need to be able to interact with existing structures
- Two options:
    - Aggregate the decorated object
    - Inherit from the decorated object

## Dynamic decorator 
- Keeps a reference to the decorated object(s)
```
ColoredShape{Square{}}
```

## Static decorator
- Uses mixin inheritance
```
ColoredShape<Square>
```
