add_library(IV
        black_scholes.h
        black_scholes.cpp
        bs_prices.h
        interval_bisection.h
        Model2.cpp
        Model2.h)

target_link_libraries(IV INTERFACE ${PROJECT_NAME}_OPTIONS ${PROJECT_NAME}_WARNINGS)