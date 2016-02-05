###############
# The library #
###############
add_library(controller STATIC
  PlannerSqlite0_5.cpp
  Manager.cpp
)
target_include_directories(controller
  PUBLIC ${CMAKE_CURRENSOURCE_DIR}/
  PRIVATE ${CMAKE_SOURCE_DIR}/external/SQLiteCpp/include
  PRIVATE ${CMAKE_SOURCE_DIR}/external/SQLiteCpp/sqlite3
)
target_link_libraries(controller
  PUBLIC SQLiteCpp
  PUBLIC sqlite3
)
target_compile_features(controller
  PUBLIC cxx_aggregate_default_initializers
)
