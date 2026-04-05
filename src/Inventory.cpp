#include "Inventory.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>

#include "Exceptions.h"
#include "Utils.h"

Inventory::Inventory(std::vector<std::shared_ptr<Item>> items)
    : items{std::move(items)} {}

const std::vector<std::shared_ptr<Item>>& Inventory::getItems() const {
  if (items.size() == 0) throw EmptyInventoryException();

  return items;
}

void Inventory::addItem(std::shared_ptr<Item> newItem) {
  const auto it = std::ranges::find_if(items, [&newItem](const auto& item) {
    return item->getItemID() == newItem->getItemID();
  });

  if (it != items.end()) {
    throw DuplicateItemException(newItem->getItemID());
  }

  items.push_back(std::move(newItem));
}

void Inventory::removeItem(const std::string& itemID) {
  // erase_if returns number of elements removed
  const auto removed = std::erase_if(items, [&itemID](const auto& item) {
    return item->getItemID() == itemID;
  });

  if (removed == 0) {
    throw ItemNotFoundException(itemID);
  }
}

void Inventory::updateQuantity(const std::string& itemID, int quantity) {
  const auto it = std::ranges::find_if(items, [&itemID](const auto& item) {
    return item->getItemID() == itemID;
  });

  if (it == items.end()) {
    throw ItemNotFoundException(itemID);
  }

  // setQuantity handles negative value validation
  (*it)->setQuantity(quantity);
}

void Inventory::displayInventory() const {
  if (items.empty()) throw EmptyInventoryException();

  for (const auto& item : items) {
    item->display();
  }
}

std::shared_ptr<Item> Inventory::findMostExpensive() const {
  const auto it =
      std::ranges::max_element(items, [](const auto& item1, const auto& item2) {
        return item1->getPrice() < item2->getPrice();
      });

  if (it == items.end()) {
    throw EmptyInventoryException();
  }

  return *it;
}

std::vector<std::shared_ptr<Item>> Inventory::belowQuantityThreshold(
    int threshold) const {
  std::vector<std::shared_ptr<Item>> result;

  std::ranges::copy_if(items, std::back_inserter(result),
                       [threshold](const auto& item) {
                         return item->getQuantity() < threshold;
                       });

  return result;
}

void Inventory::readFromFile(const std::string& filename) {
  std::ifstream inFile{filename};

  if (!inFile.is_open()) {
    throw InventoryException("Cannot open file \"" + filename +
                             "\" for reading");
  }

  std::string line;
  int lineNumber = 0;
  while (std::getline(inFile, line)) {
    ++lineNumber;
    if (line.empty()) continue;

    try {
      std::vector<std::string> fields = utils::splitLine(line, ',');

      // each line must have exactly 6 delimiter separated fields
      if (fields.size() != 6) {
        throw InventoryException("Invalid line " + std::to_string(lineNumber) +
                                 ": " + line);
      }

      const std::string& itemID = fields[0];
      const std::string& category = fields[1];
      const std::string& name = fields[2];
      int quantity = std::stoi(fields[3]);
      double price = std::stod(fields[4]);
      const std::string& extra = fields[5];

      if (category == "Electronics") {
        addItem(utils::makeElectronics(itemID, name, quantity, price,
                                       std::stoi(extra)));
      } else if (category == "Grocery") {
        addItem(utils::makeGrocery(itemID, name, quantity, price, extra));
      } else {
        throw InventoryException{"Unknown category: " + category};
      }

    } catch (const InventoryException&) {
      // rethrow inventory errors - they already have clear messages
      throw;
    } catch (const std::exception& e) {
      throw InventoryException{"Failed to parse line " +
                               std::to_string(lineNumber) + ": " + e.what()};
    }
  }
}

void Inventory::writeToFile(const std::string& filename) const {
  std::ofstream outFile{filename};

  if (!outFile.is_open()) {
    throw InventoryException("Cannot open file \"" + filename +
                             "\" for writing");
  }

  // fix decimal places so prices round correctly in CSV
  outFile << std::fixed << std::setprecision(2);

  for (const auto& item : items) {
    // format: itemID,category,name,quantity,price,extra
    outFile << item->getItemID() << FILE_OUT_DELIMITER << item->category()
            << FILE_OUT_DELIMITER << item->getName() << FILE_OUT_DELIMITER
            << item->getQuantity() << FILE_OUT_DELIMITER << item->getPrice()
            << FILE_OUT_DELIMITER << item->getExtraField() << '\n';
  }
}