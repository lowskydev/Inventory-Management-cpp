cmake_minimum_required(VERSION 4.1)
project(IMS)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(IMS
        src/main.cpp
        src/Item.cpp
        src/Electronics.cpp
        src/Grocery.cpp
        src/Inventory.cpp
        src/CLI.cpp
)

target_include_directories(IMS PRIVATE include)

# Warning flags
target_compile_options(IMS PRIVATE
        -Wall        # all common warnings
        -Wextra      # extra warnings beyond -Wall
        -Wpedantic   # strict standard compliance
        -Wshadow     # warn when variable shadows another
        -Wconversion # warn on implicit type conversions
)