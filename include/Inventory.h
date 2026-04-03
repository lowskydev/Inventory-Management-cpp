#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "Item.h"

class Inventory {
 private:
  static constexpr char FILE_OUT_DELIMITER = ',';

  std::vector<std::shared_ptr<Item>> items;

 public:
  Inventory() = default;
  explicit Inventory(std::vector<std::shared_ptr<Item>> items);

  Inventory(const Inventory&) = delete;
  Inventory& operator=(const Inventory&) = delete;

  Inventory(Inventory&&) noexcept = default;
  Inventory& operator=(Inventory&&) noexcept = default;

  [[nodiscard]] const std::vector<std::shared_ptr<Item>>& getItems()
      const noexcept;

  void addItem(std::shared_ptr<Item> newItem);

  void removeItem(const std::string& itemID);
  void updateQuantity(const std::string& itemID, int quantity);
  void displayInventory() const;

  [[nodiscard]] std::shared_ptr<Item> findMostExpensive() const;

  [[nodiscard]] std::vector<std::shared_ptr<Item>> belowQuantityThreshold(
      int threshold) const;

  void readFromFile(const std::string& filename);
  void writeToFile(const std::string& filename) const;

  template <typename Key>
  void sortBy(Key keyFn) {
    std::ranges::sort(items, [&keyFn](const auto& item1, const auto& item2) {
      return keyFn(item1) < keyFn(item2);
    });
  }
};
