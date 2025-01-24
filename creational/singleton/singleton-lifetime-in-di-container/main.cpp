#include "di.hpp"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct IFoo {
  virtual string name() = 0;
};

struct Foo : IFoo {
  static int id;
  Foo() { ++id; }
  string name() override { return "foo"s + boost::lexical_cast<string>(id); };
};

int Foo::id = 0;

struct Bar {
  shared_ptr<IFoo> foo;
};

int main() {
  auto injector = boost::di::make_injector(
      boost::di::bind<IFoo>().to<Foo>().in(boost::di::singleton));

  auto bar1 = injector.create(shared_ptr<Bar>());
  auto bar2 = injector.create(shared_ptr<Bar>());

  cout << bar1->foo->name() << endl;
  cout << bar2->foo->name() << endl;
}
