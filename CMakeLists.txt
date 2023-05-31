cmake_minimum_required(VERSION 3.2)

project(Greeks)

add_subdirectory(IVCalculator)

add_library(${PROJECT_NAME} Greeks.cpp Greeks.hpp)

target_link_libraries(${PROJECT_NAME} IV)
