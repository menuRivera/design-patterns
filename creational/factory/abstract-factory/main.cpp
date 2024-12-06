#include "DrinkFactory.hpp"
#include "HotDrink.hpp"
#include <memory>

unique_ptr<HotDrink> make_drink(string type) {
  unique_ptr<HotDrink> drink;
  if (type == "tea") {
    drink = make_unique<Tea>();
    drink->prepare(200);
  } else {
    drink = make_unique<Coffee>();
    drink->prepare(150);
  }

  return drink;
};

using namespace std;

int main() {
  // auto d = make_drink("tea");
  DrinkFactory df;
  df.make_drink("coffee");

  return 0;
}
