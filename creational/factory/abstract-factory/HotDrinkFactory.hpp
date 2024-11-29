#pragma once
#include "HotDrink.hpp"
#include <memory>

using namespace std;

struct HotDrinkFactory { // abstract factory
  virtual unique_ptr<HotDrink> make() const = 0;
};

struct TeaFactory : HotDrinkFactory {
  unique_ptr<HotDrink> make() const override { return make_unique<Tea>(); }
};

struct CoffeeFactory : HotDrinkFactory {
  unique_ptr<HotDrink> make() const override { return make_unique<Coffee>(); }
};
