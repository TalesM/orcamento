#######################
# The test executable #
#######################
add_executable(Presenter-test
#Unit tests
  MainPresenter-unit
  Presenter-unit
  SplasherPresenter-unit

#Integration Scenarios
  Startup-scenario

#The main
  main.cpp
)
target_include_directories(Presenter-test
  PRIVATE ${CATCH_INCLUDE_DIR}
)
target_link_libraries(Presenter-test
  PRIVATE nana
  PRIVATE presenter
)
add_dependencies(Presenter-test
  catch
)
target_compile_features(Presenter-test
  PUBLIC cxx_aggregate_default_initializers
  PUBLIC cxx_thread_local
)
