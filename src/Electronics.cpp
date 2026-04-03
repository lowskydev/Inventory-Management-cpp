#include "Electronics.h"

#include <iostream>

#include "Exceptions.h"

Electronics::Electronics(std::string itemID, std::string name, int quantity,
                         double price, int warrantyMonths)
    : Item{std::move(itemID), std::move(name), quantity, price},
      warrantyMonths{0} {
  setWarrantyMonths(warrantyMonths);
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
  std::cout << "[" << category() << "] ID: " << getItemID()
            << " | Name: " << getName() << " | Qty: " << getQuantity()
            << " | Price: " << getPrice() << " | Warranty: " << warrantyMonths
            << " months\n";
}

std::optional<std::string> Electronics::findAttribute(
    const std::string& key) const {
  if (key == "warranty") {
    return std::to_string(warrantyMonths) + " months";
  }

  return std::nullopt;
}