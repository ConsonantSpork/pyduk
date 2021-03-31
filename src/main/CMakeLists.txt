add_executable(main main.cpp)
get_target_property(DUKTAPE_SOURCE_DIR duktape SOURCE_DIR)
get_target_property(PYDUK_SOURCE_DIR pyduk SOURCE_DIR)
get_target_property(PYDUK_BINARY_DIR pyduk BINARY_DIR)
target_include_directories(main
  PRIVATE
  ${DUKTAPE_SOURCE_DIR}
  ${PYDUK_SOURCE_DIR}
  ${PYDUK_BINARY_DIR}
  )
target_link_libraries(main
  PRIVATE
  duktape
  pyduk
  )
