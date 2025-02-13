/*
 * Orders system example creted with gemini
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Subsystem 1: Order Management
class Order {
  int id_;
  string items_;

public:
  Order(int id, const string &items) : id_(id), items_(items) {}

  int getId() const { return id_; }
  string getItems() const { return items_; }
};

class OrderManager {
  vector<Order> orders_;

public:
  void createOrder(const Order &order) {
    cout << "Order " << order.getId()
         << " created with items: " << order.getItems() << endl;
    orders_.push_back(
        order); // In a real system, you'd likely interact with a database here
  }

  Order getOrder(int id) {
    for (const auto &order : orders_) {
      if (order.getId() == id) {
        return order;
      }
    }
    return Order(-1, ""); // Return a dummy order if not found (better error
                          // handling in real code)
  }
};

// Subsystem 2: Payment Processing
class PaymentProcessor {
public:
  bool processPayment(int orderId, double amount) {
    cout << "Processing payment of $" << amount << " for order " << orderId
         << endl;
    // Simulate payment processing (in reality, this would involve external
    // services)
    return true; // In a real application, you'd have more robust logic here
  }
};

// Subsystem 3: Inventory Management
class InventoryManager {
public:
  bool checkInventory(const string &items) {
    cout << "Checking inventory for items: " << items << endl;
    // Simulate inventory check (in a real system, this would interact with a
    // database)
    return true; //  In a real application, you'd have more robust logic here
  }

  void updateInventory(const string &items) {
    cout << "Updating inventory for items: " << items << endl;
    // Simulate inventory update
  }
};

// Facade class
class OrderFacade {
  OrderManager *orderManager_;
  PaymentProcessor *paymentProcessor_;
  InventoryManager *inventoryManager_;
  int nextOrderId_ = 1; // Simple ID generation

public:
  OrderFacade()
      : orderManager_(new OrderManager()),
        paymentProcessor_(new PaymentProcessor()),
        inventoryManager_(new InventoryManager()) {}
  ~OrderFacade() {
    delete orderManager_;
    delete paymentProcessor_;
    delete inventoryManager_;
  }

  bool placeOrder(const string &items, double amount) {
    Order newOrder(nextOrderId_++, items); // Simple ID generation
    orderManager_->createOrder(newOrder);

    if (!inventoryManager_->checkInventory(items)) {
      cout << "Inventory check failed. Order cannot be placed." << endl;
      return false;
    }

    if (!paymentProcessor_->processPayment(newOrder.getId(), amount)) {
      cout << "Payment failed. Order cannot be placed." << endl;
      return false;
    }

    inventoryManager_->updateInventory(items);
    cout << "Order placed successfully!" << endl;
    return true;
  }

  Order getOrderStatus(int orderId) { return orderManager_->getOrder(orderId); }
};

int main() {
  OrderFacade facade;
  facade.placeOrder("Laptop, Mouse", 1200.00);
  facade.placeOrder("Keyboard", 75.00);

  Order myOrder = facade.getOrderStatus(1);
  cout << "Order " << myOrder.getId() << " contains " << myOrder.getItems()
       << endl;

  return 0;
}
