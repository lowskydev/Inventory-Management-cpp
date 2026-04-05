#include "Item.h"

#include <iomanip>
#include <sstream>

#include "Exceptions.h"

Item::Item(std::string newItemID, std::string newName, int newQuantity,
           double newPrice)
    : itemID{std::move(newItemID)},
      name{std::move(newName)},
      quantity{0},
      price{0.0} {
  // Validation runs through setters rather than directly in the initializer
  // list so the rules applies when constructing
  setQuantity(newQuantity);
  setPrice(newPrice);
}

const std::string& Item::getItemID() const noexcept { return itemID; }
const std::string& Item::getName() const noexcept { return name; }
double Item::getPrice() const noexcept { return price; }
int Item::getQuantity() const noexcept { return quantity; }

void Item::setName(std::string newName) { name = std::move(newName); }
void Item::setQuantity(int newQuantity) {
  if (newQuantity < MIN_QUANTITY) {
    throw InvalidValueException("Item quantity smaller than " +
                                std::to_string(MIN_QUANTITY));
  }
  quantity = newQuantity;
}
void Item::setPrice(double newPrice) {
  if (newPrice < MIN_PRICE) {
    throw InvalidValueException("Item price smaller than " +
                                std::to_string(MIN_PRICE));
  }
  price = newPrice;
}

std::string Item::formatCommonFields() const {
  std::ostringstream oss;
  oss << std::left << std::setw(COL_CATEGORY) << ("[" + category() + "]")
      << " ID: " << std::setw(COL_ID) << itemID
      << " | Name: " << std::setw(COL_NAME) << name << " | Qty: " << std::right
      << std::setw(COL_QTY) << quantity << " | Price: " << std::setw(COL_PRICE)
      << std::fixed << std::setprecision(2) << price;
  return oss.str();
}

std::optional<std::string> Item::findAttribute(const std::string&) const {
  return std::nullopt;
}