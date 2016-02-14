#######################
# The test executable #
#######################
add_executable(presenter-test
#Unit tests
  EstimateDetailPresenter-unit
  EstimateListPresenter-unit
  ExecutionListPresenter-unit
  MainPresenter-unit
  Presenter-unit
  SplasherPresenter-unit

#Integration Scenarios
  #Startup-scenario

#The main
  main.cpp
)
target_include_directories(presenter-test
  PRIVATE ${CATCH_INCLUDE_DIR}
)
target_link_libraries(presenter-test
  PRIVATE presenter
)
add_dependencies(presenter-test
  catch
)
target_compile_features(presenter-test
  PUBLIC cxx_aggregate_default_initializers
  PUBLIC cxx_thread_local
)
