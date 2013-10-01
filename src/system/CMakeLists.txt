cmake_minimum_required(VERSION 2.6)

project(mkTest)

include_directories(".")
add_subdirectory(core)
add_subdirectory(exception)
add_subdirectory(monitor)


#add_library(system)
#target_link_libraries(system monitor)
