###############
# The library #
###############
add_library(orcamento STATIC
  PlannerSqlite0_5.cpp
  Manager.cpp
)
target_include_directories(orcamento
  PRIVATE ${CMAKE_SOURCE_DIR}/external/SQLiteCpp/include
  PRIVATE ${CMAKE_SOURCE_DIR}/external/SQLiteCpp/sqlite3
)
target_link_libraries(orcamento
  PUBLIC SQLiteCpp
  PUBLIC sqlite3
)
target_compile_features(orcamento
  PUBLIC cxx_aggregate_default_initializers
)
