#include <algorithm>
#include <exception>
#include <iostream>
#include <mutex>
#include <string>
#include <vector>

using namespace std;

// observer
template <typename T> struct Observer {
  virtual void field_changed(T &source, const string &field_name) = 0;
};

// apparently, verctors are not thread safe
// observable
template <typename T> class SaferObservable {
  vector<Observer<T> *> observers;
  // wtf are these for?
  // typedef std::mutex mutex_t;
  // mutex_t mtx;
  // ok i see now
  typedef std::recursive_mutex mutex_t;
  mutex_t mtx;
  // mutex mtx;

public:
  void notifiy(T &source, const string &field_name) {
    scoped_lock<mutex_t> lock{mtx};
    for (auto o : observers) {
      o->field_changed(source, field_name);
    }
  }
  void subscribe(Observer<T> &observer) {
    scoped_lock<mutex_t> lock{mtx};
    observers.push_back(&observer);
  }
  void unsubscribe(Observer<T> *observer) {
    scoped_lock<mutex_t> lock{mtx}; //  this locks execution
    observers.erase(remove(observers.begin(), observers.end(), observer),
                    observers.end());
  }
};

class Person : public SaferObservable<Person> {
  int age;

public:
  Person(int age) : age(age) {}

  int get_age() const { return age; }
  void set_age(int age) {
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

struct TrafficAdministration : Observer<Person> {
  void field_changed(Person &source, const string &field_name) override {
    if (field_name == "age") {
      if (source.get_age() < 17) {
        cout << "You are not old enough to drive" << endl;
      } else {
        cout << "Oh, ok, we no longer care" << endl;
        source.unsubscribe(this);
      }
    }
  }
};

int main() {
  Person person{10};
  TrafficAdministration ta;

  person.subscribe(ta);

  try {
    person.set_age(15);
    person.set_age(16);
    person.set_age(17);
  } catch (exception &e) {
    cerr << "ERROR: " << e.what() << endl;
    return 1;
  }

  person.unsubscribe(&ta);

  return 0;
}
