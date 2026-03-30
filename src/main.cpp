#include <iostream>
#include <memory>
#include <vector>

#include "Electronics.h"
#include "Grocery.h"

int main() {
  // Test display on derived classes
  std::vector<std::shared_ptr<Item>> items;
  items.push_back(
      std::make_shared<Grocery>("G1", "Apple", 15, 1.35, "2026-03-31"));
  items.push_back(std::make_shared<Electronics>("E1", "Phone", 1, 399.99, 24));

  for (const auto& item : items) {
    item->display();
  }

  return 0;
}
