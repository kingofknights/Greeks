add_library(IV STATIC
        Model2.cpp
        Model2.h)

target_link_libraries(IV INTERFACE ${PROJECT_NAME}_OPTIONS ${PROJECT_NAME}_WARNINGS)