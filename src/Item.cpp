#include "Item.h"

#include "Exceptions.h"

Item::Item(std::string itemID, std::string name, int quantity, double price)
    : itemID{std::move(itemID)},
      name{std::move(name)},
      quantity{quantity},
      price{price} {}

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

std::optional<std::string> Item::findAttribute(const std::string&) const {
  return std::nullopt;
}