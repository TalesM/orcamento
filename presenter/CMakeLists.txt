
add_library(presenter
  Presenter
  SplasherPresenter
)

target_include_directories(presenter
  PUBLIC ../external/nana/include/
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(presenter
  controller
)

target_compile_features(presenter 
  PUBLIC cxx_lambdas
)

if(UNIX)
  set(THREADS_PREFER_PTHREAD_FLAG ON)
  find_package(Threads REQUIRED)
  find_package(X11 REQUIRED)
  find_package(Freetype REQUIRED)
  target_link_libraries(presenter 
    PUBLIC Threads::Threads
    PUBLIC ${X11_LIBRARIES}
    PUBLIC ${FREETYPE_LIBRARIES}
    PUBLIC Xft
    PUBLIC nana
  )
endif(UNIX)

