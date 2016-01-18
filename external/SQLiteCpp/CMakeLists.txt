cmake_minimum_required(VERSION 2.8.8)
project(SQLiteCpp_builder CXX)
include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
    SQLiteCpp
    PREFIX ${CMAKE_BINARY_DIR}/SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    TIMEOUT 100
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
   )

# Expose required variable (CATCH_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(SQLiteCpp source_dir)
set(SQLITECPP_INCLUDE_DIR ${source_dir}/include ${source_dir}/sqlite3 CACHE INTERNAL "Path to include folder for SQLiteCpp")
