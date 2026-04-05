#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "Item.h"

// Manages a collection of inventory items.
// Owns its items - copying is disabled to prevent two inventories
// from sharing and changing the same item objects
class Inventory {
 private:
  // Delimiter used when serializing items
  static constexpr char FILE_OUT_DELIMITER = ',';

  std::vector<std::shared_ptr<Item>> items;

 public:
  Inventory() = default;
  explicit Inventory(std::vector<std::shared_ptr<Item>> items);

  // -- Copy & Move ------------------------------------------------------------

  // Copying is disabled - two inventories sharing the same item objects

  Inventory(const Inventory&) = delete;
  Inventory& operator=(const Inventory&) = delete;

  // Moving transfers full ownership of all items

  Inventory(Inventory&&) noexcept = default;
  Inventory& operator=(Inventory&&) noexcept = default;

  // -- Item Management --------------------------------------------------------

  // Throws DuplicateItemException if item with the same ID exists
  void addItem(std::shared_ptr<Item> newItem);

  // Throws ItemNotFoundException if no item with the given ID exists
  void removeItem(const std::string& itemID);

  // Throws ItemNotFoundException if no item with the given ID exists.
  // Throws InvalidValueException if quantity is negative
  void updateQuantity(const std::string& itemID, int quantity);

  void displayInventory() const;

  // -- Search & Utility -------------------------------------------------------

  // Throws EmptyInventoryException if the inventory has no items
  [[nodiscard]] std::shared_ptr<Item> findMostExpensive() const;

  [[nodiscard]] std::vector<std::shared_ptr<Item>> belowQuantityThreshold(
      int threshold) const;

  // Returns a const reference to the internal item list.
  // Used by functions in Utils.h
  [[nodiscard]] const std::vector<std::shared_ptr<Item>>& getItems() const;

  // -- File I/O ---------------------------------------------------------------

  // Throws InventoryException if the file cannot be read
  void readFromFile(const std::string& filename);

  // Throws InventoryException if the file cannot be written
  void writeToFile(const std::string& filename) const;

  // -- Templates --------------------------------------------------------------

  // Sorts items in place using given key function.
  // keyFn should take shared_ptr<Item> and return result that is comparable.
  // Example: sortBy([](const auto& item) { return item->getPrice(); })
  template <typename Key>
  void sortBy(Key keyFn) {
    std::ranges::sort(items, [&keyFn](const auto& item1, const auto& item2) {
      return keyFn(item1) < keyFn(item2);
    });
  }
};
