
add_library(presenter
  Presenter
  SplasherPresenter
)

target_include_directories(presenter
  PUBLIC ../external/nana/include/
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(presenter 
  PUBLIC cxx_lambdas
)

add_executable(HelloWorld
  HelloWorld.cpp
)

target_include_directories(HelloWorld
  PRIVATE ${CMAKE_SOURCE_DIR}/external/nana/include/
)

target_link_libraries(HelloWorld nana)
set_property( TARGET HelloWorld PROPERTY CXX_STANDARD 14 ) #Uggly hack because I don't know how to inherit it from nana.
set_property( TARGET HelloWorld PROPERTY CXX_STANDARD_REQUIRED OFF ) #Uggly hack because I don't know how to inherit it from nana.
