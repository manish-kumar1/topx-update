cmake_minimum_required(VERSION 2.6)

#include_directories("system/exception")
ADD_DEFINITIONS("-std=c++0x")
set(core_source_files object.hpp runnable.hpp file.hpp file.cpp)
add_library(core ${core_source_files})
#target_link_libraries(core exception)
