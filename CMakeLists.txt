cmake_minimum_required(VERSION 3.16)
project(fourth_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(include)

add_executable(figures main.cpp)
target_include_directories(figures PRIVATE include)

find_package(GTest REQUIRED)
add_executable(figures_tests tests/tests.cpp)
target_include_directories(figures_tests PRIVATE include)
target_link_libraries(figures_tests PRIVATE GTest::gtest GTest::gtest_main pthread)
