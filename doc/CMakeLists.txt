option(DOCS "Build documentation" ON)

if(${DOCS})
  find_package(Doxygen)
  if(DOXYGEN_FOUND)
    set(CMAKE_DOCS_OUTPUT_DIRECTORY doc)
    configure_file(Doxyfile.in Doxyfile)
    add_custom_target(doc
      ALL
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      VERBATIM
      )
  endif()
endif()
