cmake_minimum_required(VERSION 2.6)

#include_directories(".")
ADD_DEFINITIONS("-std=c++0x")
set(exception_source_files exception.hpp exception.cpp)
add_library(exception ${exception_source_files})
