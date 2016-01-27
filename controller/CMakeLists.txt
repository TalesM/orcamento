###############
# The library #
###############
add_library(orcamento STATIC
  PlannerSqlite0_5.cpp
  Manager.cpp
)
target_include_directories(orcamento
  PUBLIC ${SQLITECPP_INCLUDE_DIR}
  PUBLIC ${SQLITE_INLUDE_DIRS}
)
target_link_libraries(orcamento
  PUBLIC SQLiteCpp
)
target_compile_features(orcamento
  PUBLIC cxx_aggregate_default_initializers
)
