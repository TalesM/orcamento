cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(orcamento VERSION 0.5 LANGUAGES CXX)

add_subdirectory(external/catch)
add_subdirectory(external/nana)
add_subdirectory(external/sqlite3)
add_subdirectory(external/SQLiteCpp)
add_subdirectory(controller)
add_subdirectory(controller-test)
