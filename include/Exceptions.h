#pragma once
#include <stdexcept>
#include <string>

class InventoryException : public std::runtime_error {
 public:
  explicit InventoryException(const std::string& message)
      : std::runtime_error{message} {}
};

class ItemNotFoundException : public InventoryException {
 private:
  std::string itemID;

 public:
  explicit ItemNotFoundException(const std::string& itemID)
      : InventoryException{"Item with ID \"" + itemID + "\" not found"},
        itemID{itemID} {}

  [[nodiscard]] const std::string& getItemID() const { return itemID; }
};

class DuplicateItemException : public InventoryException {
 private:
  std::string itemID;

 public:
  explicit DuplicateItemException(const std::string& itemID)
      : InventoryException{"Item with ID \"" + itemID + "\" already exists"},
        itemID{itemID} {}

  [[nodiscard]] const std::string& getItemID() const { return itemID; }
};

class InvalidValueException : public InventoryException {
 public:
  explicit InvalidValueException(const std::string& message)
      : InventoryException{message} {}
};
