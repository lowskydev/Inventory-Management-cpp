#include <gtest/gtest.h>

#include "Inventory.h"
#include "Utils.h"

class InventoryTest : public testing::Test {
  Inventory inv;
  void SetUp() override {
    inv.addItem(utils::makeElectronics("E1", "Phone", 10, 699.99, 24));
    inv.addItem(utils::makeElectronics("E2", "Laptop", 5, 1099.99, 12));
    inv.addItem(utils::makeGrocery("G1", "Apple", 100, 0.99, "2026-06-01"));
    inv.addItem(utils::makeGrocery("G2", "Milk", 30, 1.49, "2026-04-10"));
  }

  void TearDown() override;
};
