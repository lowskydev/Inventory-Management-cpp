#include <gtest/gtest.h>

#include <fstream>

#include "Exceptions.h"
#include "Inventory.h"
#include "Utils.h"

class FileIOTest : public testing::Test {
 protected:
  const std::string testFilename = "test_inventory_temp.csv";

  Inventory inv;

  void SetUp() override {
    inv.addItem(utils::makeElectronics("E1", "Phone", 10, 699.99, 24));
    inv.addItem(utils::makeElectronics("E2", "Laptop", 5, 1099.99, 12));
    inv.addItem(utils::makeGrocery("G1", "Apple", 100, 0.99, "2026-06-01"));
    inv.addItem(utils::makeGrocery("G2", "Milk", 30, 1.49, "2026-04-10"));
  };

  void TearDown() override { std::remove(testFilename.c_str()); };
};

// -- writeToFile --------------------------------------------------------------

TEST_F(FileIOTest, WriteToFileCreatesFile) {
  EXPECT_NO_THROW(inv.writeToFile(testFilename));

  std::ifstream file{testFilename};

  // verify file actually exists
  EXPECT_TRUE(file.is_open());
  // verify file is not empty
  EXPECT_NE(file.peek(), std::ifstream::traits_type::eof());
}

TEST_F(FileIOTest, WriteToFileThrowsOnInvalidPath) {
  EXPECT_THROW(inv.writeToFile("/nonexistent/path/inventory.csv"),
               InventoryException);
}

// -- readFromFile -------------------------------------------------------------

TEST_F(FileIOTest, ReadFromFileLoadsCorrectNumberOfItems) {
  inv.writeToFile(testFilename);

  Inventory loaded;
  EXPECT_NO_THROW(loaded.readFromFile(testFilename));

  EXPECT_EQ(loaded.getItems().size(), 4);
}

TEST_F(FileIOTest, ReadFromFileLoadsCorrectItemData) {
  inv.writeToFile(testFilename);
  Inventory loaded;
  loaded.readFromFile(testFilename);

  const auto& items = loaded.getItems();
  const auto it = std::ranges::find_if(
      items, [](const auto& item) { return item->getItemID() == "E1"; });

  ASSERT_NE(it, items.end());

  ASSERT_EQ((*it)->getItemID(), "E1");
  ASSERT_EQ((*it)->getName(), "Phone");
  ASSERT_EQ((*it)->getQuantity(), 10);
  ASSERT_DOUBLE_EQ((*it)->getPrice(), 699.99);
  ASSERT_EQ((*it)->category(), "Electronics");
}

// -- Read-Write Cycle ---------------------------------------------------------

TEST_F(FileIOTest, WriteReadCyclePreservesAllItems) {
  inv.writeToFile(testFilename);

  Inventory loaded;
  loaded.readFromFile(testFilename);

  // same number of items
  EXPECT_EQ(loaded.getItems().size(), inv.getItems().size());

  // every item ID from original exists in loaded
  for (const auto& original : inv.getItems()) {
    const auto it =
        std::ranges::find_if(loaded.getItems(), [&original](const auto& item) {
          return item->getItemID() == original->getItemID();
        });

    EXPECT_NE(it, loaded.getItems().end())
        << "Item \"" << original->getItemID()
        << "\" missing after read-write cycle";
  }
}
TEST_F(FileIOTest, WriteReadCyclePreservesItemData) {
  inv.writeToFile(testFilename);

  Inventory loaded;
  loaded.readFromFile(testFilename);

  // verify every item's data survived read-write cycle
  for (const auto& original : inv.getItems()) {
    const auto it =
        std::ranges::find_if(loaded.getItems(), [&original](const auto& item) {
          return item->getItemID() == original->getItemID();
        });

    ASSERT_NE(it, loaded.getItems().end());

    EXPECT_EQ((*it)->getName(), original->getName());
    EXPECT_EQ((*it)->getQuantity(), original->getQuantity());
    EXPECT_DOUBLE_EQ((*it)->getPrice(), original->getPrice());
    EXPECT_EQ((*it)->category(), original->category());
    EXPECT_EQ((*it)->getExtraField(), original->getExtraField());
  }
}

// -- Edge Cases ---------------------------------------------------------------

TEST_F(FileIOTest, ReadFromFileHandlesEmptyFile) {
  // create empty file
  std::ofstream{testFilename};
  Inventory emptyInv;

  EXPECT_NO_THROW(emptyInv.readFromFile(testFilename));
  EXPECT_EQ(emptyInv.getItems().size(), 0);
}

TEST_F(FileIOTest, WriteAndReadEmptyInventory) {
  Inventory emptyInv;
  EXPECT_NO_THROW(emptyInv.writeToFile(testFilename));

  Inventory loaded;
  EXPECT_NO_THROW(loaded.readFromFile(testFilename));
  EXPECT_TRUE(loaded.getItems().empty());
}