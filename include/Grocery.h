#pragma once

#include <optional>
#include <string>
#include <string_view>

#include "Item.h"

class Grocery : public Item {
 private:
  std::string expirationDate;

  static bool isValidDate(const std::string& date);

 public:
  static constexpr std::string_view DATE_FORMAT = "YYYY-MM-DD";

  Grocery(std::string itemID, std::string name, int quantity, double price,
          std::string expirationDate);
  ~Grocery() override = default;

  [[nodiscard]] const std::string& getExpirationDate() const noexcept;
  void setExpirationDate(std::string newExpirationDate);
  void display() const override;

  [[nodiscard]] std::string category() const noexcept override;

  [[nodiscard]] std::string getExtraField() const override;

  [[nodiscard]] std::optional<std::string> findAttribute(
      const std::string& key) const override;
};