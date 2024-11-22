cmake_minimum_required(VERSION 3.10)
project(MatrixLibrary)

# Find Python and Pybind11
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

# Define the source files
set(SOURCES src/matrix.cpp)

# Create a shared library for Python bindings
pybind11_add_module(matrix_module ${SOURCES})

# Optionally, set the output name for the shared library
set_target_properties(matrix_module PROPERTIES PREFIX "")

# Link Python3 and Pybind11
target_link_libraries(matrix_module PRIVATE Python3::Python pybind11::module)
