#include "Item.h"

#include <iostream>

Item::Item(std::string itemID, std::string name, int quantity, double price)
    : itemID{std::move(itemID)},
      name{std::move(name)},
      quantity{quantity},
      price{price} {}

std::string Item::getItemID() const { return itemID; }
std::string Item::getName() const { return name; }
double Item::getPrice() const { return price; }
int Item::getQuantity() const { return quantity; }

void Item::setName(std::string newName) { name = std::move(newName); }
void Item::setQuantity(int newQuantity) {
  if (newQuantity < MIN_QUANTITY) {
    std::cout << "Error: Item quantity smaller than " << MIN_QUANTITY << "\n";
    return;
  }
  quantity = newQuantity;
}
void Item::setPrice(double newPrice) {
  if (newPrice < MIN_PRICE) {
    std::cout << "Error: Item price smaller than " << MIN_PRICE << "\n";
    return;
  }
  price = newPrice;
}

std::optional<std::string> Item::findAttribute(const std::string&) const {
  return std::nullopt;
}