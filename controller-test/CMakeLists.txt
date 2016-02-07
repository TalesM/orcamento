#######################
# The test executable #
#######################
add_executable(controller-test
#Unit tests
  Manager-unit.cpp
  PlannerSqlite0_5-unit.cpp

#The main
  main.cpp
)
target_include_directories(controller-test
  PRIVATE ${CATCH_INCLUDE_DIR}
  PRIVATE ${CMAKE_SOURCE_DIR}/external/SQLiteCpp/include
  PRIVATE ${CMAKE_SOURCE_DIR}/external/SQLiteCpp/sqlite3
  PRIVATE ../controller
)
target_link_libraries(controller-test
  PUBLIC controller
)
add_dependencies(controller-test
  catch
)
target_compile_features(controller-test
  PUBLIC cxx_aggregate_default_initializers
  PUBLIC cxx_thread_local
)
