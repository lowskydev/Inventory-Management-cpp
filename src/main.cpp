#include <iostream>
#include <memory>
#include <vector>

#include "Electronics.h"
#include "Grocery.h"
#include "Inventory.h"

int main() {
  // create inventory
  Inventory myInv;
  myInv.addItem(std::make_shared<Electronics>("E1", "Phone", 2, 399, 24));
  myInv.addItem(std::make_shared<Electronics>("E2", "Laptop", 5, 690, 12));
  myInv.addItem(
      std::make_shared<Grocery>("G1", "Banana", 58, 2.95, "2026-12-14"));

  std::cout << "Initial inventory: \n";
  myInv.displayInventory();
  std::cout << '\n';

  // removing items
  myInv.removeItem("A5");
  myInv.removeItem("E2");

  // update item
  myInv.updateQuantity("A5", 1);
  myInv.updateQuantity("E1", 1);

  std::cout << "\nAfter operations:\n";
  myInv.displayInventory();

  // most expensive
  if (const auto mostExpensiveItem = myInv.findMostExpensive()) {
    std::cout << "\nMost expensive Item: \n";

    mostExpensiveItem->display();
  } else {
    std::cout << "No items in inventory\n";
  }

  // below threshold
  std::cout << "\nThreshold below 5:\n";
  for (const auto newInv = myInv.belowQuantityThreshold(5);
       const auto& item : newInv) {
    item->display();
  }

  // move semantics
  Inventory inv2 = std::move(myInv);
  std::cout << "\nAfter move:\n";
  inv2.displayInventory();

  // empty edge case
  std::cout << "\nEmpty inv:\n";
  Inventory emptyInv;
  emptyInv.findMostExpensive();
  emptyInv.displayInventory();

  return 0;
}
