#########################
# The library Front-end #
#########################
add_library(controller-interface STATIC
  Manager
)
target_include_directories(controller-interface
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/
)
target_compile_features(controller-interface
  PUBLIC cxx_aggregate_default_initializers
)

######################
# The SQLite backend #
######################
add_library(controller-sqlite3 STATIC
  MainControllerSqlite0_5
)
target_include_directories(controller-sqlite3
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/
  PUBLIC ${CMAKE_SOURCE_DIR}/external/SQLiteCpp/include
  PUBLIC ${CMAKE_SOURCE_DIR}/external/SQLiteCpp/sqlite3
)
target_link_libraries(controller-sqlite3
  PUBLIC controller-interface
  PUBLIC SQLiteCpp
  PUBLIC sqlite3
)
