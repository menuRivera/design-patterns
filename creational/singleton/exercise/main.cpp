/*
Implementing a singleton is a bit too easy, so you've got a different
challenge.

You are given the function SingletonTester::is_singleton()  defined below. This
function takes a factory, and needs to return true  or false  depending on
whether that factory produces singletons.

This one's actually easy. Ask yourself: what traits do two 'instances' of a
singleton have in common?
*/

#include <functional>
using namespace std;

struct SingletonTester {
  template <typename T> bool is_singleton(function<T *()> factory) {
    T *s1 = factory();
    T *s2 = factory();
    return s1 == s2;
  }
};
