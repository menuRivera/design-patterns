# Proxy pattern
An interface for accessing a particular resource.
A class that functions as an interfaec to a particular resource. That resource may be remote, expensive to construct, or may require logging or some other added functionality.

- Same interface as the underlying object 
- To create a proxy, simply replicate the existing interface of an object 
- Add relevant functionality to the redefined member functions 
- Different proxies have completely different behaviors

## Example
- You are calling foo.bar()
- This assumes that foo is in the same process as bar()
- What if, later on, you want to pull all Foo-related operations into a separate process
    - Can you avoid changing your code?
- Proxy solves this issue:
    - **Same interface, entirely different behavior**

## Proxy vs Decorators 
- Proxy provides an identical interface, decorator provides an enhanced interface
- Decorators typically aggregate what it is decorating; proxies don't
- Proxy might not even be working with a materialized object
