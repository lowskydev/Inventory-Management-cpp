cmake_minimum_required(VERSION 4.1)
project(IMS)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -- Main Executable ----------------------------------------
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

# -- Google Test -------------------------------------------

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# -- Test Executable ---------------------------------------

add_executable(IMS_tests
        src/Item.cpp
        src/Electronics.cpp
        src/Grocery.cpp
        src/Inventory.cpp
        tests/test_item.cpp
        tests/test_inventory.cpp
        tests/test_electronics.cpp
        tests/test_grocery.cpp
        tests/test_file_io.cpp
)

target_include_directories(IMS_tests PRIVATE include)

target_compile_options(IMS_tests PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
)

target_link_libraries(IMS_tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(IMS_tests)