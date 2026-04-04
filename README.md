# Inventory Management System

A command-line inventory management system written in modern C++23.

## Features

- Add, remove, and update Electronics and Grocery items
- Filter items by quantity threshold
- Sort items by price
- Find the most expensive item
- Save and load inventory from CSV files
- Full input validation with descriptive error messages

## Build

Requires CMake 4.1+ and a C++23 compatible compiler (GCC 13+ or Clang 16+).

```bash
cmake -B build
cmake --build build
```

## Run

```bash
./build/IMS
```

## CSV Format

The inventory can be saved and loaded from a CSV file.
Each line represents one item:

```
itemID,category,name,quantity,price,extra
```

Where `extra` is `warrantyMonths` for Electronics or `expirationDate` for Grocery.

Sample file:

```
E1,Electronics,Phone,10,699.99,24
E2,Electronics,Laptop,5,1099.99,12
G1,Grocery,Apple,100,0.99,2026-06-01
G2,Grocery,Milk,30,1.49,2026-04-10
```

## Project Structure

```
include/       — header files
src/           — implementation files
inventory.csv  — sample inventory file
```

## Design Decisions

**Why `std::erase_if` instead of `remove_if` + `erase`?**  
`std::erase_if` is the C++20 equivalent - cleaner and does the same thing.

**Why `std::ranges` algorithms instead of `std`?**  
Ranges algorithms accept containers directly without requiring explicit
`begin()`/`end()` calls which reduces noise.

**Why `getExtraField()` instead of `dynamic_cast` in `writeToFile`?**  
The original approach used `dynamic_cast` to detect the item type and extract
the extra field. Every new derived class would require finding and updating if statement.

**Why is `Inventory` non-copyable?**  
Two inventories sharing the same item objects via `shared_ptr` would cause
silent inventory mutations. Moving is allowed - it transfers ownership
cleanly and leaves the source empty.

**Why a free function `runCLI` instead of a class?**  
The CLI has no meaningful state of its own - `Inventory` holds everything.
A class would add structure without adding clarity.

**Why does `sortItems` delegate to `Inventory::sortBy` instead of sorting directly?**  
`sortItems` is a free function but needs to modify the private `items` vector.
Rather than exposing a mutable getter - which would let anyone call
`inv.getItems().clear()` - we keep mutation internal and delegate through a
method that has legitimate private access.
