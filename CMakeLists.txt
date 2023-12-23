cmake_minimum_required(VERSION 3.5)

project(Greeks VERSION 1.0 LANGUAGES C CXX)

add_library(${PROJECT_NAME} STATIC
        Greeks/Greeks.hpp
        Greeks/Greeks.cpp
        Greeks/IVCalculator/Model2.hpp
        Greeks/IVCalculator/Model2.cpp
)



