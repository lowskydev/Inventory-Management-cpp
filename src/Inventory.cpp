#include "Inventory.h"

#include <algorithm>
#include <iostream>
#include <ranges>

Inventory::Inventory(std::vector<std::shared_ptr<Item>> items)
    : items{std::move(items)} {}

void Inventory::addItem(std::shared_ptr<Item> newItem) {
  const auto it = std::ranges::find_if(items, [&newItem](const auto& item) {
    return item->getItemID() == newItem->getItemID();
  });

  if (it != items.end()) {
    std::cout << "Error: item with itemID of \"" << newItem->getItemID()
              << "\" already exists\n";
    return;
  }

  items.push_back(std::move(newItem));
}

void Inventory::removeItem(const std::string& itemID) {
  const auto removed = std::erase_if(items, [&itemID](const auto& item) {
    return item->getItemID() == itemID;
  });

  if (removed == 0) {
    std::cout << "Error: item with ID \"" << itemID << "\" not found\n";
  }
}

void Inventory::updateQuantity(const std::string& itemID, int quantity) {
  const auto it = std::ranges::find_if(items, [&itemID](const auto& item) {
    return item->getItemID() == itemID;
  });

  if (it == items.end()) {
    std::cout << "Error: could not find ID \"" << itemID
              << "\" in the inventory\n";
    return;
  }

  (*it)->setQuantity(quantity);
}

void Inventory::displayInventory() const {
  for (const auto& item : items) {
    item->display();
  }
}

std::shared_ptr<Item> Inventory::findMostExpensive() const {
  const auto it =
      std::ranges::max_element(items, [](const auto& item1, const auto& item2) {
        return item1->getPrice() < item2->getPrice();
      });

  if (it == items.end()) {
    std::cout << "Error: inventory is empty\n";
    return nullptr;
  }

  return *it;
}

std::vector<std::shared_ptr<Item>> Inventory::belowQuantityThreshold(
    int threshold) const {
  std::vector<std::shared_ptr<Item>> result;

  std::ranges::copy_if(items, std::back_inserter(result),
                       [threshold](const auto& item) {
                         return item->getQuantity() < threshold;
                       });

  return result;
}