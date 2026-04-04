#pragma once
#include <stdexcept>
#include <string>

// All exceptions derive from InventoryException so callers
// can catch everything with a single catch block
class InventoryException : public std::runtime_error {
 public:
  explicit InventoryException(const std::string& message)
      : std::runtime_error{message} {}
};

// Thrown when an operation is attempted on an empty inventory
class EmptyInventoryException : public InventoryException {
 public:
  EmptyInventoryException() : InventoryException{"Inventory is empty"} {}
};

// Thrown when item ID is not found in the inventory.
// Stores ID so callers can include it in error messages
class ItemNotFoundException : public InventoryException {
 private:
  std::string itemID;

 public:
  explicit ItemNotFoundException(const std::string& itemID)
      : InventoryException{"Item with ID \"" + itemID + "\" not found"},
        itemID{itemID} {}

  [[nodiscard]] const std::string& getItemID() const { return itemID; }
};

// Thrown when attempting to add item that ID already exists.
// Stores ID so callers can include it in error messages
class DuplicateItemException : public InventoryException {
 private:
  std::string itemID;

 public:
  explicit DuplicateItemException(const std::string& itemID)
      : InventoryException{"Item with ID \"" + itemID + "\" already exists"},
        itemID{itemID} {}

  [[nodiscard]] const std::string& getItemID() const { return itemID; }
};

// Thrown when a setter receives value that violates rules
// like negative price or quantity
class InvalidValueException : public InventoryException {
 public:
  explicit InvalidValueException(const std::string& message)
      : InventoryException{message} {}
};
