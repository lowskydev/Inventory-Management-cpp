#include "Electronics.h"

#include <iostream>

Electronics::Electronics(std::string itemID, std::string name, int quantity,
                         double price, int warrantyMonths)
    : Item{std::move(itemID), std::move(name), quantity, price},
      warrantyMonths{warrantyMonths} {}

int Electronics::getWarrantyMonths() const { return warrantyMonths; }

void Electronics::setWarrantyMonths(int newWarrantyMonths) {
  if (newWarrantyMonths < MIN_WARRANTY_MONTHS) {
    std::cout << "Error: Item warranty (months) smaller than "
              << MIN_WARRANTY_MONTHS << "\n";
    return;
  }
  warrantyMonths = newWarrantyMonths;
}

std::string Electronics::category() const { return "Electronics"; }

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