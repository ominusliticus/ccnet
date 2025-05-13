cmake_minimum_required(VERSION 3.20)
project(
    CCNet 
    VERSION 0.1
    LANGUAGES CXX  # PYTHON
)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
include(CMakePrintHelpers)

set(CCNet_SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(CCNet_PYTHON_DIR "${PROJECT_SOURCE_DIR}/python")

# Specify version number and internal paths as necessary
configure_file(
    "${CMAKE_SOURCE_DIR}/cmake/version.hpp.in"
    "${CMAKE_SOURCE_DIR}/src/version.hpp"
    @ONLY
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(
    -Wall -Wpedantic -Wextra
    -std=c++20
    # -fconcepts-diagnostics-depth=3
    # -Wno-gnu-statement-expression
)

add_subdirectory(src)
# add_subdirectory(python)

# Intel OneAPI MKL library
find_package(MKL REQUIRED)

# Numerical Linear Algebra libraries
set(blaspp_DIR "${CCNet_SOURCE_DIR}/third_party/installs/lib/cmake/blaspp")
set(lapackpp_DIR "${CCNet_SOURCE_DIR}/third_party/installs/lib/cmake/lapackpp")
find_package(blaspp REQUIRED)
find_package(lapackpp REQUIRED)

add_executable(
    ccnet 
    "${CCNet_SRC_DIR}/main.cpp"
)
target_include_directories(
    ccnet
    PUBLIC
    ${CCNet_SRC_DIR}
    ${CCNet_SOURCE_DIR}/third_party/installs/include
    "$ENV{HOME}/intel/oneapi/2025.1/include"
)
target_link_libraries(
    ccnet
    PUBLIC
    blaspp
    lapackpp
    $<LINK_ONLY:MKL::MKL>
)
target_sources(
    ccnet
    PUBLIC
    ${CCNet_SOURCE_FILES}
)

# Testing 
add_subdirectory(tests)
