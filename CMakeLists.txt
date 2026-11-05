cmake_minimum_required(VERSION 3.5)

project(Greeks VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
        Greeks/Greeks.hpp
        Greeks/Greeks.cpp
        Greeks/IVCalculator/Model2.hpp
        Greeks/IVCalculator/Model2.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Greeks
)

add_executable(greeks_test main.cpp)
target_link_libraries(greeks_test PRIVATE ${PROJECT_NAME})



