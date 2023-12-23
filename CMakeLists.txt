cmake_minimum_required(VERSION 3.5)

project(Greeks VERSION 1.0 LANGUAGES C CXX)

add_library(${PROJECT_NAME} STATIC
        Greeks/Greeks.hpp
        Greeks/Greeks.cpp
        Greeks/IVCalculator/Model2.hpp
        Greeks/IVCalculator/Model2.cpp
)

include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
    if (ENABLE_BUILD_WITH_TIME_TRACE)
        add_compile_definitions(${PROJECT_NAME} INTERFACE -ftime-trace)
    endif ()
endif ()


# enable cache system
include(cmake/Cache.cmake)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(${PROJECT_NAME})

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(${PROJECT_NAME})

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
    # This sets a global PCH parameter, each project will build its own PCH, which is a good idea if any #define's change
    #
    # consider breaking this out per project as necessary
    target_precompile_headers(
            ${PROJECT_NAME}
            INTERFACE
            <vector>
            <string>
            <map>
            <utility>
    )
endif ()

