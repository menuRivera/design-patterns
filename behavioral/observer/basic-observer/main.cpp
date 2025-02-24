#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// observer
template <typename T> struct Observer {
  virtual void field_changed(T &source, const string &field_name) = 0;
};

// observable
template <typename T> class Observable {
  vector<Observer<T> *> observers;

public:
  void notifiy(T &source, const string &field_name) {
    for (auto o : observers) {
      o->field_changed(source, field_name);
    }
  }
  // review
  void subscribe(Observer<T> &observer) { observers.push_back(&observer); }
  void unsubscribe(Observer<T> *observer) {
    observers.erase(remove(observers.begin(), observers.end(), observer),
                    observers.end());
  }
};

class Person : public Observable<Person> {
  int age;

public:
  Person(int age) : age(age) {}

  int get_age() const { return age; }
  void set_age(int age) {
    // Person::age = age;
    if (this->age == age)
      return;
    this->age = age;
    notifiy(*this, "age");
  }
};

struct ConsolePersonObserver : public Observer<Person> {
private:
  void field_changed(Person &source, const string &field_name) override {
    cout << "Person's " << field_name << " has changed to " << source.get_age()
         << endl;
  }
};

int main() {
  Person person{10};
  ConsolePersonObserver cpo;

  person.subscribe(cpo);

  person.set_age(11);
  person.set_age(12);

  person.unsubscribe(&cpo);

  // this won't be printed to console
  person.set_age(13);

  return 0;
}
