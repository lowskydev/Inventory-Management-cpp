#include "Electronics.h"

#include <iostream>

#include "Exceptions.h"

Electronics::Electronics(std::string newItemID, std::string newName,
                         int newQuantity, double newPrice,
                         int newWarrantyMonths)
    : Item{std::move(newItemID), std::move(newName), newQuantity, newPrice},
      warrantyMonths{0} {
  // set via setter so validation runs at construction
  // time with the same rules as updates
  setWarrantyMonths(newWarrantyMonths);
}

int Electronics::getWarrantyMonths() const noexcept { return warrantyMonths; }

void Electronics::setWarrantyMonths(int newWarrantyMonths) {
  if (newWarrantyMonths < MIN_WARRANTY_MONTHS) {
    throw InvalidValueException("Item warranty (months) smaller than " +
                                std::to_string(MIN_WARRANTY_MONTHS));
  }
  warrantyMonths = newWarrantyMonths;
}

std::string Electronics::category() const noexcept { return "Electronics"; }

std::string Electronics::getExtraField() const {
  return std::to_string(warrantyMonths);
}

void Electronics::display() const {
  std::cout << formatCommonFields() << " | Warranty: " << warrantyMonths
            << " months\n";
}

std::optional<std::string> Electronics::findAttribute(
    const std::string& key) const {
  if (key == "warranty") {
    return std::to_string(warrantyMonths) + " months";
  }

  return std::nullopt;
}