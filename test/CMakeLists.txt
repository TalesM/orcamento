#######################
# The test executable #
#######################
add_executable(orcamento_tests
#Unit tests
  Manager-unit.cpp
  PlannerSqlite0_5-unit.cpp

#The main
  main.cpp
)
target_include_directories(orcamento_tests
  PRIVATE ${CATCH_INCLUDE_DIR}
  PRIVATE ../controller
)
target_link_libraries(orcamento_tests
  PUBLIC orcamento
)
add_dependencies(orcamento_tests
  catch
)
target_compile_features(orcamento_tests
  PUBLIC cxx_aggregate_default_initializers
  PUBLIC cxx_thread_local
)
