#include <iostream>
#include <map>
#include <memory>

using namespace std;

enum class Importance { primary, secondary, tertiary };

template <typename T, typename Key = std::string> class Multiton {
public:
  static shared_ptr<T> get(const Key &key) {
    if (const auto i = instances.find(key); i != instances.end()) {
      return i->second;
    }

    auto instance = make_shared<T>();
    instances[key] = instance;
    return instance;
  }

protected:
  Multiton() = default;
  virtual ~Multiton() = default;

private:
  static map<Key, shared_ptr<T>> instances;
};

template <typename T, typename Key>
map<Key, shared_ptr<T>> Multiton<T, Key>::instances;

class Printer {
  static int totalInstanceCount;

public:
  Printer() {
    ++Printer::totalInstanceCount;
    cout << "A total of " << Printer::totalInstanceCount
         << " instances created so far" << endl;
  }
};

int Printer::totalInstanceCount = 0;

int main() {
  typedef Multiton<Printer, Importance> mt;

  auto main = mt::get(Importance::primary);
  auto aux = mt::get(Importance::secondary);
  auto aux2 = mt::get(Importance::secondary);
}
