#include "CLI.h"

#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "Exceptions.h"
#include "Utils.h"

struct MenuItem {
  std::string label;
  std::function<void(Inventory&)> handler;
};

static std::string getString(const std::string& prompt) {
  std::cout << prompt;

  std::string value;
  std::cin >> value;
  return value;
}

static int getInt(const std::string& prompt) {
  while (true) {
    std::cout << prompt;

    int value;
    if (std::cin >> value) return value;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Invalid input: please enter whole number\n";
  }
}

static double getDouble(const std::string& prompt) {
  while (true) {
    std::cout << prompt;

    double value;
    if (std::cin >> value) return value;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Invalid input: please enter number";
  }
}

static void handleAddElectronics(Inventory& inv) {
  try {
    const std::string itemID = getString("Item ID: ");
    const std::string name = getString("Name: ");
    const int quantity = getInt("Quantity: ");
    const double price = getDouble("Price: ");
    const int warrantyMonths = getInt("Warranty (months): ");
    inv.addItem(
        utils::makeElectronics(itemID, name, quantity, price, warrantyMonths));

    std::cout << "Electronics created successfully\n";
  } catch (const InventoryException& e) {
    std::cout << "Error: " << e.what() << '\n';
  }
}

static void handleAddGrocery(Inventory& inv) {
  try {
    const std::string itemID = getString("Item ID: ");
    const std::string name = getString("Name: ");
    const int quantity = getInt("Quantity: ");
    const double price = getDouble("Price: ");
    const std::string expirationDate =
        getString("Expiration date (YYYY-MM-DD): ");

    inv.addItem(
        utils::makeGrocery(itemID, name, quantity, price, expirationDate));

    std::cout << "Grocery created successfully\n";
  } catch (const InventoryException& e) {
    std::cout << "Error: " << e.what() << '\n';
  }
}

static void handleRemoveItem(Inventory& inv) {
  try {
    const std::string itemID = getString("Item ID: ");
    inv.removeItem(itemID);

    std::cout << "Item \"" << itemID << "\" removed successfully\n";
  } catch (const InventoryException& e) {
    std::cout << "Error: " << e.what() << '\n';
  }
}

static void handleUpdateQuantity(Inventory& inv) {
  try {
    const std::string itemID = getString("Item ID: ");
    const int quantity = getInt("Quantity: ");

    inv.updateQuantity(itemID, quantity);

    std::cout << "Quantity update to " << quantity << " successfully\n";
  } catch (const InventoryException& e) {
    std::cout << "Error: " << e.what() << '\n';
  }
}

static void handleDisplayInventory(Inventory& inv) {
  if (inv.getItems().empty()) {
    std::cout << "Inventory is empty\n";
    return;
  }

  inv.displayInventory();
}

static void handleReadFromFile(Inventory& inv) {
  try {
    const std::string filename = getString("Filename: ");

    inv.readFromFile(filename);

    std::cout << "Inventory loaded successfully\n";
  } catch (const InventoryException& e) {
    std::cout << "Error: " << e.what() << '\n';
  }
}

static void handleWriteToFile(Inventory& inv) {
  try {
    const std::string filename = getString("Filename: ");

    inv.writeToFile(filename);

    std::cout << "Inventory saved to \"" << filename << "\" successfully\n";
  } catch (const InventoryException& e) {
    std::cout << "Error: " << e.what() << '\n';
  }
}

static void handleFindMostExpensive(Inventory& inv) {
  try {
    const auto item = inv.findMostExpensive();
    item->display();
  } catch (const InventoryException& e) {
    std::cout << "Error: " << e.what() << '\n';
  }
}

static void handleBelowThreshold(Inventory& inv) {
  try {
    const int threshold = getInt("Threshold: ");

    const auto result = utils::filterItems(inv, [threshold](const auto& item) {
      return item->getQuantity() < threshold;
    });

    if (result.empty()) {
      std::cout << "No items below threshold of " << threshold << '\n';
    }

    for (const auto& item : result) {
      item->display();
    }
  } catch (const InventoryException& e) {
    std::cout << "Error: " << e.what() << '\n';
  }
}

static void handleSortByPrice(Inventory& inv) {
  utils::sortItems(inv, [](const auto& item) { return item->getPrice(); });
  inv.displayInventory();
}

static void printMenu(const std::vector<MenuItem>& menuItems) {
  std::cout << "\n=== Inventory System ===\n";

  for (size_t i = 0; i < menuItems.size(); i++) {
    std::cout << i + 1 << ". " << menuItems[i].label << '\n';
  }

  std::cout << "========================\n";
}

void runCLI(Inventory& inv) {
  const std::vector<MenuItem> menuItems{
      {"Add Electronics", handleAddElectronics},
      {"Add Grocery", handleAddGrocery},
      {"Remove Item", handleRemoveItem},
      {"Update Quantity", handleUpdateQuantity},
      {"Display Inventory", handleDisplayInventory},
      {"Read from File", handleReadFromFile},
      {"Write to File", handleWriteToFile},
      {"Find Most Expensive Item", handleFindMostExpensive},
      {"Find Items Below Quantity Threshold", handleBelowThreshold},
      {"Sort by Price", handleSortByPrice},
      {"Exit", nullptr},
  };

  while (true) {
    printMenu(menuItems);

    const int choice = getInt("Choice: ");

    if (choice < 1 || choice > static_cast<int>(menuItems.size())) {
      std::cout << "Invalid choice: range <1 - " << menuItems.size() << ">\n";
      continue;
    }

    const MenuItem& item = menuItems[static_cast<size_t>(choice - 1)];

    if (!item.handler) {
      std::cout << "Goodbye!\n";
      break;
    }

    item.handler(inv);
  }
}
