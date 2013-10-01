cmake_minimum_required (VERSION 2.6)
project (mkTest)
set(CMAKE_AUTOMOC ON)
add_subdirectory(system)
set (mk_source_files main.cpp)
ADD_DEFINITIONS("-std=c++0x")
#set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")
find_package(Boost REQUIRED COMPONENTS regex)
find_package(Threads)
#list( APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")
#if(UNIX)
#    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -g -lpthread")
#    MESSAGE("-- Enabled std=c++11 --")
#endif()

# Google Logging
MESSAGE("-- Check for Google Log")
FIND_LIBRARY(GLOG_LIB NAMES glog PATHS ${SEARCH_LIBS})
IF (NOT EXISTS ${GLOG_LIB})
  MESSAGE(FATAL_ERROR
          "Can't find Google Log. Please specify: "
          "-DGLOG_LIB=...")
ENDIF (NOT EXISTS ${GLOG_LIB})
MESSAGE("-- Found Google Log library: ${GLOG_LIB}")

FIND_PATH(GLOG_INCLUDE NAMES glog/logging.h PATHS ${SEARCH_HEADERS})
IF (NOT EXISTS ${GLOG_INCLUDE})
  MESSAGE(FATAL_ERROR
          "Can't find Google Log. Please specify: "
          "-DGLOG_INCLUDE=...")
ENDIF (NOT EXISTS ${GLOG_INCLUDE})
MESSAGE("-- Found Google Log header in: ${GLOG_INCLUDE}")

include_directories(".")
include_directories(${Boost_INCLUDE_DIRS} )


add_executable(mk ${mk_source_files})

#SET_TARGET_PROPERTIES([some name] PROPERTIES LINKER_LANGUAGE CXX)

# Alternatively you could use ${Boost_LIBRARIES} here.
target_link_libraries( mk monitor ${Boost_REGEX_LIBRARY} ${GLOG_LIB} ${CMAKE_THREADS_LIBS_INIT})
