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
)

target_include_directories(IMS PRIVATE include)