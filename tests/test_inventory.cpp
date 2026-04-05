#include <gtest/gtest.h>

#include "Exceptions.h"
#include "Inventory.h"
#include "Utils.h"

class InventoryTest : public testing::Test {
 protected:
  Inventory inv;
  void SetUp() override {
    inv.addItem(utils::makeElectronics("E1", "Phone", 10, 699.99, 24));
    inv.addItem(utils::makeElectronics("E2", "Laptop", 5, 1099.99, 12));
    inv.addItem(utils::makeGrocery("G1", "Apple", 100, 0.99, "2026-06-01"));
    inv.addItem(utils::makeGrocery("G2", "Milk", 30, 1.49, "2026-04-10"));
  }
};

// -- addItem ------------------------------------------------------------------

TEST_F(InventoryTest, AddItemIncreasesSize) {
  EXPECT_EQ(inv.getItems().size(), 4);
  inv.addItem(utils::makeElectronics("E3", "Tablet", 3, 499.99, 12));
  EXPECT_EQ(inv.getItems().size(), 5);
}

TEST_F(InventoryTest, AddItemStoresCorrectData) {
  inv.addItem(utils::makeElectronics("E3", "Tablet", 3, 499.99, 12));

  const auto& items = inv.getItems();

  const auto it = std::ranges::find_if(
      items, [](const auto& item) { return item->getItemID() == "E3"; });

  ASSERT_NE(it, items.end());

  EXPECT_EQ((*it)->getItemID(), "E3");
  EXPECT_EQ((*it)->getName(), "Tablet");
  EXPECT_EQ((*it)->getQuantity(), 3);
  EXPECT_DOUBLE_EQ((*it)->getPrice(), 499.99);
  EXPECT_EQ((*it)->category(), "Electronics");
}

TEST_F(InventoryTest, AddItemThrowsOnDuplicateID) {
  EXPECT_THROW(
      inv.addItem(utils::makeElectronics("E2", "Tablet", 3, 499.99, 24)),
      DuplicateItemException);
}

TEST_F(InventoryTest, AddItemDoesNotModifyInventoryOnDuplicate) {
  // strong exception safety - inventory unchanged after failed add
  try {
    inv.addItem(utils::makeElectronics("E1", "Phone", 10, 699.99, 24));
  } catch (const DuplicateItemException&) {
  }

  EXPECT_EQ(inv.getItems().size(), 4);
}

// -- removeItem ---------------------------------------------------------------

TEST_F(InventoryTest, RemoveItemDecreasesSize) {
  EXPECT_NO_THROW(inv.removeItem("E1"));
  EXPECT_EQ(inv.getItems().size(), 3);
}

TEST_F(InventoryTest, RemoveItemThrowsOnInvalidID) {
  EXPECT_THROW(inv.removeItem("E6"), ItemNotFoundException);
}

TEST_F(InventoryTest, RemoveItemRemovesCorrectItem) {
  inv.removeItem("E1");

  // E1 should no longer exist
  EXPECT_THROW(inv.removeItem("E1"), ItemNotFoundException);
}

// -- updateQuantity -----------------------------------------------------------

TEST_F(InventoryTest, UpdateQuantitySucceeds) {
  EXPECT_NO_THROW(inv.updateQuantity("E1", 50));

  const auto& items = inv.getItems();
  const auto it = std::ranges::find_if(
      items, [](const auto& item) { return item->getItemID() == "E1"; });

  EXPECT_NE(it, items.end());
  EXPECT_EQ((*it)->getQuantity(), 50);
}

TEST_F(InventoryTest, UpdateQuantityThrowsOnMissingID) {
  EXPECT_THROW(inv.updateQuantity("X99", 10), ItemNotFoundException);
}

TEST_F(InventoryTest, UpdateQuantityThrowsOnNegativeQuantity) {
  EXPECT_THROW(inv.updateQuantity("E1", -1), InvalidValueException);
}

TEST_F(InventoryTest, UpdateQuantityAcceptsZero) {
  EXPECT_NO_THROW(inv.updateQuantity("E1", 0));
}

// -- displayInventory ---------------------------------------------------------

TEST_F(InventoryTest, DisplayInventoryDoesNotThrow) {
  EXPECT_NO_THROW(inv.displayInventory());
}

// -- findMostExpensive --------------------------------------------------------

TEST_F(InventoryTest, FindMostExpensiveReturnsCorrectItem) {
  // E2 Laptop is most expensive at 1099.99
  const auto item = inv.findMostExpensive();

  EXPECT_NE(item, nullptr);
  EXPECT_EQ(item->getItemID(), "E2");
}

TEST_F(InventoryTest, FindMostExpensiveThrowsOnEmptyInventory) {
  Inventory emptyInv;
  EXPECT_THROW(emptyInv.findMostExpensive(), EmptyInventoryException);
}

// -- belowQuantityThreshold ---------------------------------------------------

TEST_F(InventoryTest, BelowQuantityThresholdReturnsCorrectItems) {
  // E2 has qty 5 - only item below threshold of 10
  const auto result = inv.belowQuantityThreshold(10);
  ASSERT_EQ(result.size(), 1);
  EXPECT_EQ(result[0]->getItemID(), "E2");
}

TEST_F(InventoryTest, BelowQuantityThresholdReturnsEmptyWhenNoneQualify) {
  const auto result = inv.belowQuantityThreshold(1);
  EXPECT_TRUE(result.empty());
}

TEST_F(InventoryTest, BelowQuantityThresholdReturnsAllWhenAllQualify) {
  const auto result = inv.belowQuantityThreshold(1000);
  EXPECT_EQ(result.size(), 4);
}

// -- getItems -----------------------------------------------------------------

TEST_F(InventoryTest, GetItemsReturnCorrectSize) {
  EXPECT_EQ(inv.getItems().size(), 4);
}

// -- moveSemantics ------------------------------------------------------------

TEST_F(InventoryTest, MoveConstructorTransfersItems) {
  const size_t original_size = inv.getItems().size();

  const Inventory movedInv = std::move(inv);

  EXPECT_EQ(movedInv.getItems().size(), original_size);
}
TEST_F(InventoryTest, MoveAssignmentTransfersItems) {
  const size_t original_size = inv.getItems().size();

  Inventory movedInv;
  movedInv = std::move(inv);

  EXPECT_EQ(movedInv.getItems().size(), original_size);
}
