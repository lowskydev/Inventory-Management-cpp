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

namespace utils {

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

template <typename Predicate>
std::vector<std::shared_ptr<Item>> filterItems(const Inventory& inv,
                                               Predicate pred) {
  std::vector<std::shared_ptr<Item>> result;
  std::ranges::copy_if(inv.getItems(), std::back_inserter(result), pred);
  return result;
}

template <typename Key>
void sortItems(Inventory& inv, Key keyFn) {
  inv.sortBy(keyFn);
}

}  // namespace utils
