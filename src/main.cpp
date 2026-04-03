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
  printTitle("Reading file");
  try {
    Inventory readInv;
    readInv.readFromFile("inventory.csv");

    std::cout << "Read successfully" << '\n';

    readInv.displayInventory();
  } catch (const InventoryException& e) {
    std::cerr << "Error reading: " << e.what() << '\n';
  }

  printTitle("Writing to file");
  try {
    Inventory writeInv;
    writeInv.addItem(std::make_shared<Electronics>("E1", "Phone", 35, 399, 24));
    writeInv.addItem(std::make_shared<Electronics>("E2", "Laptop", 9, 690, 12));
    writeInv.addItem(
        std::make_shared<Electronics>("E3", "USB C", 120, 12, 128));
    writeInv.addItem(
        std::make_shared<Grocery>("G1", "Banana", 58, 2.95, "2026-12-14"));
    writeInv.addItem(
        std::make_shared<Grocery>("G2", "Dragon Fruit", 7, 2.95, "2026-12-14"));

    writeInv.writeToFile("test-out.csv");

    std::cout << "Writen sucesfully";
  } catch (const InventoryException& e) {
    std::cout << "Writing error: " << e.what() << '\n';
  }

  return 0;
}
