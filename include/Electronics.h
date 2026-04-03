#pragma once

#include <optional>
#include <string>

#include "Item.h"

class Electronics : public Item {
 private:
  int warrantyMonths;

 public:
  static constexpr int MIN_WARRANTY_MONTHS = 0;

  Electronics(std::string itemID, std::string name, int quantity, double price,
              int warrantyMonths);
  ~Electronics() override = default;

  [[nodiscard]] int getWarrantyMonths() const noexcept;

  void setWarrantyMonths(int newWarrantyMonths);
  void display() const override;

  [[nodiscard]] std::string category() const noexcept override;

  [[nodiscard]] std::string getExtraField() const override;

  [[nodiscard]] std::optional<std::string> findAttribute(
      const std::string& key) const override;
};