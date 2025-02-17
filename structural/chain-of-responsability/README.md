# Chain of Responsability Pattern
Sequence of handlers processing an event one after another.
A cahin of components who all get a chance to process a command or query, optionally having default processing implementation an an ability to terminate the processing chain.

- CoR can implemented as 
    - A chain of pointers/references (singly linked list)
    - Centralized list
- Enlist objects in the chain, possibly controlling their order
- Object removal from chain (e.g. disconnect from a signal)

## Example
- Unethical behavior by an employee; who takes the blame?
    - Employee
    - Manager
    - CEO
- You click a graphical element on a form
    - Button handles it, stops further processing
    - Underlying group box
    - Underlying window
