# Command pattern
An object which represents an instruction to perform a particular action. 
Contains all the information necessary for the action to be taken.

## Summary 
- Encapsulate all details of an operation in a separate object
- Define instructions for applying the command
- Optionally define instructions for undoing the command
- Can create composite commands (macros)

## Motivation
- Ordinary C++ statements are perishable
    - Cannot undo a field/property assignment
    - Cannot directly serialize a sequence of actions (calls)
- Want an object that represents an operation
    - X should change its field Y to the value Z   
    - W should do W()
- Uses: GUI commands, multi-level undo/redo, macro recording and more...

## Command Query Separation
- Command = asking for an action or change
- Query = asking for information
- CQS = having separate means of sending commands and queries
- In GoF book context, both commands and queries are represented with the command design pattern
