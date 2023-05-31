cmake_minimum_required(VERSION 3.2)

project(Greeks)

add_subdirectory(IVCalculator)
add_library(Greeks Greeks.cpp Greeks.hpp)

target_link_libraries(Greeks IV)
