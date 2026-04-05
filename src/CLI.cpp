#include "CLI.h"

#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <string>

#include "Exceptions.h"
#include "Utils.h"

// -- Data Structures ----------------------------------------------------------

struct MenuItem {
  std::string label;
  std::function<void(Inventory&)> handler;
};

// Groups the four fields shared by Item.
// Used by getCommonItems
struct ItemFields {
  std::string itemID;
  std::string name;
  int quantity;
  double price;
};

// -- Input Helpers ----------------------------------------------------------

// Reads non-empty string from stdin.
// Trims leading and trailing whitespace.
// Re-prompts if the input is blank or whitespace only
static std::string getString(const std::string& prompt) {
  while (true) {
    std::cout << prompt;
    std::string value;

    // cin >> used by getInt/getDouble leaves '\n' in the buffer.
    // this removes it
    if (std::cin.peek() == '\n') {
      std::cin.ignore();
    }

    std::getline(std::cin, value);

    // find the first and last non-whitespace characters
    const auto start = value.find_first_not_of(" \t");
    const auto end = value.find_last_not_of(" \t");

    if (start == std::string::npos) {
      std::cout << "Invalid input: cannot be empty\n";
      continue;
    }

    // return the trimmed substring
    return value.substr(start, end - start + 1);
  }
}

// Reads whole number from stdin.
// Rejects floats, letters, and symbols by checking each character.
// Re-prompts on invalid input
static int getInt(const std::string& prompt) {
  while (true) {
    std::cout << prompt;
    std::string input;
    std::cin >> input;

    // reject anything that isn't purely digits
    const bool isWholeNumber = std::ranges::all_of(
        input, [](const char character) { return std::isdigit(character); });

    if (input.empty() || !isWholeNumber) {
      std::cout << "Invalid input: please enter whole number\n";
      continue;
      ;
    }

    return std::stoi(input);
  }
}

// Reads non-negative whole number from stdin.
// Re-prompts if the value is negative
static int getPositiveInt(const std::string& prompt) {
  while (true) {
    const int value = getInt(prompt);
    if (value >= 0) return value;
    std::cout << "Invalid input: please enter positive whole number\n";
  }
}

// Reads a decimal number from stdin.
// Re-prompts on invalid input
static double getDouble(const std::string& prompt) {
  while (true) {
    std::cout << prompt;

    double value;
    if (std::cin >> value) return value;

    // clear the error flag and discard the bad input
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Invalid input: please enter number\n";
  }
}
// Reads positive decimal number from stdin.
// Re-prompts on invalid input
static double getPositiveDouble(const std::string& prompt) {
  while (true) {
    const double value = getDouble(prompt);
    if (value >= 0) return value;
    std::cout << "Invalid input: please enter positive number\n";
  }
}

// Reads a date string from stdin
// Validates YYYY-MM-DD format by Grocery::isValidDate.
// Re-prompting until the input matches
static std::string getDate(const std::string& prompt) {
  while (true) {
    std::cout << prompt;
    std::string value;
    std::cin >> value;

    if (Grocery::isValidDate(value)) return value;

    std::cout << "Invalid date: expected " << Grocery::DATE_FORMAT << '\n';
  }
}

// Prompts for the four fields common to all item types.
// Used by handleAdd[Derived Item Class] to avoid repetition
static ItemFields getCommonItems() {
  return {
      getString("Item ID: "),
      getString("Name: "),
      getPositiveInt("Quantity: "),
      getPositiveDouble("Price: "),
  };
}

// -- Menu Handlers ----------------------------------------------------------

static void handleAddElectronics(Inventory& inv) {
  try {
    const auto [itemID, name, quantity, price] = getCommonItems();
    const int warrantyMonths = getPositiveInt("Warranty (months): ");
    inv.addItem(
        utils::makeElectronics(itemID, name, quantity, price, warrantyMonths));

    std::cout << "Electronics created successfully\n";
  } catch (const InventoryException& e) {
    std::cout << "Error: " << e.what() << '\n';
  }
}

static void handleAddGrocery(Inventory& inv) {
  try {
    const auto [itemID, name, quantity, price] = getCommonItems();
    const std::string expirationDate = getDate(
        "Expiration date (" + std::string{Grocery::DATE_FORMAT} + "): ");

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
    const int quantity = getPositiveInt("Quantity: ");

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
    const int threshold = getPositiveInt("Threshold: ");

    const auto result = utils::filterItems(inv, [threshold](const auto& item) {
      return item->getQuantity() < threshold;
    });

    if (result.empty()) {
      std::cout << "No items below threshold of " << threshold << '\n';
      return;
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

// -- Menu Display ----------------------------------------------------------

static void printMenu(const std::vector<MenuItem>& menuItems) {
  std::cout << "\n=== Inventory System ===\n";

  for (size_t i = 0; i < menuItems.size(); i++) {
    const size_t number = i + 1;
    std::cout << std::setw(2) << number << ". " << menuItems[i].label << '\n';
  }

  std::cout << "========================\n";
}

// -- Entry Point  ----------------------------------------------------------

void runCLI(Inventory& inv) {
  // menu items are stored in a vector.
  // their position determines the number shown to the user
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

    // nullptr handler signals the Exit option
    if (!item.handler) {
      std::cout << "Goodbye!\n";
      break;
    }

    item.handler(inv);
  }
}
