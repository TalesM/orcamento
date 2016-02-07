#######################
# The test executable #
#######################
add_executable(controller-test
#Unit tests
  MainControllerSqlite0_5-unit
  Manager-unit.cpp

#The main
  main.cpp
)
target_include_directories(controller-test
  PRIVATE ${CATCH_INCLUDE_DIR}
  PRIVATE ${CMAKE_SOURCE_DIR}/external/SQLiteCpp/include
  PRIVATE ${CMAKE_SOURCE_DIR}/external/SQLiteCpp/sqlite3
)
target_link_libraries(controller-test
  PUBLIC controller-sqlite3
)
add_dependencies(controller-test
  catch
)
target_compile_features(controller-test
  PUBLIC cxx_aggregate_default_initializers
  PUBLIC cxx_thread_local
)
