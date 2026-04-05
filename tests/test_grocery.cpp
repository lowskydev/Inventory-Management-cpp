#include <gtest/gtest.h>

#include "Exceptions.h"
#include "Grocery.h"

class GroceryTest : public testing::Test {
 protected:
  Grocery item{"G1", "Apple", 100, 0.99, "2026-06-01"};
};

// -- isValidDate --------------------------------------------------------------

TEST_F(GroceryTest, IsValidDateAcceptsValidDate) {
  EXPECT_TRUE(Grocery::isValidDate("2026-04-05"));
}
TEST_F(GroceryTest, IsValidDateRejectsWrongLength) {
  EXPECT_FALSE(Grocery::isValidDate("2026-6-1"));
  EXPECT_FALSE(Grocery::isValidDate("26-06-01"));
  EXPECT_FALSE(Grocery::isValidDate(""));
}

TEST_F(GroceryTest, IsValidDateRejectsMissingDashes) {
  EXPECT_FALSE(Grocery::isValidDate("20260601"));
  EXPECT_FALSE(Grocery::isValidDate("2026/06/01"));
}

TEST_F(GroceryTest, IsValidDateRejectsLetters) {
  EXPECT_FALSE(Grocery::isValidDate("YYYY-MM-DD"));
  EXPECT_FALSE(Grocery::isValidDate("2026-AB-01"));
}

TEST_F(GroceryTest, IsValidDateRejectsInvalidMonth) {
  EXPECT_FALSE(Grocery::isValidDate("2026-00-01"));
  EXPECT_FALSE(Grocery::isValidDate("2026-13-01"));
}

TEST_F(GroceryTest, IsValidDateRejectsInvalidDay) {
  EXPECT_FALSE(Grocery::isValidDate("2026-06-00"));
  EXPECT_FALSE(Grocery::isValidDate("2026-06-32"));
}

TEST_F(GroceryTest, IsValidDateRejectsYearBelow1900) {
  EXPECT_FALSE(Grocery::isValidDate("1899-06-01"));
}

// -- Constructor --------------------------------------------------------------

TEST_F(GroceryTest, ConstructorRejectsInvalidDate) {
  EXPECT_THROW(Grocery("G2", "Milk", 10, 1.49, "not-a-date"),
               InvalidValueException);
}

TEST_F(GroceryTest, ConstructorAcceptsValidDate) {
  EXPECT_NO_THROW(Grocery("G2", "Milk", 10, 1.49, "2026-04-05"));
}

// -- GetExpirationDate --------------------------------------------------------

TEST_F(GroceryTest, GetExpirationDateReturnsCorrectValue) {
  EXPECT_EQ(item.getExpirationDate(), "2026-06-01");
}

// -- SetExpirationDate --------------------------------------------------------

TEST_F(GroceryTest, SetExpirationDateRejectsInvalidFormat) {
  EXPECT_THROW(item.setExpirationDate("not-a-date"), InvalidValueException);
}

TEST_F(GroceryTest, SetExpirationDateAcceptsValidDate) {
  EXPECT_NO_THROW(item.setExpirationDate("2027-01-01"));
  EXPECT_EQ(item.getExpirationDate(), "2027-01-01");
}

// -- Category -----------------------------------------------------------------

TEST_F(GroceryTest, CategoryReturnsCorrectString) {
  EXPECT_EQ(item.category(), "Grocery");
}

// -- getExtraField ------------------------------------------------------------

TEST_F(GroceryTest, GetExtraFieldReturnsExpirationDate) {
  EXPECT_EQ(item.getExtraField(), "2026-06-01");
}

// -- findAttribute ------------------------------------------------------------

TEST_F(GroceryTest, FindAttributeReturnsDateForExpirationKey) {
  const auto result = item.findAttribute("expiration");
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), "2026-06-01");
}

TEST_F(GroceryTest, FindAttributeReturnsNulloptForUnknownKey) {
  const auto result = item.findAttribute("unknown");
  EXPECT_FALSE(result.has_value());
}