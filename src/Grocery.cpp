#include "Grocery.h"

#include <iostream>
#include <string>

#include "Exceptions.h"

Grocery::Grocery(std::string newItemID, std::string newName, int newQuantity,
                 double newPrice, std::string newExpirationDate)
    : Item{std::move(newItemID), std::move(newName), newQuantity, newPrice},
      expirationDate{""} {
  // set via setter so validation runs at construction
  // time with the same rules as updates
  setExpirationDate(std::move(newExpirationDate));
}

// Structure must be exactly as defined in DATE_FORMAT (eg "YYYY-MM-DD")
bool Grocery::isValidDate(const std::string& date) {
  // check length
  if (date.length() != 10) return false;

  // check dashes
  if (date[4] != '-' || date[7] != '-') return false;

  // every character except the dashes must be a digit
  for (size_t i = 0; i < 10; i++) {
    if (i == 4 || i == 7) continue;
    if (!std::isdigit(date[i])) return false;
  }

  const int year = std::stoi(date.substr(0, 4));
  const int month = std::stoi(date.substr(5, 2));
  const int day = std::stoi(date.substr(8, 2));

  // check ranges
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
  std::cout << formatCommonFields() << " | Expires: " << expirationDate << '\n';
}

std::string Grocery::getExtraField() const { return expirationDate; }

std::optional<std::string> Grocery::findAttribute(
    const std::string& key) const {
  if (key == "expiration") {
    return expirationDate;
  }
  return std::nullopt;
}