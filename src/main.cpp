#include <iostream>
#include <memory>
#include <vector>

#include "Electronics.h"
#include "Exceptions.h"
#include "Grocery.h"
#include "Inventory.h"
#include "Utils.h"

void printTitle(const std::string& title) {
  std::cout << "\n --- " << title << " --- \n";
}

int main() {
  Inventory inv;

  printTitle("Adding items");
  try {
    inv.addItem(std::make_shared<Electronics>("E1", "Phone", 10, 699.99, 24));
    inv.addItem(std::make_shared<Electronics>("E2", "Laptop", 5, 1099.99, 12));
    inv.addItem(
        std::make_shared<Grocery>("G1", "Apple", 100, 0.99, "2026-04-02"));
    inv.addItem(
        std::make_shared<Grocery>("G2", "Milk", 30, 1.49, "2026-04-10"));

    std::cout << "All items added successfully\n";
  } catch (const InventoryException& e) {
    std::cout << "Error: " << e.what() << '\n';
  }

  printTitle("Display inventory");
  inv.displayInventory();

  printTitle("Adding duplicate item");
  try {
    inv.addItem(std::make_shared<Electronics>("E1", "Phone", 1, 699.99, 24));
  } catch (const DuplicateItemException& e) {
    std::cout << "Error: " << e.what() << '\n';
    std::cout << "Duplicate ID: " << e.getItemID() << '\n';
  }

  printTitle("Removing item");
  try {
    inv.removeItem("E2");
    std::cout << "E2 removed successfully\n";
  } catch (const ItemNotFoundException& e) {
    std::cout << "Error: " << e.what() << '\n';
  }

  printTitle("Removing non-existent item");
  try {
    inv.removeItem("X99");
  } catch (const ItemNotFoundException& e) {
    std::cout << "Error: " << e.what() << '\n';
    std::cout << "Missing ID: " << e.getItemID() << '\n';
  }

  printTitle("Updating quantity");
  try {
    inv.updateQuantity("E1", 15);
    std::cout << "Quantity updated successfully\n";
  } catch (const ItemNotFoundException& e) {
    std::cout << "Error: " << e.what() << '\n';
  }

  printTitle("Invalid quantity");
  try {
    inv.updateQuantity("E1", -5);
  } catch (const InvalidValueException& e) {
    std::cout << "Error: " << e.what() << '\n';
  }

  printTitle("Most expensive item");
  try {
    auto item = inv.findMostExpensive();
    item->display();
  } catch (const EmptyInventoryException& e) {
    std::cout << "Error: " << e.what() << '\n';
  }

  printTitle("Empty inventory exception");
  try {
    Inventory emptyInv;
    emptyInv.findMostExpensive();
  } catch (const EmptyInventoryException& e) {
    std::cout << "Error: " << e.what() << '\n';
  }

  return 0;
}
