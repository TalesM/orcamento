cmake_minimum_required(VERSION 2.8.8)
include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
    SQLiteCpp_Downloader
    PREFIX ${CMAKE_BINARY_DIR}/SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    TIMEOUT 100
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
   )

# Expose required variable (CATCH_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(SQLiteCpp_Downloader source_dir)
set(SQLITECPP_INCLUDE_DIR ${source_dir}/include ${source_dir}/sqlite3/ CACHE INTERNAL "Path to include folder for SQLiteCpp")

# FILE(GLOB SQLiteCpp_Sources ${source_dir}/src)

add_library(SQLiteCpp STATIC
  ${source_dir}/src/Backup.cpp
  ${source_dir}/src/Column.cpp
  ${source_dir}/src/Database.cpp
  ${source_dir}/src/Statement.cpp
  ${source_dir}/src/Transaction.cpp
)
target_include_directories(SQLiteCpp
  PUBLIC ${source_dir}/sqlite3/
  PUBLIC ${source_dir}/include/
)
target_link_libraries(SQLiteCpp
  sqlite3
)
add_dependencies(SQLiteCpp SQLiteCpp_Downloader)
