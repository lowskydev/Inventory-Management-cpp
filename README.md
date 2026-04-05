<div align="center">

[![C++23](https://img.shields.io/badge/C%2B%2B-23-4FC3F7?style=for-the-badge&labelColor=2D2D2D&logo=cplusplus&logoColor=4FC3F7)](https://en.cppreference.com)
&nbsp;&nbsp;
[![CMake](https://img.shields.io/badge/CMake-4.1-FF6B6B?style=for-the-badge&labelColor=2D2D2D&logo=cmake&logoColor=white)](https://cmake.org)
&nbsp;&nbsp;
[![Google Test](https://img.shields.io/badge/Google_Test-1.14-F9AB00?style=for-the-badge&labelColor=2D2D2D&logo=google&logoColor=white)](https://github.com/google/googletest)
&nbsp;&nbsp;
[![CI](https://img.shields.io/badge/CI-2D2D2D?style=for-the-badge&logo=github&logoColor=white)](https://github.com/USERNAME/REPO/actions)

</div>

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

Requires CMake 3.20+ and a C++23 compatible compiler (GCC 13+ or Clang 16+).

```bash
cmake -B build
cmake --build build
```

## Run

```bash
./build/IMS
```

## Tests

Unit tests are written with [Google Test](https://github.com/google/googletest).
Google Test is downloaded automatically by CMake - no manual installation needed.

```bash
cmake -B build
cmake --build build
./build/IMS_tests
```

Or via CTest:

```bash
cd build && ctest --output-on-failure
```

### What is tested

- `Item` - setter validation, constructor validation, getters
- `Electronics` - warranty validation, category, findAttribute
- `Grocery` - date format validation, constructor, findAttribute
- `Inventory` - add, remove, update, find, filter, move semantics
- `FileIO` - write, read, read-write cycle, edge cases

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
include/           - header files
src/               - implementation files
tests/             - Google Test unit tests
.github/workflows/ - CI pipeline
inventory.csv      - sample inventory file
```

## CI

Every push to `main` or `dev` and every pull request automatically triggers
a build and test run on Ubuntu via GitHub Actions. The pipeline compiles the
project with GCC 13 and runs the full test suite.

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
