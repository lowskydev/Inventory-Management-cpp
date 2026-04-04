#pragma once

#include <optional>
#include <string>

// Abstract base class for all inventory items.
// Cannot be instantiated directly - use derived classes like Electronics
class Item {
 private:
  std::string itemID;
  std::string name;
  int quantity;
  double price;

  // Column widths for aligned display output
  static constexpr int COL_CATEGORY = 14;
  static constexpr int COL_ID = 5;
  static constexpr int COL_NAME = 12;
  static constexpr int COL_QTY = 6;
  static constexpr int COL_PRICE = 8;

 protected:
  // Formats the fields common to all item types into display string.
  // Used by derived classes to make display() easier
  [[nodiscard]] std::string formatCommonFields() const;

 public:
  static constexpr int MIN_QUANTITY = 0;
  static constexpr double MIN_PRICE = 0.0;

  Item(std::string itemID, std::string name, int quantity, double price);
  virtual ~Item() = default;

  // -- Getters ----------------------------------------------------------------

  [[nodiscard]] const std::string& getItemID() const noexcept;
  [[nodiscard]] const std::string& getName() const noexcept;
  [[nodiscard]] int getQuantity() const noexcept;
  [[nodiscard]] double getPrice() const noexcept;

  // -- Setters ----------------------------------------------------------------

  // Throws InvalidValueException if quantity < MIN_QUANTITY
  void setQuantity(int newQuantity);

  // Throws InvalidValueException if price < MIN_PRICE
  void setPrice(double newPrice);

  void setName(std::string newName);

  // -- Virtual Functions ------------------------------------------------------

  // Prints a formatted item info to stdout
  virtual void display() const = 0;

  // Returns the category name
  [[nodiscard]] virtual std::string category() const noexcept = 0;

  // Returns specific to derived class extra field as a
  // string for CSV
  [[nodiscard]] virtual std::string getExtraField() const = 0;

  // Returns attribute specific to the derived class.
  // Base implementation returns nullopt
  [[nodiscard]] virtual std::optional<std::string> findAttribute(
      const std::string& key) const;
};