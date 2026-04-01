#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Item.h"

class Inventory {
 private:
  std::vector<std::shared_ptr<Item>> items;

 public:
  Inventory() = default;
  explicit Inventory(std::vector<std::shared_ptr<Item>> items);

  Inventory(const Inventory&) = delete;
  Inventory& operator=(const Inventory&) = delete;

  Inventory(Inventory&&) = default;
  Inventory& operator=(Inventory&&) = default;

  [[nodiscard]] const std::vector<std::shared_ptr<Item>>& getItems() const;

  void addItem(std::shared_ptr<Item> newItem);

  void removeItem(const std::string& itemID);
  void updateQuantity(const std::string& itemID, int quantity);
  void displayInventory() const;

  [[nodiscard]] std::shared_ptr<Item> findMostExpensive() const;

  [[nodiscard]] std::vector<std::shared_ptr<Item>> belowQuantityThreshold(
      int threshold) const;
};
