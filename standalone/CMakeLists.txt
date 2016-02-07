add_executable(orcamento-standalone
  main
)
set_target_properties(orcamento-standalone PROPERTIES 
  OUTPUT_NAME orcamento
)

target_link_libraries(orcamento-standalone
  presenter
  controller-sqlite3
)