#include <iostream>
#include <memory>
#include <vector>

#include "Electronics.h"
#include "Grocery.h"
#include "Inventory.h"
#include "Utils.h"

int main() {
  // create inventory
  Inventory myInv;
  myInv.addItem(std::make_shared<Electronics>("E1", "Phone", 35, 399, 24));
  myInv.addItem(std::make_shared<Electronics>("E2", "Laptop", 9, 690, 12));
  myInv.addItem(std::make_shared<Electronics>("E3", "USB C", 120, 12, 128));
  myInv.addItem(
      std::make_shared<Grocery>("G1", "Banana", 58, 2.95, "2026-12-14"));
  myInv.addItem(
      std::make_shared<Grocery>("G2", "Dragon Fruit", 7, 2.95, "2026-12-14"));

  std::cout << "Initial inventory: \n";
  myInv.displayInventory();
  std::cout << '\n';

  const auto lowStock = utils::filterItems(
      myInv, [](const auto& item) { return item->getQuantity() < 10; });

  for (const auto& item : lowStock) {
    item->display();
  }
  std::cout << '\n';

  utils::sortItems(myInv, [](const auto& item) { return item->getQuantity(); });
  myInv.displayInventory();

  return 0;
}
