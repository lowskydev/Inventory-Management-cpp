#pragma once

#include <optional>
#include <string>

class Item {
 private:
  std::string itemID;
  std::string name;
  int quantity;
  double price;

 public:
  static constexpr int MIN_QUANTITY = 0;
  static constexpr double MIN_PRICE = 0.0;

  Item(std::string itemID, std::string name, int quantity, double price);
  virtual ~Item() = default;

  [[nodiscard]] const std::string& getItemID() const noexcept;
  [[nodiscard]] const std::string& getName() const noexcept;
  [[nodiscard]] int getQuantity() const noexcept;
  [[nodiscard]] double getPrice() const noexcept;

  void setName(std::string newName);
  void setQuantity(int newQuantity);
  void setPrice(double newPrice);

  virtual void display() const = 0;

  [[nodiscard]] virtual std::string category() const noexcept = 0;

  [[nodiscard]] virtual std::string getExtraField() const = 0;

  [[nodiscard]] virtual std::optional<std::string> findAttribute(
      const std::string& key) const;
};