#include <gtest/gtest.h>

#include "Electronics.h"
#include "Exceptions.h"

// Electronics is used to test abstract Item class.
// All methods under test here are defined in Item and inherited unchanged
class ItemTest : public testing::Test {
 protected:
  Electronics item{"E1", "Phone", 10, 699.99, 24};
};

// -- Constructor --------------------------------------------------------------

TEST_F(ItemTest, ConstructorRejectsNegativeQuantity) {
  EXPECT_THROW(Electronics("E2", "Laptop", -1, 699.99, 24),
               InvalidValueException);
}

TEST_F(ItemTest, ConstructorRejectsNegativePrice) {
  EXPECT_THROW(Electronics("E2", "Laptop", 10, -699.99, 24),
               InvalidValueException);
}

TEST_F(ItemTest, ConstructorAcceptsPositiveQuantity) {
  EXPECT_NO_THROW(Electronics("E2", "Laptop", 10, 699.99, 24));
}

TEST_F(ItemTest, ConstructorAcceptsPositivePrice) {
  EXPECT_NO_THROW(Electronics("E2", "Laptop", 10, 699.99, 24));
}

// -- Getters ------------------------------------------------------------------

TEST_F(ItemTest, GettersReturnCorrectValuesAfterConstruction) {
  EXPECT_EQ(item.getItemID(), "E1");
  EXPECT_EQ(item.getName(), "Phone");
  EXPECT_EQ(item.getQuantity(), 10);
  EXPECT_DOUBLE_EQ(item.getPrice(), 699.99);
}

// -- setQuantity --------------------------------------------------------------

TEST_F(ItemTest, SetQuantityRejectsNegative) {
  EXPECT_THROW(item.setQuantity(-10), InvalidValueException);
}

TEST_F(ItemTest, SetQuantityAcceptsPositive) {
  EXPECT_NO_THROW(item.setQuantity(100));
  EXPECT_EQ(item.getQuantity(), 100);
}

// -- setPrice -----------------------------------------------------------------

TEST_F(ItemTest, SetPriceRejectsNegative) {
  EXPECT_THROW(item.setPrice(-10), InvalidValueException);
}

TEST_F(ItemTest, SetPriceAcceptsPositive) {
  EXPECT_NO_THROW(item.setPrice(999.99));
  EXPECT_DOUBLE_EQ(item.getPrice(), 999.99);
}

// -- setName ------------------------------------------------------------------

TEST_F(ItemTest, SetNameUpdatesCorrectly) {
  EXPECT_NO_THROW(item.setName("USB C Cable"));
  EXPECT_EQ(item.getName(), "USB C Cable");
}

// -- findAttribute ------------------------------------------------------------

TEST_F(ItemTest, FindAttributeReturnsNulloptForUnknownKey) {
  const auto result = item.findAttribute("unknown");
  EXPECT_FALSE(result.has_value());
}