#include "Grocery.h"

#include <iostream>
#include <string>

#include "Exceptions.h"

Grocery::Grocery(std::string itemID, std::string name, int quantity,
                 double price, std::string expirationDate)
    : Item{std::move(itemID), std::move(name), quantity, price},
      expirationDate{""} {
  setExpirationDate(std::move(expirationDate));
}

bool Grocery::isValidDate(const std::string& date) {
  // check length
  if (date.length() != 10) return false;

  // check dashes
  if (date[4] != '-' || date[7] != '-') return false;

  // check if chars are digits
  for (size_t i = 0; i < 10; i++) {
    if (i == 4 || i == 7) continue;
    if (!std::isdigit(date[i])) return false;
  }

  // check ranges
  const int year = std::stoi(date.substr(0, 4));
  const int month = std::stoi(date.substr(5, 2));
  const int day = std::stoi(date.substr(8, 2));

  if (year < 1900 || year > 9999) return false;
  if (month < 1 || month > 12) return false;
  if (day < 1 || day > 31) return false;

  return true;
}

const std::string& Grocery::getExpirationDate() const noexcept {
  return expirationDate;
}

void Grocery::setExpirationDate(std::string newExpirationDate) {
  if (!isValidDate(newExpirationDate)) {
    throw InvalidValueException("Item date format is wrong (expected " +
                                std::string{DATE_FORMAT} + ")");
  }

  expirationDate = std::move(newExpirationDate);
}

std::string Grocery::category() const noexcept { return "Grocery"; }

void Grocery::display() const {
  std::cout << "[" << category() << "] ID: " << getItemID()
            << " | Name: " << getName() << " | Qty: " << getQuantity()
            << " | Price: " << getPrice() << " | Expires: " << expirationDate
            << "\n";
}

std::optional<std::string> Grocery::findAttribute(
    const std::string& key) const {
  if (key == "expiration") {
    return expirationDate;
  }
  return std::nullopt;
}