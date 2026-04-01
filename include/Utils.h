#pragma once

#include <algorithm>
#include <memory>
#include <ranges>
#include <vector>

#include "Inventory.h"
#include "Item.h"

namespace utils {

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
