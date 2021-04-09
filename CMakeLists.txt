cmake_minimum_required(VERSION 3.15.1)

project(pyduk VERSION 0.1)

option(TEST "Build tests" ON)
option(DOCS "Build documentation" ON)
option(MODULE_ONLY "Build python module only" OFF)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/pyduk)
if(NOT(${MODULE_ONLY}))
  add_subdirectory(${PROJECT_SOURCE_DIR}/src/main)
  if(${DOCS})
    add_subdirectory(${PROJECT_SOURCE_DIR}/doc)
  endif()
  if(${TEST})
    add_subdirectory(${PROJECT_SOURCE_DIR}/test)
  endif()
endif()


install(
    TARGETS pyduk
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
