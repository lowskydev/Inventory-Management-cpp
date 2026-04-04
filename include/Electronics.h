#pragma once

#include <optional>
#include <string>

#include "Item.h"

// Represents an electronic product in the inventory.
// Extends Item with a warranty duration in months
class Electronics : public Item {
 private:
  int warrantyMonths;

 public:
  static constexpr int MIN_WARRANTY_MONTHS = 0;

  // Throws InvalidValueException if any value violates its minimum
  Electronics(std::string itemID, std::string name, int quantity, double price,
              int warrantyMonths);
  ~Electronics() override = default;

  // -- Getters ----------------------------------------------------------------

  [[nodiscard]] int getWarrantyMonths() const noexcept;

  // -- Setters ----------------------------------------------------------------

  // Throws InvalidValueException if warrantyMonths < MIN_WARRANTY_MONTHS
  void setWarrantyMonths(int newWarrantyMonths);

  // -- Virtual Functions ------------------------------------------------------

  void display() const override;

  [[nodiscard]] std::string category() const noexcept override;

  // Returns warrantyMonths as a string for CSV
  [[nodiscard]] std::string getExtraField() const override;

  // Supports "warranty" key
  [[nodiscard]] std::optional<std::string> findAttribute(
      const std::string& key) const override;
};