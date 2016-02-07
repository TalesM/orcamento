###############
# The library #
###############
add_library(controller STATIC
  MainControllerSqlite0_5
  Manager
)
target_include_directories(controller
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/
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
