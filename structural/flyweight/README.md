# Flyweight pattern
A space optimization technique that lets us use less memory by storing externally the data associated with similar objects.

- Avoid redundancy when storing data
- E.g. MMORPG
    - Plenty of users with identical first/last names
    - No sense in storing same first/last name orver and over again
    - Store a list of names and pointers to them
- Store common data externally
- Define the idea of ranges on homogeneous collections
    - Store data related to those ranges
