#include <gtest/gtest.h>

#include "Electronics.h"
#include "Exceptions.h"

class ElectronicsTest : public testing::Test {
 protected:
  Electronics item{"E1", "Phone", 10, 699.99, 24};
};

// -- Constructor --------------------------------------------------------------

TEST_F(ElectronicsTest, ConstructorRejectsNegativeWarranty) {
  EXPECT_THROW(Electronics("E2", "Laptop", 10, 699.99, -24),
               InvalidValueException);
}

TEST_F(ElectronicsTest, ConstructorAcceptsZeroWarranty) {
  EXPECT_NO_THROW(Electronics("E2", "Laptop", 10, 699.99, 0));
}

TEST_F(ElectronicsTest, ConstructorAcceptsPositiveWarranty) {
  EXPECT_NO_THROW(Electronics("E2", "Laptop", 10, 699.99, 24));
}

// -- getWarrantyMonths --------------------------------------------------------

TEST_F(ElectronicsTest, GetWarrantyMonthsReturnsCorrectValue) {
  EXPECT_EQ(item.getWarrantyMonths(), 24);
}

// -- setWarrantyMonths --------------------------------------------------------

TEST_F(ElectronicsTest, SetWarrantyMonthsRejectsNegative) {
  EXPECT_THROW(item.setWarrantyMonths(-60), InvalidValueException);
}

TEST_F(ElectronicsTest, SetWarrantyMonthsAcceptsZero) {
  EXPECT_NO_THROW(item.setWarrantyMonths(0));
  EXPECT_EQ(item.getWarrantyMonths(), 0);
}

TEST_F(ElectronicsTest, SetWarrantyMonthsAcceptsPositive) {
  EXPECT_NO_THROW(item.setWarrantyMonths(60));
  EXPECT_EQ(item.getWarrantyMonths(), 60);
}

// -- Category -----------------------------------------------------------------

TEST_F(ElectronicsTest, CategoryReturnsCorrectString) {
  EXPECT_EQ(item.category(), "Electronics");
}

// -- GetExtraField ------------------------------------------------------------

TEST_F(ElectronicsTest, GetExtraFieldReturnsWarrantyAsString) {
  EXPECT_EQ(item.getExtraField(), "24");
}

// -- findAttribute ------------------------------------------------------------

TEST_F(ElectronicsTest, FindAttributeReturnsWarrantyForWarrantyKey) {
  const auto result = item.findAttribute("warranty");
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), "24 months");
}

TEST_F(ElectronicsTest, FindAttributeReturnsNulloptForUknownKey) {
  const auto result = item.findAttribute("unknown");
  EXPECT_FALSE(result.has_value());
}