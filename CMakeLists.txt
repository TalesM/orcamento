cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(orcamento VERSION 0.5 LANGUAGES CXX)

add_subdirectory(external/catch)
# add_subdirectory(external/sqlite3)
add_subdirectory(external/SQLiteCpp)
enable_testing(true)  # Enables unit-testing.

###############
# The library #
###############
add_library(orcamento STATIC
  library/PlannerSqlite0_5.cpp
)
target_include_directories(orcamento
  PUBLIC ${SQLITECPP_INCLUDE_DIR}
  PUBLIC ${SQLITE_INLUDE_DIRS}
)
target_link_libraries(orcamento
  PRIVATE SQLiteCpp
  PRIVATE sqlite3
)

#######################
# The test executable #
#######################
add_executable(orcamento_tests
  test/main.cpp
  test/PlannerSqlite0_5.cpp
)
target_include_directories(orcamento_tests
  PRIVATE ${CATCH_INCLUDE_DIR}
  PRIVATE library
)
target_link_libraries(orcamento_tests
  PRIVATE orcamento
)
add_dependencies(orcamento_tests
  catch
)
target_compile_features(orcamento_tests
  PUBLIC cxx_aggregate_default_initializers
  PUBLIC cxx_thread_local
)
