cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(orcamento VERSION 0.5 LANGUAGES CXX)

option(orca-build-tests "Build test executables" ON)
option(orca-build-standalone "build standalone app" OFF)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/sqlite3/src)
add_subdirectory(external/catch)
add_subdirectory(external/nana)
add_subdirectory(external/sqlite3)
add_subdirectory(external/SQLiteCpp)
add_subdirectory(controller)
add_subdirectory(presenter)
if(orca-build-tests)
  add_subdirectory(controller-test)
  add_subdirectory(presenter-test)
endif(orca-build-tests)
if(orca-build-standalone)
  add_subdirectory(standalone)
endif(orca-build-standalone)