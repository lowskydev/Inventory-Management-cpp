#pragma once

#include <algorithm>
#include <memory>
#include <ranges>
#include <sstream>
#include <vector>

#include "Electronics.h"
#include "Grocery.h"
#include "Inventory.h"
#include "Item.h"

// Utility functions for the inventory system
namespace utils {

// Splits a string by the given delimiter and returns the tokens
inline std::vector<std::string> splitLine(const std::string& line,
                                          char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream stream{line};

  while (std::getline(stream, token, delimiter)) {
    tokens.push_back(token);
  }

  return tokens;
}

// -- Factory Functions --------------------------------------------------------
// Centralize item construction

inline std::shared_ptr<Item> makeElectronics(const std::string& itemID,
                                             const std::string& name,
                                             int quantity, double price,
                                             int warrantyMonths) {
  return std::make_shared<Electronics>(itemID, name, quantity, price,
                                       warrantyMonths);
}

inline std::shared_ptr<Item> makeGrocery(const std::string& itemID,
                                         const std::string& name, int quantity,
                                         double price,
                                         const std::string& expirationDate) {
  return std::make_shared<Grocery>(itemID, name, quantity, price,
                                   expirationDate);
}

// -- Generic Item Operation ---------------------------------------------------

// Returns a new vector containing only the items that satisfy pred.
// The original inventory is not modified.
// Example: filterItems(inv, [](const auto& i) { return i->getPrice() > 10; })
template <typename Predicate>
std::vector<std::shared_ptr<Item>> filterItems(const Inventory& inv,
                                               Predicate pred) {
  std::vector<std::shared_ptr<Item>> result;
  std::ranges::copy_if(inv.getItems(), std::back_inserter(result), pred);
  return result;
}

// Sorts the inventory in place using the given key function.
// Delegates to Inventory::sortBy which has direct access to the
// private items vector - avoids exposing mutable internal state.
// Example: sortItems(inv, [](const auto& i) { return i->getPrice(); })
template <typename Key>
void sortItems(Inventory& inv, Key keyFn) {
  inv.sortBy(keyFn);
}

}  // namespace utils
