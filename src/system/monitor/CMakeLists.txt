cmake_minimum_required(VERSION 2.6)

include_directories("system/core/")
ADD_DEFINITIONS("-std=c++0x")
set(monitor_source_files watcherImpl.hpp watcher.hpp fileWatcherImpl.hpp fileWatcher.hpp dummy.cpp)
add_library(monitor ${monitor_source_files})
target_link_libraries(monitor core exception)
