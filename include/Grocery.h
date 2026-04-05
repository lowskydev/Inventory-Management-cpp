#pragma once

#include <optional>
#include <string>
#include <string_view>

#include "Item.h"

// Represents a grocery product in the inventory.
// Extends Item with an expiration date
class Grocery : public Item {
 private:
  std::string expirationDate;

 public:
  static constexpr std::string_view DATE_FORMAT = "YYYY-MM-DD";

  // Validates that the date string is in DATE_FORMAT format.
  // Made public so the CLI can use it for input validation
  static bool isValidDate(const std::string& date);

  // Throws InvalidValueException if date fails format validation
  Grocery(std::string itemID, std::string name, int quantity, double price,
          std::string newExpirationDate);
  ~Grocery() override = default;

  // -- Getters ----------------------------------------------------------------

  [[nodiscard]] const std::string& getExpirationDate() const noexcept;

  // -- Setters ----------------------------------------------------------------

  // Throws InvalidValueException if date fails format validation
  void setExpirationDate(std::string newExpirationDate);

  // -- Virtual Functions ------------------------------------------------------

  void display() const override;

  [[nodiscard]] std::string category() const noexcept override;

  // Returns the expiration date string for CSV
  [[nodiscard]] std::string getExtraField() const override;

  // Supports "expiration" key
  [[nodiscard]] std::optional<std::string> findAttribute(
      const std::string& key) const override;
};