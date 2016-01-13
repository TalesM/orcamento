cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(orcamento VERSION 0.5 LANGUAGES CXX)


add_executable(orcamento
  main.cpp
)

add_executable(orcamento_tests
  test/main.cpp
)
add_subdirectory(external/catch)
enable_testing(true)  # Enables unit-testing.
add_dependencies(orcamento_tests catch)
target_include_directories(orcamento_tests
  PRIVATE ${CATCH_INCLUDE_DIR}
)
